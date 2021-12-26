#include "int.h"
#include "util.h"
#include "userint.h"
#include "logger.h"
#include "pcb.h"
#include "schedule.h"
#include "KernelS.h"
#include "iostream.h"

#define TIMER_IVTE 0x08

ISR oldISR=NULL;
volatile int onDemand=0;
volatile unsigned cnt;
volatile Time remainingTime=defaultTimeSlice;
unsigned gss;
unsigned gsp;
unsigned gbp;

void interrupt timerISR(...)
{
	if(onDemand==0)
	{
		if(oldISR!=NULL)
		{
			oldISR();
		}
		if(remainingTime>0)
		{
			remainingTime--;
		}
		cnt++;
		while(lock==0 && cnt>0){
			cnt--;
			tick();
			llist_KernelSemp::listNode* h=KernelSem::allSem()->head;
			while(h!=NULL)
			{
				KernelSem* ks=h->value;

				if(!ks->blockedHere.emptyTimer())
				{
					Time timeout = ks->blockedHere.timerHead->timeout;
					if(timeout==1)
					{
						PCB* t=ks->blockedHere.topTimer();
						ks->blockedHere.popTimer();
						ks->val++;
						t->state=THREAD_STATE_READY;
						t->semReturn=0;
						Scheduler::put(t);
						while(ks->blockedHere.timerHead!=NULL  && ks->blockedHere.timerHead->timeout==0)
						{
							PCB* t=ks->blockedHere.topTimer();
							ks->blockedHere.popTimer();
							ks->val++;
							t->state=THREAD_STATE_READY;
							t->semReturn=0;
							Scheduler::put(t);
						}
					}
					else if(timeout>1)
					{
						ks->blockedHere.timerHead->timeout--;
					}
				}

				h=h->next;
			}
		}
	}

	if(lock==0 && (onDemand==1 || (remainingTime==0 && PCB::running->timeSlice!=0)))
	{
		INTDN();
		onDemand=0;
		if(PCB::running->state==THREAD_STATE_READY)
		{
			Scheduler::put(PCB::running);
		}
		else if(PCB::running->state==THREAD_STATE_FINISHED)
		{
			PCB::running->deallocate();
			PCB::rerunAllocator();
		}

		PCB::oldRunning=PCB::running;
		PCB::running=Scheduler::get();

		if(PCB::running==NULL)
		{
			debug("Zero ready processes, potential deadlock?");
			PCB::running=PCB::idleThread;
			if(PCB::idleThread==NULL)
			{
				panic("Idle thread is NULL");
			}
		}

		remainingTime=PCB::running->timeSlice;

		//save context
		asm{
			mov gss, ss
			mov gsp, sp
			mov gbp, bp
		}

		PCB::oldRunning->sSeg=gss;
		PCB::oldRunning->sp=gsp;
		PCB::oldRunning->bp=gbp;

		gss=PCB::running->sSeg;
		gsp=PCB::running->sp;
		gbp=PCB::running->bp;

		//restore context
		asm{
			mov ss, gss
			mov sp, gsp
			mov bp, gbp
		}
		INTEN();
	}
}

void initIVTP()
{
	REALINTDN();
	oldISR=getvect(TIMER_IVTE);
	if(oldISR==NULL)
	{
		warning("oldISR is NULL");
	}
	setvect(TIMER_IVTE,timerISR);
	REALINTEN();
}

void releaseIVTP()
{
	REALINTDN();
	if(oldISR!=NULL)
	{
		setvect(TIMER_IVTE,oldISR);
	}
	REALINTEN();
}
