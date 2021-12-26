#include <malloc.h>
#include "PCB.h"
#include "logger.h"
#include "schedule.h"
#include "iostream.h"

ID PCB::nextID = 1;
PCB* PCB::running = NULL;
PCB* PCB::oldRunning = NULL;
llist_PCBp PCB::allProc;
queue_PCBp PCB::allocatorQueue;
PCB* PCB::idleThread=NULL;
PCB* PCB::childThread=NULL;

unsigned pss;
unsigned psp;
unsigned pbp;

PCB::PCB(Thread* mt, StackSize ss, Time ts) {
	PID = nextID++;
	myThread = mt;
	if(ss>MAX_MEMORY)
	{
		ss=MAX_MEMORY;
		warning("Thread requested stackSize larger than limit, quietly reducing it");
	}
	if(ss<MIN_MEMORY)
	{
		ss=MIN_MEMORY;
		warning("Thread requested stackSize smaller than limit, quietly increasing it");
	}
	stackSize = ss;
	timeSlice = ts;
	EOS=NULL;
	sSeg=NULL;
	sp=NULL;
	bp=NULL;
	state=THREAD_STATE_INIT;
	allProc.insertFront(this);
	forkReturn=0;
	semReturn=0;
}

PCB::~PCB() {
	removePCBByID(this->PID);
}

PCB* PCB::getPCBByID(ID id) {
	return allProc.getPredicate(PCBIDPredicate, &id);
}

void PCB::removePCBByID(ID id) {
	allProc.removePredicate(PCBIDPredicate, &id);
}

int PCB::PCBIDPredicate(PCB* p, void* idp) {
	int id = *((int*) idp);
	return p->PID == id;
}

int PCB::tryAllocate()
{
	StackSize stackindex=stackSize/sizeof(unsigned);
	INTDN();
	EOS=(unsigned far*)farmalloc(stackSize);
	//EOS=new unsigned[stackindex];
	INTEN();
	if(EOS==NULL)
	{
		warning("Cant allocate stack");
		return 0;
	}
	EOS[stackindex-1]=0;
	EOS[stackindex-2]=0x200;
	EOS[stackindex-3]=FP_SEG(PCB::wrapper);
	EOS[stackindex-4]=FP_OFF(PCB::wrapper);
	EOS[stackindex-13]=FP_OFF(EOS+stackindex-1);
	sSeg=FP_SEG(EOS+stackindex-13);
	sp=FP_OFF(EOS+stackindex-13);
	bp=sp;

	return 1;
}

void PCB::deallocate()
{
	INTDN();
	farfree(EOS);
	//delete [] EOS;
	//cout<<"dealloc"<<endl;
	INTEN();
	EOS=NULL;
	PCB* p=waitingForMe.top();
	while(p!=NULL)
	{
		waitingForMe.pop();
		p->state=THREAD_STATE_READY;
		Scheduler::put(p);
		p=waitingForMe.top();
	}
}

void PCB::wrapper()
{
	//debug("Starting Wrapper");
	running->myThread->run();
	running->state=THREAD_STATE_FINISHED;
	//deallocate stack after context switch
	dispatch();
}

void PCB::idle()
{
	while(1){}
}

PCB* PCB::setupIdleThread()
{
	INTDN();
	PCB* it=new PCB(NULL,256,1);
	INTEN();
	if(it==NULL)
	{
		panic("No memory for idle thread PCB",RETURN_CODE_OUTOFMEMORY);
	}
	it->state=THREAD_STATE_BLOCKED;
	if(!(it->tryAllocate()))
	{
		panic("No memory for idle thread stack",RETURN_CODE_OUTOFMEMORY);
	}
	StackSize stackindex=it->stackSize/sizeof(unsigned);
	it->EOS[stackindex-3]=FP_SEG(PCB::idle);
	it->EOS[stackindex-4]=FP_OFF(PCB::idle);
	return it;
}

void PCB::rerunAllocator()
{
	queue_PCBp::listNode* n=PCB::allocatorQueue.head;
	while(n!=NULL)
	{
		if(n->value->tryAllocate())
		{
			n->value->state=THREAD_STATE_READY;
			Scheduler::put(n->value);
			queue_PCBp::listNode* t=n;
			n=n->next;
			PCB::allocatorQueue.removeNode(t);
		}else
		{
			n=n->next;
		}
	}
}

void interrupt walkStack()
{
	PCB* p=PCB::childThread;
	//cout<<"E"<<p->EOS<<" "<<"RE"<<PCB::running->EOS<<endl;
	asm{
		mov pss, ss
		mov psp, sp
		mov pbp, bp
	}

	StackSize stackindex=p->stackSize/sizeof(unsigned);
	for(int i=0;i<stackindex;i++)
	{
		p->EOS[i]=PCB::running->EOS[i];
	}

	unsigned far* fbp=(unsigned far*)MK_FP(pss,pbp);
	unsigned far* fsp=(unsigned far*)MK_FP(pss,psp);

	unsigned far* mfbp=(fbp-PCB::running->EOS)+p->EOS;
	unsigned far* mfsp=(fsp-PCB::running->EOS)+p->EOS;

	p->sSeg=FP_SEG(mfsp);
	p->sp=FP_OFF(mfsp);
	p->bp=FP_OFF(mfbp);
	//cout<<"E"<<p->EOS<<" "<<"RE"<<PCB::running->EOS<<endl;
	//cout<<"MFBP"<<mfbp<<" "<<"FBP"<<fbp<<endl;
	//cout<<"MFSP"<<mfsp<<" "<<"FSP"<<fsp<<endl;
	//cout<<(p->EOS-PCB::running->EOS)<<endl;
	//cout<<mfbp-p->EOS<<endl;
	//cout<<fbp-PCB::running->EOS<<endl;

	while(*mfbp!=0)
	{
		*mfbp=*mfbp+((p->EOS-PCB::running->EOS)*sizeof(unsigned));
		mfbp=(unsigned far*)MK_FP(FP_SEG(mfbp),*mfbp);
	}
	//for(i=0;i<stackindex;i++)
	//{
	//	cout<<i<<" "<<p->EOS+i<<" "<<p->EOS[i]<<" "<<PCB::running->EOS[i]<<endl;
	//}
}
