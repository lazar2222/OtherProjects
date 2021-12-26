#ifndef _KERNELSEM_H_
#define _KERNELSEM_H_

#include "semaphor.h"
#include "pcb.h"
#include "oepq.h"

#define TYPE KernelSem*
#define TYPEN KernelSemp
#include "llist.h"
#undef TYPEN
#undef TYPE

class KernelSem
{
public:
	KernelSem(int v,Semaphore* s);
	~KernelSem();
	int wait (Time maxTimeToWait);
	void signal();
	int value () const; // Returns the current value of the semaphore
	Semaphore* mySem;
	int val;
	overengeneeredProcessQueue blockedHere;

	static llist_KernelSemp* allSem();
	static llist_KernelSemp* asp;
	static int KSPredicate(KernelSem* a,void* b);
};

#endif
