#include "IVTE.h"
#include "util.h"
#include "KernelE.h"
#include "logger.h"


IVTEntry** IVTEntry::entries = NULL;

IVTEntry::IVTEntry(IVTENO en, IVTEISR nISR) {
	entry=en;
	newISR=nISR;
	oldISR=NULL;
	myEv=NULL;
	if(entries==NULL){allocateEntries();}
	entries[en]=this;
}

IVTEntry::~IVTEntry()
{
	release();
}
void IVTEntry::signal() {
	myEv->signal();
}

IVTEntry* IVTEntry::get(IVTENO en)
{
	if(entries==NULL){allocateEntries();}
	return entries[en];
}

void IVTEntry::jam()
{
	REALINTDN();
	oldISR=getvect(entry);
	if(oldISR==NULL)
	{
		warning("oldISR is NULL");
	}
	setvect(entry,newISR);
	REALINTEN();
}

void IVTEntry::release()
{
	REALINTDN();
	if(oldISR!=NULL)
	{
		setvect(entry,oldISR);
		oldISR=NULL;
	}
	REALINTEN();
}


void IVTEntry::allocateEntries()
{
	INTDN();
	entries=new IVTEntry*[256];
	INTEN();
	for(int i=0;i<256;i++)
	{
		entries[i]=NULL;
	}
}
