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


    typedef struct CONCAT(listNode_, TYPEN) CONCAT(stack_, TYPEN);

    bool CONCAT(empty_, TYPEN)(CONCAT(stack_, TYPEN)** s)
    {
        return *s==NULL;
    }

    void CONCAT(push_, TYPEN)(CONCAT(stack_, TYPEN)** s,TYPE v)
    {
        CONCAT(stack_, TYPEN)* n=CONCAT(newListNode_, TYPEN)();
        n->value=v;
        n->next=*s;
        *s=n;
    }

    TYPE CONCAT(top_, TYPEN)(CONCAT(stack_, TYPEN)** s)
    {
        assert(!CONCAT(empty_, TYPEN)(s));
        return (*s)->value;
    }

    TYPE CONCAT(pop_, TYPEN)(CONCAT(stack_, TYPEN)** s)
    {
        assert(!CONCAT(empty_, TYPEN)(s));
        CONCAT(stack_, TYPEN)* x=*s;
        *s=x->next;
        TYPE r=x->value;
        free(x);
        return r;
    }

#endif
#endif
