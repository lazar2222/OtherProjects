#ifndef _IVTE_H_
#define _IVTE_H_

#include "util.h"

typedef unsigned char IVTENO;
typedef void interrupt (*IVTEISR)(...);

class KernelEv;

class IVTEntry
{
public:
	IVTEntry(IVTENO en,IVTEISR nISR);
	IVTEntry(IVTENO en,IVTEISR nISR,int reg);
	~IVTEntry();

	IVTENO entry;
	IVTEISR newISR;
	IVTEISR oldISR;
	KernelEv* myEv;

	void signal();
	void jam();
	void release();

	static IVTEntry* get(IVTENO en);
	static void allocateEntries();
	static IVTEntry** entries;

};

#endif
