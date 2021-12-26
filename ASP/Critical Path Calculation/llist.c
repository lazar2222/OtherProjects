#include <stdlib.h>

#ifdef TYPE
#ifdef TYPEN

#define CONCAT(a, b) CONCAT_(a, b)
#define CONCAT_(a, b) a ## b

    struct CONCAT(listNode_, TYPEN)
    {
        TYPE value;
        struct CONCAT(listNode_, TYPEN)* next;
    };

    struct CONCAT(listNode_, TYPEN)* CONCAT(newListNode_, TYPEN)()
    {
        struct CONCAT(listNode_, TYPEN)* r=(CONCAT(listNode_, TYPEN)*)malloc(sizeof(struct CONCAT(listNode_, TYPEN)));
        r->next=NULL;
        return r;
    }

    struct CONCAT(listNode_, TYPEN)* CONCAT(insertFront_, TYPEN)(struct CONCAT(listNode_, TYPEN)* head,struct CONCAT(listNode_, TYPEN)* node)
    {
        node->next=head;
        return node;
    }

    struct CONCAT(listNode_, TYPEN)* CONCAT(insertAfter_, TYPEN)(struct CONCAT(listNode_, TYPEN)* head,struct CONCAT(listNode_, TYPEN)* node)
    {
        if(head==NULL)
        {
            return node;
        }
        node->next=head->next;
        head->next=node;
        return head;
    }

    struct CONCAT(listNode_, TYPEN)* CONCAT(insertBefore_, TYPEN)(struct CONCAT(listNode_, TYPEN)* head,struct CONCAT(listNode_, TYPEN)* node)
    {
        head=CONCAT(insertAfter_, TYPEN)(head,node);
        TYPE t=head->value;
        head->value=node->value;
        node->value=t;
        return head;
    }

    struct CONCAT(listNode_, TYPEN)* CONCAT(insertOrd_, TYPEN)(struct CONCAT(listNode_, TYPEN)* head,struct CONCAT(listNode_, TYPEN)* node,int (*fun)(TYPE ,TYPE ))
    {
        if(head==NULL || fun(node->value,head->value)==1){return CONCAT(insertBefore_, TYPEN)(head,node);}
        struct CONCAT(listNode_, TYPEN)* t=head;
        while(t->next!=NULL && fun(node->value,t->value)!=1)
        {
            t=t->next;
        }
        if(fun(node->value,t->value)==1){CONCAT(insertBefore_, TYPEN)(t,node);return head;}
        else{CONCAT(insertAfter_, TYPEN)(t,node); return head;}
    }

    void CONCAT(iter_, TYPEN)(struct CONCAT(listNode_, TYPEN)* head,void (*fun)(TYPE))
    {
        while(head!=NULL)
        {
            fun(head->value);
            head=head->next;
        }
    }

    void CONCAT(iter1_, TYPEN)(struct CONCAT(listNode_, TYPEN)* head,void (*fun)(TYPE , void*),void* a)
    {
        while(head!=NULL)
        {
            fun(head->value,a);
            head=head->next;
        }
    }

    void CONCAT(iter1f_, TYPEN)(struct CONCAT(listNode_, TYPEN)* head,void (*fun)(TYPE , void*,bool),void* a)
    {
        while(head!=NULL)
        {
            fun(head->value,a,head->next==NULL);
            head=head->next;
        }
    }

    void CONCAT(iter2_, TYPEN)(struct CONCAT(listNode_, TYPEN)* head,void (*fun)(TYPE , void* , void*),void* a,void* b)
    {
        while(head!=NULL)
        {
            fun(head->value,a,b);
            head=head->next;
        }
    }

    void CONCAT(del_, TYPEN)(struct CONCAT(listNode_, TYPEN)* head)
    {
        while(head!=NULL)
        {
            struct CONCAT(listNode_, TYPEN)* t=head;
            head=head->next;
            free(t);
        }
    }

    struct CONCAT(listNode_, TYPEN)* CONCAT(remove_, TYPEN)(struct CONCAT(listNode_, TYPEN)* head,void* a,int (*fun)(TYPE,void*))
    {
        if(head==NULL){return NULL;}
        struct CONCAT(listNode_, TYPEN)* p=head;
        struct CONCAT(listNode_, TYPEN)* tmp=head;
        if(fun(head->value,a))
        {
            head=head->next;
            free(tmp);
            return head;
        }
        head=head->next;
        while(head!=NULL)
        {
            if(fun(head->value,a))
            {
                tmp->next=head->next;
                free(head);
                return p;
            }

            tmp=head;
            head=head->next;
        }
        return p;
    }

    struct CONCAT(listNode_, TYPEN)* CONCAT(copy_, TYPEN)(struct CONCAT(listNode_, TYPEN)* head)
    {
        struct CONCAT(listNode_, TYPEN)* res=NULL;
        struct CONCAT(listNode_, TYPEN)* t=NULL;
        while(head!=NULL)
        {
            struct CONCAT(listNode_, TYPEN)* tmp=CONCAT(newListNode_, TYPEN)();
            tmp->value=head->value;
            t=CONCAT(insertAfter_, TYPEN)(t,tmp);
            if(res==NULL)
            {
                res=t;
            }
            if(t->next!=NULL)
            {
                t=t->next;
            }
            head=head->next;
        }
        return res;
    }

#endif
#endif
