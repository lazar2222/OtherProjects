#include "thread.h"
#include "pcb.h"
#include "util.h"
#include "logger.h"
#include "int.h"
#include "schedule.h"
#include "iostream.h"

//assuming constructor called in clone
ID Thread::fork()
{
	PCB* p2;
	Thread* t;
	if(PCB::running->myThread!=NULL)
	{
		t=PCB::running->myThread->clone();
		if(t==NULL)
		{
			warning("Cant clone");
			return -1;
		}
		p2=t->myPCB;
	}
	else
	{
		panic("Kernel fork",RETURN_CODE_DEFAULT);
	}
	if(p2->tryAllocate())
	{
		INTDN();
		PCB::running->forkReturn=p2->PID;
		p2->forkReturn=0;
		p2->state=THREAD_STATE_READY;
		PCB::running->myChildren.insertFront(p2);
		Scheduler::put(p2);
		PCB::childThread=p2;
		//p2->EOS+=3;
		walkStack();
		if(PCB::running->forkReturn!=0)
		{
			INTEN();
		}
		return PCB::running->forkReturn;
	}
	else
	{
		delete t;
		return -1;
	}
}

void Thread::exit()
{
	PCB::running->state=THREAD_STATE_FINISHED;
	//deallocate stack after context switch
	dispatch();
}

void Thread::waitForForkChildren()
{
	PCB* p=PCB::running->myChildren.top();
	while(p!=NULL)
	{
		PCB::running->myChildren.pop();
		p->myThread->waitToComplete();
		p=PCB::running->myChildren.top();
	}
}

Thread::Thread (StackSize stackSize, Time timeSlice)
{
	INTDN();
	myPCB=new PCB(this,stackSize,timeSlice);
	INTEN();
	if(myPCB==NULL)
	{
		panic("No memory for Thread PCB",RETURN_CODE_OUTOFMEMORY);
	}
}

Thread::~Thread()
{
	waitToComplete();
	INTDN();
	delete myPCB;
	INTEN();
}

void Thread::start()
{
	if(myPCB->state!=THREAD_STATE_INIT && myPCB->state!=THREAD_STATE_WAITINGALLOC){return;}
	if(myPCB->tryAllocate())
	{
		myPCB->state=THREAD_STATE_READY;
		Scheduler::put(myPCB);
	}
	else
	{
		myPCB->state=THREAD_STATE_WAITINGALLOC;
		PCB::allocatorQueue.insert(myPCB);
	}
}

void Thread::waitToComplete()
{
	if(PCB::running==this->myPCB)
	{
		error("Thread tried of wait itself");
		return;
	}
	if(this->myPCB->state==THREAD_STATE_FINISHED || this->myPCB->state==THREAD_STATE_INIT)
	{
		return;
	}
	INTDN();
	PCB::running->state=THREAD_STATE_BLOCKED;
	this->myPCB->waitingForMe.insertFront(PCB::running);
	INTEN();
	dispatch();
}

ID Thread::getId()
{
	return myPCB->PID;
}

ID Thread::getRunningId()
{
	return PCB::running->PID;
}

Thread* Thread::getThreadById(ID id)
{
	PCB* p=PCB::getPCBByID(id);
	if(p!=NULL)
	{
		return p->myThread;
	}
	return NULL;
}

void dispatch ()
{
	//INTDN();
	onDemand=1;
	timerISR();
	//INTEN();
}

Thread* Thread::clone() const
{
	error("Thread clone");
	INTDN();
	Thread* t=new Thread;
	INTEN();
	return t;
}
