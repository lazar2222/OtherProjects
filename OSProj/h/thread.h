#ifndef _thread_h_
#define _thread_h_

typedef unsigned long StackSize; 
typedef unsigned int Time; // time, x 55ms
typedef int ID;

const StackSize defaultStackSize = 4096; 
const Time defaultTimeSlice = 2; // default = 2*55ms 

class PCB; // Kernel's implementation of a user's thread 

class Thread 
{ 
public: 

	void start(); 
	void waitToComplete(); 
	virtual ~Thread();
	ID getId();
	
	static ID getRunningId(); 
	static Thread * getThreadById(ID id);
	
	static ID fork();
	static void exit();
	static void waitForForkChildren();

	virtual Thread* clone() const;

protected: 

	friend class PCB; 
	Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run() {}

private:
	PCB* myPCB;
};

void dispatch ();

#endif
