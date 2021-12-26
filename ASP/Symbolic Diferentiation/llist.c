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
        struct CONCAT(listNode_, TYPEN)* r=malloc(sizeof(struct CONCAT(listNode_, TYPEN)));
        return r;
    }

#endif
#endif
