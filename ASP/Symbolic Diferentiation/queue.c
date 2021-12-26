#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#ifdef TYPE
#ifdef TYPEN

#ifndef NOLIST
    #include "llist.c"
#endif

#define CONCAT(a, b) CONCAT_(a, b)
#define CONCAT_(a, b) a ## b


    typedef struct CONCAT(listNode_, TYPEN) CONCAT(queue_, TYPEN);

    bool CONCAT(emptyQ_, TYPEN)(CONCAT(queue_, TYPEN)** s)
    {
        return *s==NULL;
    }

    void CONCAT(insert_, TYPEN)(CONCAT(queue_, TYPEN)** s,TYPE v)
    {
        CONCAT(queue_, TYPEN)* n=CONCAT(newListNode_, TYPEN)();
        n->value=v;
        if(CONCAT(emptyQ_, TYPEN)(s))
        {
            *s=n;
            n->next=n;
        }
        else
        {
            CONCAT(queue_, TYPEN)* t=(*s)->next;
            (*s)->next=n;
            n->next=t;
            *s=n;
        }
    }

    TYPE CONCAT(peek_, TYPEN)(CONCAT(queue_, TYPEN)** s)
    {
        assert(!CONCAT(emptyQ_, TYPEN)(s));
        return (*s)->next->value;
    }

    TYPE CONCAT(delete_, TYPEN)(CONCAT(queue_, TYPEN)** s)
    {
        assert(!CONCAT(emptyQ_, TYPEN)(s));
        if((*s)==(*s)->next)
        {
            CONCAT(queue_, TYPEN)* t=*s;
            TYPE r=t->value;
            *s=NULL;
            free(t);
            return r;
        }
        else
        {
            CONCAT(queue_, TYPEN)* t=(*s)->next;
            (*s)->next=t->next;
            TYPE r=t->value;
            free(t);
            return r;
        }

    }
#endif
#endif


