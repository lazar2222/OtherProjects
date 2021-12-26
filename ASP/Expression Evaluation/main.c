#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXLEN 150
#define VARCNT 30

// Jednostruko ulancana lista
typedef struct listNode
{
    int v;
    struct listNode* next;
} Stack;

Stack* newListNode();

//Stack
void Push(Stack** n,int v);
int Pop(Stack** n);
int Top(Stack** n);
bool Empty(Stack** n);

//Demo Aplikacija
void printMenu();
void handleMenu(char* izraz,int* promenljive);
void IInput(char* izraz);
void Vinput(int* promenljive);
void Eval(char* izraz,int* promenljive);

int main()
{
    char* izraz=(char*) calloc(MAXLEN,sizeof(char));
    int* promenljive=(int*) calloc(VARCNT,sizeof(int));
    izraz[0]='\0';
    while(true)
    {
        printMenu();
        handleMenu(izraz,promenljive);
    }
    return 0;
}

Stack* newListNode()
{
    Stack* nln=(Stack*)calloc(1,sizeof(Stack));
    return nln;
}

void Push(Stack** n,int v)
{
    if(*n==NULL)
    {
        *n=newListNode();
        (*n)->v=v;
        (*n)->next=NULL;
    }
    else
    {
        Stack* nx=(*n);
        *n=newListNode();
        (*n)->v=v;
        (*n)->next=nx;
    }
}

int Pop(Stack** n)
{
    if(!Empty(n))
    {
        Stack* x=*n;
        *n=x->next;
        int r=x->v;
        free(x);
        return r;
    }
    else
    {
        exit(-1);
    }
}

int Top(Stack** n)
{
    if(!Empty(n))
    {
        return (*n)->v;
    }
    else
    {
        exit(-1);
    }

}
bool Empty(Stack** n)
{
    return (*n)==NULL;
}

void printMenu()
{
    printf("\r\n");
    printf("1. Unos izraza\r\n");
    printf("2. Unos vrednosti operanada (default 0)\r\n");
    printf("3. Izracunavanje izraza\r\n");
    printf("9. Kraj rada\r\n");
}

void handleMenu(char* izraz,int* promenljive)
{
int in;
    scanf("%d",&in);
    switch(in)
    {
        case 1:{ IInput(izraz); break;}
        case 2:{ Vinput(promenljive); break;}
        case 3:{ Eval(izraz,promenljive); break;}
        case 9:{free(izraz); free(promenljive);  exit(0); break;}
        default: {printf("Greska: Nepostojeca opcija\r\n");break;}
    }
}

void IInput(char* izraz)
{
    int ss=0;
    bool valid=true;
    bool chare=false;
    while(getchar()!='\n'){}
    fgets(izraz,MAXLEN,stdin);
    for(int i=0;i<MAXLEN;i++)
    {
        if(izraz[i]=='\r' || izraz[i]=='\n' || izraz[i]=='\0'){break;}
        else if(izraz[i]>='A' && izraz[i]<='Z'){ss++;}
        else if (izraz[i]=='+' || izraz[i]=='-' || izraz[i]=='*' || izraz[i]=='/'){ if(ss<2){valid=false;break;} ss--;}
        else if(izraz[i]==' '){}
        else {valid=false;chare=true;break;}
    }
    valid=valid && (ss==1);
    if(!valid)
    {
        izraz[0]='\0';
        printf("Greka: ");
        printf(chare?"Neocekivani karakter\r\n":"Nepravilan izraz\r\n");
    }
}

void Vinput(int* promenljive)
{
    printf("Unesite broj operanada cije vrednosti zelite da podesite:\r\n");
    int n;
    scanf("%d",&n);
    printf("Unesite ime operanda i njegovu vrednost za svaki operand koji zelite da podesite:\r\n");
    for(int i=0;i<n;i++)
    {
        char c[MAXLEN];
        int v;
        scanf("%s %d",c,&v);
        if(c[1]!='\0' || c[0]<'A' || c[0]>'Z'){printf("Greka: Nepravilno ime operanda\r\n");}
        else
        {
            promenljive[c[0]-'A']=v;
        }
    }
}
void Eval(char* izraz,int* promenljive)
{
    Stack* st=NULL;
    Stack** S=&st;
    bool divz=false;
    if(izraz[0]!='\0')
    {
        for(int i=0;i<MAXLEN;i++)
        {
            if(izraz[i]=='\r' || izraz[i]=='\n' || izraz[i]=='\0'){break;}
            else if(izraz[i]>='A' && izraz[i]<='Z')
            {
                Push(S,promenljive[izraz[i]-'A']);
            }
            else if (izraz[i]=='+' || izraz[i]=='-' || izraz[i]=='*' || izraz[i]=='/')
            {
                int a,b;
                b=Pop(S);
                a=Pop(S);
                switch(izraz[i])
                {
                    case '+':{Push(S,a+b); break;}
                    case '-':{Push(S,a-b); break;}
                    case '*':{Push(S,a*b); break;}
                    case '/':{if(b!=0){Push(S,a/b);}else{divz=true;} break;}
                }
            }
            if(divz){break;}
        }
        if(!divz)
        {
            int r=Pop(S);
            if(Empty(S))
            {
                printf("%d\r\n",r);
            }
            else
            {
                printf("Greska: stek machine broke :(\r\n");
            }
        }
        else
        {
            printf("Greska: Deljenje nulom\r\n");
        }
    }
    else
    {
        printf("Greska: Nepostojeci izraz\r\n");
    }
}
