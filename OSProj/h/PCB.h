#ifndef _PCB_H_
#define _PCB_H_

#include "thread.h"
#include "util.h"

#define TYPE PCB*
#define TYPEN PCBp
#include "llist.h"
#include "queue.h"
#undef TYPEN
#undef TYPE

#define THREAD_STATE_INIT 0
#define THREAD_STATE_READY 1
#define THREAD_STATE_BLOCKED 2
#define THREAD_STATE_FINISHED 3
#define THREAD_STATE_WAITINGALLOC 4

#define MAX_MEMORY 65540L
#define MIN_MEMORY 128L

class PCB
{
public:
	PCB(Thread* mt=NULL,StackSize ss=defaultStackSize,Time ts=defaultTimeSlice);
	~PCB();
	int tryAllocate();
	void deallocate();

	ID PID;
	Thread* myThread;
	StackSize stackSize;
	Time timeSlice;

	unsigned far* EOS;
	unsigned sSeg;
	unsigned sp;
	unsigned bp;
	char state;
	llist_PCBp waitingForMe;
	llist_PCBp myChildren;
	int semReturn;
	int forkReturn;


	static PCB* getPCBByID(ID id);
	static void removePCBByID(ID id);
	static int PCBIDPredicate(PCB* p,void* idp);
	static void wrapper();
	static void idle();
	static PCB* setupIdleThread();
	static void rerunAllocator();
	static PCB* running;
	static PCB* oldRunning;
	static llist_PCBp allProc;
	static queue_PCBp allocatorQueue;
	static PCB* idleThread;
	static PCB* childThread;

private:
	static ID nextID;
};

void interrupt walkStack();

#endif
