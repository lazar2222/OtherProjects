#ifdef TYPE
#ifdef TYPEN

#define CONCAT(a, b) CONCAT_(a, b)
#define CONCAT_(a, b) a ## b

#include "util.h"
#include "logger.h"
#include "llist.h"

	CONCAT(llist_,TYPEN)::CONCAT(llist_,TYPEN)()
	{
		head=NULL;
	}

	CONCAT(llist_,TYPEN)::~CONCAT(llist_,TYPEN)()
	{
		while(head!=NULL)
		{
			warning("Proceses left in llist");
			pop();
		}
	}

	CONCAT(llist_,TYPEN)::listNode* CONCAT(llist_,TYPEN)::newListNode(TYPE t)
    {
		INTDN();
		CONCAT(llist_,TYPEN)::listNode* r=new CONCAT(llist_,TYPEN)::listNode;
		INTEN();
		if(r==NULL)
		{
			panic("No memory for llist node",RETURN_CODE_OUTOFMEMORY);
		}
		r->value=t;
        r->next=NULL;
        return r;
    }

    void CONCAT(llist_,TYPEN)::insertFront(TYPE t)
    {
    	listNode* node=newListNode(t);
        node->next=head;
        head=node;
    }

    TYPE CONCAT(llist_,TYPEN)::top()
	{
		if(head==NULL){return NULL;}
		return head->value;
	}

    void CONCAT(llist_,TYPEN)::pop()
	{
		if(head!=NULL)
		{
			listNode* t=head;
			head=head->next;
			INTDN();
			delete t;
			INTEN();
		}
	}

    TYPE CONCAT(llist_,TYPEN)::getPredicate(int (*fun)(TYPE,void*),void* par)
	{
		listNode* node=head;
		while(node!=NULL)
		{
			if(fun(node->value,par))
			{
				return node->value;
			}
			node=node->next;
		}
		return NULL;
	}

    void CONCAT(llist_,TYPEN)::removePredicate(int (*fun)(TYPE,void*),void* par)
	{
		if(head==NULL){return;}
		listNode* tmp=head;
		listNode* lhead=head;
		if(fun(lhead->value,par))
		{
			lhead=lhead->next;
			INTDN();
			delete tmp;
			INTEN();
			return;
		}
		lhead=lhead->next;
		while(lhead!=NULL)
		{
			if(fun(lhead->value,par))
			{
				tmp->next=lhead->next;
				INTDN();
				delete lhead;
				INTEN();
				return;
			}

			tmp=lhead;
			lhead=lhead->next;
		}
	}

    int CONCAT(llist_,TYPEN)::len()
	{
		int cnt=0;
		listNode* node=head;
		while(node!=NULL)
		{
			cnt++;
			node=node->next;
		}
		return cnt;
	}

#endif
#endif
