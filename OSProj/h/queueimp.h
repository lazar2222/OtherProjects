#ifdef TYPE
#ifdef TYPEN

#define CONCAT(a, b) CONCAT_(a, b)
#define CONCAT_(a, b) a ## b

#include "util.h"
#include "logger.h"
#include "queue.h"

    CONCAT(queue_,TYPEN)::CONCAT(queue_,TYPEN)()
	{
		head=NULL;
		tail=NULL;
		size=0;
	}

    CONCAT(queue_,TYPEN)::~CONCAT(queue_,TYPEN)()
	{
		while(head!=NULL)
		{
			warning("Proceses left in queue");
			remove();
		}
	}

    CONCAT(queue_,TYPEN)::listNode* CONCAT(queue_,TYPEN)::newListNode(TYPE t)
	{
    	INTDN();
		CONCAT(queue_,TYPEN)::listNode* r=new CONCAT(queue_,TYPEN)::listNode;
		INTEN();
		if(r==NULL)
		{
			panic("No memory for queue node",RETURN_CODE_OUTOFMEMORY);
		}
		r->value=t;
		r->next=NULL;
		r->prev=NULL;
		return r;
	}

    int CONCAT(queue_,TYPEN)::empty()
    {
        return head==NULL;
    }

    void CONCAT(queue_,TYPEN)::insert(TYPE t)
    {
        listNode* n=newListNode(t);
        if(empty())
        {
            head=n;
            tail=n;
        }
        else
        {
            tail->next=n;
            n->prev=tail;
            tail=n;
        }
        size++;
    }

    TYPE CONCAT(queue_,TYPEN)::peek()
    {
        if(empty()){return NULL;}
        return head->value;
    }

    TYPE CONCAT(queue_,TYPEN)::remove()
    {
    	if(empty()){return NULL;}
        if(head==tail)
        {
            listNode* t=head;
            TYPE r=t->value;
            head=NULL;
            tail=NULL;
            INTDN();
            delete t;
            INTEN();
            size--;
            return r;
        }
        else
        {
            listNode* t=head;
            head=t->next;
            head->prev = NULL;
            TYPE r=t->value;
            INTDN();
            delete t;
            INTEN();
            size--;
            return r;
        }

    }

    void CONCAT(queue_,TYPEN)::removeNode(listNode* n)
	{
		if(head==n && tail==n)
		{
			head=NULL;
			tail=NULL;
			INTDN();
			delete n;
			INTEN();
			size--;
			return;

		}
		if(n->next==NULL)
		{
			tail=n->prev;
			tail->next=NULL;
		}
		else
		{
			n->next->prev=n->prev;
		}
		if(n->prev==NULL)
		{
			head=n->next;
			head->prev=NULL;
		}
		else
		{
			n->prev->next=n->next;
		}
		INTDN();
		delete n;
		INTEN();
		size--;
	}

#endif
#endif


