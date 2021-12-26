#include "semaphor.h"
#include "KernelS.h"
#include "util.h"
#include "logger.h"

Semaphore::Semaphore(int init)
{
	INTDN();
	myImpl=new KernelSem(init,this);
	INTEN();
	if(myImpl==NULL)
	{
		panic("No memory for KernelSem",RETURN_CODE_OUTOFMEMORY);
	}
}

Semaphore::~Semaphore()
{
	//probably release everyone
	INTDN();
	delete myImpl;
	INTEN();
}

int Semaphore::wait(Time maxTimeToWait)
{
	return myImpl->wait(maxTimeToWait);
}

void Semaphore::signal()
{
	myImpl->signal();
}

int Semaphore::val() const
{
	return myImpl->value();
}
