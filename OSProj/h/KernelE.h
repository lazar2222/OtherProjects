#ifndef _KERNELE_H_
#define _KERNELE_H_

#include "event.h"
#include "PCB.h"

class KernelEv
{
public:
	KernelEv (IVTNo i,Event* e);
	~KernelEv ();
	void wait ();
	void signal();
	IVTNo ivtno;
	PCB* owner;
	int val;
	Event* myEv;
};

#endif
