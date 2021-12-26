#include <string.h>
#include <stdlib.h>

#define SSTEP 10

char* readLine()
{
    while(getchar()!='\n'){}
    char* r=malloc(SSTEP*sizeof(char));
    char c;
    int br=0;
    while(true)
    {
        c=getchar();
        if(c=='\n' || c=='\r'){break;}
        r[br++]=c;
        if(br%SSTEP==0)
        {
            r=realloc(r,((br/SSTEP)+1)*SSTEP*sizeof(char));
        }

    }
    r[br++]='\0';
    r=realloc(r,br*sizeof(char));
    return r;
}

void smartDouble(double d)
{
    int size=snprintf(NULL, 0, "%f", d);
    char* buf=malloc((size+1)*sizeof(char));
    sprintf(buf,"%f",d);
    int j=strlen(buf);
    j--;
    while(buf[j]=='0'){j--;}
    if(buf[j]!='.'){j++;}
    buf[j]='\0';
    printf("%s",buf);
    free(buf);
}
