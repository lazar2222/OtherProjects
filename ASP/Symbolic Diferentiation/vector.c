#include <stdlib.h>
#include <string.h>

#ifdef TYPE
#ifdef TYPEN

#define VSTEP 10

#define CONCAT(a, b) CONCAT_(a, b)
#define CONCAT_(a, b) a ## b

    struct CONCAT(svector_, TYPEN)
    {
        TYPE* vector;
        long tsize;
        long size;
    };

    typedef struct CONCAT(svector_, TYPEN) CONCAT(vector_, TYPEN);

    CONCAT(vector_, TYPEN)* CONCAT(initVector_, TYPEN) ()
    {
        CONCAT(vector_, TYPEN)* r=malloc(sizeof(CONCAT(vector_, TYPEN)));
        r->vector=malloc(VSTEP*sizeof(TYPE));
        memset(r->vector,0,VSTEP*sizeof(TYPE));
        r->tsize=VSTEP;
        r->size=0;
        return r;
    }

    void CONCAT(freeVector_, TYPEN) (CONCAT(vector_, TYPEN)* v)
    {
        free(v->vector);
        free(v);
    }

    void CONCAT(resize_, TYPEN) (CONCAT(vector_, TYPEN)* v,long nsize)
    {
        v->vector=realloc(v->vector,nsize*sizeof(TYPE));
        if(nsize>(v->tsize))
        {
            memset((v->vector)+(v->tsize),0,nsize-(v->tsize));
        }
        v->tsize=nsize;
    }

    long CONCAT(len_, TYPEN) (CONCAT(vector_, TYPEN)* v)
    {
        return v->size;
    }

    void CONCAT(set_, TYPEN)(CONCAT(vector_, TYPEN)* v,long pos,TYPE val)
    {
        if(pos>=v->tsize)
        {
            CONCAT(resize_, TYPEN)(v,pos+VSTEP);
        }
        v->vector[pos]=val;
        if(pos>=v->size)
        {
            v->size=pos+1;
        }
    }

    TYPE CONCAT(get_, TYPEN) (CONCAT(vector_, TYPEN)* v,long pos)
    {
        if(pos<v->size)
        {
            return v->vector[pos];
        }
        else
        {
            return 0;
        }
    }

#endif
#endif
