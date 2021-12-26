#include "KernelS.h"
#include "Schedule.h"
#include "logger.h"
#include "iostream.h"

llist_KernelSemp* KernelSem::asp=NULL;

KernelSem::KernelSem(int v, Semaphore* s)
{
	val=v;
	mySem=s;
	//REALINTDN();
	INTDN();
	allSem()->insertFront(this);
	INTEN();
	//REALINTEN();
}

KernelSem::~KernelSem()
{
	while(!blockedHere.emptySignal())
	{
		signal();
	}
	//REALINTDN();
	INTDN();
	allSem()->removePredicate(KSPredicate,this);
	INTEN();
	//REALINTEN();
}

llist_KernelSemp* KernelSem::allSem()
{
	if(asp==NULL)
	{
		INTDN();
		asp=new llist_KernelSemp;
		INTEN();
	}
	return asp;
}

int KernelSem::KSPredicate(KernelSem* a,void* b)
{
	KernelSem* kb = (KernelSem*) b;
	return a==kb;
}

int KernelSem::wait(Time maxTimeToWait)
{
	//REALINTDN();
	INTDN();
	val--;
	PCB::running->semReturn=2;
	if(val<0)
	{
		PCB::running->semReturn=1;
		PCB::running->state=THREAD_STATE_BLOCKED;
		if(maxTimeToWait==0)
		{
			blockedHere.insertSignal(PCB::running);
		}
		else
		{
			blockedHere.insertTimer(PCB::running,maxTimeToWait);
		}
	}
	INTEN();
	//REALINTEN();
	if(PCB::running->state==THREAD_STATE_BLOCKED)
	{
		dispatch();
	}
	return PCB::running->semReturn;
}

void KernelSem::signal()
{
	//REALINTDN();
	INTDN();
	val++;
	if(!blockedHere.emptySignal())
	{
		PCB* p=blockedHere.topSignal();
		blockedHere.popSignal();
		p->state=THREAD_STATE_READY;
		Scheduler::put(p);
	}
	INTEN();
	//REALINTEN();
}

int KernelSem::value() const
{
	int ret;
	//REALINTDN();
	INTDN();
	ret=val;
	INTEN();
	//REALINTEN();
	return ret;
}
