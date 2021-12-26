#include <iostream.h>

#include "userint.h"
#include "thread.h"
#include "schedule.h"
#include "util.h"
#include "logger.h"
#include "pcb.h"
#include "int.h"
#include "KernelS.h"
#include "ivte.h"

class MainThread:public Thread
{
public:
	MainThread(int c,char** v):Thread(defaultStackSize,defaultTimeSlice),argc(c),argv(v)
	{
		ret=0;
	}
	~MainThread(){waitToComplete();}
	int argc;
	char** argv;
	int ret;
	virtual Thread* clone() const{return new MainThread(argc,argv);}
protected: virtual void run(){ret=userMain(argc,argv);}
};

int main(int argc,char* argv[])
{
	//kernel init
	INTDN();

	//set up idle Thread
	PCB::idleThread=PCB::setupIdleThread();

	//create PCB for main thread
	PCB* kernelThread=new PCB();
	if(kernelThread==NULL)
	{
		panic("No memory for kernel thread PCB",RETURN_CODE_OUTOFMEMORY);
	}


	kernelThread->state=THREAD_STATE_READY;
	PCB::running=kernelThread;

	//setup IVTP
	initIVTP();

	INTEN();

	MainThread* mt=new MainThread(argc,argv);
	mt->start();
	mt->waitToComplete();
	//int userreturn=userMain(argc,argv);
	int userreturn=mt->ret;
	delete mt;

	//forcequit remaining threads


	//kernel release
	INTDN();

	//ensure All events are cleared
	if(IVTEntry::entries!=NULL)
	{
		for(int i=0;i<256;i++)
		{
			if(IVTEntry::entries[i]!=NULL)
			{
				IVTEntry::entries[i]->release();
			}
		}
	}

	//delte idle Thread
	PCB::idleThread->deallocate();
	delete PCB::idleThread;
	PCB::idleThread=NULL;

	//delete main thread PCB
	delete kernelThread;
	delete KernelSem::asp;

	//release IVTP
	releaseIVTP();

	INTEN();

	return userreturn;
}


