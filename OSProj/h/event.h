#ifndef _event_h_
#define _event_h_

#include "IVTE.h"

#define PREPAREENTRY(ino,cold)\
void interrupt ISR##ino(...)\
{\
	if(cold==1 && IVTEntry::get(ino)->oldISR!=NULL)\
	{\
		IVTEntry::get(ino)->oldISR();\
	}\
	IVTEntry::get(ino)->signal();\
}\
IVTEntry IVTE##ino(ino,ISR##ino);

typedef unsigned char IVTNo;

class KernelEv;

class Event 
{
public:
	Event (IVTNo ivtNo);
	~Event ();
	void wait ();
	
protected:
	friend class KernelEv;
	void signal(); // can call KernelEv
	
private:
	KernelEv* myImpl;
};

#endif
