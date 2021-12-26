#include "KernelE.h"
#include "SCHEDULE.h"

KernelEv::KernelEv(IVTNo i,Event* e)
{
	ivtno=i;
	myEv=e;
	val=0;
	owner=PCB::running;
}

KernelEv::~KernelEv()
{
	//REALINTDN();
	INTDN();
	if(val<0)
	{
		signal();
	}
	INTEN();
	//REALINTEN();
}

void KernelEv::wait()
{
	if(owner!=PCB::running){return;}
	//REALINTDN();
	INTDN();
	val--;
	if(val<0)
	{
		val=-1;
		PCB::running->state=THREAD_STATE_BLOCKED;
	}
	INTEN();
	//REALINTEN();
	if(PCB::running->state==THREAD_STATE_BLOCKED)
	{
		dispatch();
	}
}

void KernelEv::signal()
{
	//REALINTDN();
	val++;
	if(val==0)
	{
		owner->state=THREAD_STATE_READY;
		if(PCB::running!=owner)
		{
			Scheduler::put(owner);
		}
	}
	else
	{
	val=1;
	}
	dispatch();
	//REALINTEN();
}
