#include "userint.h"
#include "util.h"
#include "thread.h"
#include "iostream.h"

#define N 200

class Thread1: public Thread
{
public:
	Thread1():Thread(64L,defaultTimeSlice){num=0;};
	~Thread1(){waitToComplete();};
	virtual Thread* clone()const {return new Thread1;};
	int num;
protected:
	virtual void run();
};

volatile int task;

void Thread1::run()
{
	task++;
	INTDN();
	cout<<task<<endl;
	INTEN();
}

void tick()
{

}

int userMain(int argc,char* argv[])
{
	Thread1** t=new Thread1*[N];
	for(int i=0;i<N;i++)
	{
		t[i]=new Thread1();
		t[i]->num=i;
	}
	for(i=0;i<N;i++)
	{
		t[i]->start();
	}
	for(i=0;i<N;i++)
	{
		t[i]->waitToComplete();
	}
	for(i=0;i<N;i++)
	{
		delete t[i];
	}
	delete [] t;
	return 0;
}
