#include "event.h"
#include "IVTE.h"
#include "KernelE.h"
#include "logger.h"

Event::Event(IVTNo ivtNo)
{
	INTDN();
	myImpl=new KernelEv(ivtNo,this);
	INTEN();
	if(myImpl==NULL)
	{
		panic("No memory for KernelEv",RETURN_CODE_OUTOFMEMORY);
	}
	IVTEntry::get(ivtNo)->myEv=myImpl;
	IVTEntry::get(ivtNo)->jam();
}

Event::~Event()
{
	IVTEntry::get(myImpl->ivtno)->release();
	//probably release everyone
	INTDN();
	delete myImpl;
	INTEN();
}

void Event::wait()
{
	myImpl->wait();
}

void Event::signal()
{
	//myImpl->signal();
	error("Somehow called event.signal");
}
