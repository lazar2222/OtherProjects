#include "oepq.h"
#include "pcb.h"
#include "logger.h"

overengeneeredProcessQueue::overengeneeredProcessQueue()
{
	signalHead=NULL;
	signalTail=NULL;
	timerHead=NULL;
	timerTail=NULL;
}

overengeneeredProcessQueue::~overengeneeredProcessQueue()
{
	while(!emptySignal())
	{
		warning("Proceses left in OEPQ");
		popSignal();
	}
}

overengeneeredProcessQueue::oepqNode* overengeneeredProcessQueue::newListNode(PCB* p, Time t)
{
	INTDN();
	oepqNode* n=new oepqNode;
	INTEN();
	if(n==NULL)
	{
		panic("No memory for oepq node",RETURN_CODE_OUTOFMEMORY);
	}
	n->value=p;
	n->timeout=t;
	n->signalNext=NULL;
	n->signalPrev=NULL;
	n->timerNext=NULL;
	n->timerPrev=NULL;
	return n;
}

void overengeneeredProcessQueue::insertSignal(PCB* p)
{
	insertSignal(newListNode(p,0));
}

void overengeneeredProcessQueue::insertTimer(PCB* p, Time t)
{
	insertTimer(newListNode(p,t));
}

void overengeneeredProcessQueue::insertSignal(oepqNode* n)
{
	if(signalTail==NULL)
	{
		signalHead=n;
		signalTail=n;
		return;
	}
	signalTail->signalNext=n;
	n->signalPrev=signalTail;
	signalTail=n;
}

void overengeneeredProcessQueue::insertTimer(oepqNode* n)
{
	if(timerTail==NULL)
	{
		timerTail=n;
		timerHead=n;
		insertSignal(n);
		return;
	}
	oepqNode* tmp=timerHead;
	while(tmp != NULL && n->timeout>=tmp->timeout)
	{
		n->timeout-=tmp->timeout;
		tmp=tmp->timerNext;
	}
	if(tmp==NULL)
	{
		timerTail->timerNext=n;
		n->timerPrev=timerTail;
		timerTail=n;
	}
	else if(tmp==timerHead)
	{
		timerHead->timerPrev=n;
		n->timerNext=timerHead;
		timerHead=n;

		n->timerNext->timeout-=n->timeout;
	}
	else
	{
		n->timerNext=tmp;
		n->timerPrev=tmp->timerPrev;
		tmp->timerPrev=n;
		n->timerPrev->timerNext=n;

		n->timerNext->timeout-=n->timeout;
	}
	insertSignal(n);
}

PCB* overengeneeredProcessQueue::topTimer()
{
	if(timerHead==NULL){return NULL;}
	return timerHead->value;
}

PCB* overengeneeredProcessQueue::topSignal()
{
	if(signalHead==NULL){return NULL;}
	return signalHead->value;
}

void overengeneeredProcessQueue::popTimer()
{
	if(timerHead==NULL){return;}
	oepqNode* n=timerHead;
	timerHead=n->timerNext;
	if(timerHead==NULL){timerTail=NULL;}
	else 
	{
		timerHead->timerPrev = NULL;
	}
	removeSignal(n);
	INTDN();
	delete n;
	INTEN();
}

void overengeneeredProcessQueue::popSignal()
{
	if(signalHead==NULL){return;}
	oepqNode* n=signalHead;
	signalHead=n->signalNext;
	if(signalHead==NULL){signalTail=NULL;}
	else
	{
		signalHead->signalPrev = NULL;
	}
	removeTimer(n);
	INTDN();
	delete n;
	INTEN();
}

void overengeneeredProcessQueue::removeTimer(oepqNode* n)
{
	if(n->timerNext==NULL && n->timerPrev==NULL)
	{
		if(timerHead==n)
		{
			timerHead=NULL;
			timerTail=NULL;
		}
		return;
	}
	if(n->timerNext==NULL)
	{
		timerTail=n->timerPrev;
		timerTail->timerNext=NULL;
	}
	else
	{
		n->timerNext->timerPrev=n->timerPrev;
		n->timerNext->timeout += n->timeout;
	}
	if(n->timerPrev==NULL)
	{
		timerHead=n->timerNext;
		timerHead->timerPrev=NULL;
	}
	else
	{
		n->timerPrev->timerNext=n->timerNext;
	}
}

void overengeneeredProcessQueue::removeSignal(oepqNode* n)
{
	if(n->signalNext==NULL && n->signalPrev==NULL)
	{
		if(signalHead==n)
		{
			signalHead=NULL;
			signalTail=NULL;
		}
		return;
	}
	if(n->signalNext==NULL)
	{
		signalTail=n->signalPrev;
		signalTail->signalNext=NULL;
	}
	else
	{
		n->signalNext->signalPrev=n->signalPrev;
	}
	if(n->signalPrev==NULL)
	{
		signalHead=n->signalNext;
		signalHead->signalPrev=NULL;
	}
	else
	{
		n->signalPrev->signalNext=n->signalNext;
	}
}

int overengeneeredProcessQueue::emptyTimer()
{
	return timerHead==NULL;
}


int overengeneeredProcessQueue::emptySignal()
{
	return signalHead==NULL;
}
