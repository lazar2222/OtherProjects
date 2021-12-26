#ifndef _OEPQ_H_
#define _OEPQ_H_

typedef unsigned int Time;
class PCB;

class overengeneeredProcessQueue
{
public:

	overengeneeredProcessQueue();
	~overengeneeredProcessQueue();

	struct oepqNode
	{
		PCB* value;
		Time timeout;
		oepqNode* signalNext;
		oepqNode* signalPrev;
		oepqNode* timerNext;
		oepqNode* timerPrev;
	};


	static oepqNode* newListNode(PCB* p,Time t);

	void insertSignal(PCB* p);
	void insertTimer(PCB* p,Time t);
	void insertSignal(oepqNode* n);
	void insertTimer(oepqNode* n);
	PCB* topTimer();
	PCB* topSignal();
	void popTimer();
	void popSignal();
	void removeTimer(oepqNode* n);
	void removeSignal(oepqNode* n);
	int emptyTimer();
	int emptySignal();

	oepqNode* signalHead;
	oepqNode* signalTail;
	oepqNode* timerHead;
	oepqNode* timerTail;

};

#endif
