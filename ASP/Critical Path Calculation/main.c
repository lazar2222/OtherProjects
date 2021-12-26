#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// i=3 Inverzna lista susednosti i BFS Tranzitivne zavisnosti

typedef struct sedge
{
    int weight;
    int source;
} edge;

#define TYPE edge
#define TYPEN edge
#include "llist.c"
#undef TYPE
#undef TYPEN
typedef struct listNode_edge listNode_edge;

#define TYPE int
#define TYPEN int
#include "llist.c"
#undef TYPE
#undef TYPEN
typedef struct listNode_int listNode_int;

#define TYPE listNode_int*
#define TYPEN lni
#include "queue.c"
#undef TYPE
#undef TYPEN

#define TYPE int
#define TYPEN int
#define NOLIST
#include "queue.c"
#undef NOLIST
#undef TYPE
#undef TYPEN

typedef struct score
{
    listNode_edge* incidence[30];
    int LUT[30];
    char RLUT[30];
    char op[30];
    int EST[30];
    int LST[30];
    int L[30];
    int Vc;
    int MET;
} core;

void printMenu();
void handleMenu(core* c);
void scan(core* c,FILE* f);
int line(core* cp,FILE* f);
void scandat(core * c);
void printdat(core* c);
int max(int a,int b);
int min(int a,int b);
int idFromName(core* c,char name);
char nameFromId(core* c,int id);
int getWeight(char op);
void initCore(core* c);
void addVertex(core* c,char name,char op);
void addEdge(core* c,int source,int dest,int weight);
void delEdge(core* c,int source,int dest);
int edgecompare(edge e,void* source);
void delVertex(core* c,int id);
void clearCore(core* c);
void printGraph(core* c,FILE* f);
void printedge(edge e,void* cp,void* fp);
void fillCP(core* c);
void CPLEN(core* c);
void allcpBFS(core* c);
void printlistint(int a,void* cp,bool l);
void printsched(core* c);
void transitive(core* c,int s);
int bfs(core* c,int src,int des);
void transitivem(core* c);

int main()
{
    core* c=malloc(sizeof(core));
    initCore(c);
    while(true)
    {
        printMenu(c);
        handleMenu(c);
    }
    return 0;
}

void printMenu()
{
    printf("\r\n");
    printf("1. Unos grafa sa standardnog ulaza\r\n");
    printf("2. Unos grafa iz datoteke\r\n");
    printf("3. Ispis grafa na standardni izlaz\r\n");
    printf("4. Ispis grafa u datoteku\r\n");
    printf("5. Duzina kriticnog puta\r\n");
    printf("6. Ispis kriticnog puta\r\n");
    printf("7. Raspored operacija po kriticnom putu\r\n");
    printf("8. Odredjivanje tranzitivne zavisnosti za neki cvor\r\n");
    printf("9. Kraj rada\r\n");
}

void handleMenu(core* c)
{
    int in;
    if(scanf("%d",&in)==0)
    {
        scanf("%*[^\n]%*c");
        printf("Greska: Nepostojeca opcija\r\n");
        return;
    }
    switch(in)
    {
        case 1:{printf("Unesite kod,prazan red zavrsava unos\n");scan(c,stdin);break;}
        case 2:{scandat(c);break;}
        case 3:{printGraph(c,stdout);break;}
        case 4:{printdat(c);break;}
        case 5:{CPLEN(c);break;}
        case 6:{allcpBFS(c);break;}
        case 7:{printsched(c);break;}
        case 8:{transitivem(c);break;}
        case 9:{clearCore(c);free(c);exit(0);break;}
        default:{printf("Greska: Nepostojeca opcija\r\n"); break;}
    }
}

void scan(core* c,FILE* f)
{
    if(c->Vc!=0){clearCore(c);initCore(c);}
    while(1)
    {
        char ch=fgetc(f);
        if(ch!='\n'){ungetc(ch,f);break;}
    }
    while(1)
    {
        if(line(c,f)==0){break;}
    }
}

int line(core* cp,FILE* f)
{
    int nrr=0;
    char r=-1;
    char a1=-1;
    char a2=-1;
    char op=-1;
    char p1;
    char p2;
    while(1)
    {
        char c=fgetc(f);
        if(c=='\n' || c==EOF)
        {
            if(nrr!=0)
            {
                addVertex(cp,r,op);
                if(a1!=-1)
                {
                    addEdge(cp,idFromName(cp,a1),idFromName(cp,r),getWeight(cp->op[idFromName(cp,a1)]));
                }
                if(a2!=-1)
                {
                    addEdge(cp,idFromName(cp,a2),idFromName(cp,r),getWeight(cp->op[idFromName(cp,a2)]));
                }
                return 1;
            }
            else
            {
                return 0;
            }
        }
        if(c>='a' && c<='z')
        {
            if(op==-1 && (c=='a' || c=='o' || c=='x' || c=='n'))
            {
                p1=fgetc(f);
                p2=fgetc(f);
                if(c=='a' && p1=='n' && p2=='d'){op='a';}
                else if(c=='o' && p1=='r'){op='o';ungetc(p2,f);}
                else if(c=='x' && p1=='o' && p2=='r'){op='x';}
                else if(c=='n' && p1=='o' && p2=='t'){op='n';}
                else
                {
                    ungetc(p2,f);
                    ungetc(p1,f);
                    if(r==-1)
                    {
                        r=c;
                        nrr++;
                    }
                    else if(a1==-1)
                    {
                        a1=c;
                        nrr++;
                    }
                    else
                    {
                        a2=c;
                        nrr++;
                    }
                }
            }
            else
            {
                if(r==-1)
                {
                    r=c;
                    nrr++;
                }
                else if(a1==-1)
                {
                    a1=c;
                    nrr++;
                }
                else
                {
                    a2=c;
                    nrr++;
                }
            }
        }
        if(c=='+' || c=='-' || c=='*' || c=='/')
        {
            nrr++;
            op=c;
        }
    }
}

void scandat(core* c)
{
    char fn[50];
    printf("Unesite ime datoteke iz koje ce biti procitan kod:\n");
    scanf("%s",fn);
    FILE* f=fopen(fn,"r");
    if(f==NULL){printf("Greska sa datotekom");}
    else{scan(c,f);fclose(f);}

}

void printdat(core* c)
{
    char fn[50];
    printf("Unesite ime datoteke u koju ce biti upisan graf:\n");
    scanf("%s",fn);
    FILE* f=fopen(fn,"w");
    if(f==NULL){printf("Greska sa datotekom");}
    else{printGraph(c,f);fclose(f);}

}

int max(int a,int b)
{
    return a>b?a:b;
}

int min(int a,int b)
{
    return a<b?a:b;
}

int idFromName(core* c,char name)
{
    return c->LUT[name-'a'];
}

char nameFromId(core* c,int id)
{
    return c->RLUT[id];
}

int getWeight(char op)
{
    switch(op)
    {
        case '+':case '-':{return 3;}
        case '*':{return 10;}
        case '/':{return 23;}
        case 'a':case 'o':case 'x':case 'n':{return 1;}
        default: {return 1;}
    }
}

void initCore(core* cp)
{
    for(int i=0;i<30;i++)
    {
        cp->incidence[i]=NULL;
        cp->LUT[i]=-1;
        cp->RLUT[i]=-1;
        cp->op[i]=0;
        cp->EST[i]=0;
        cp->LST[i]=0;
        cp->L[i]=0;
    }
    cp->Vc=0;
    cp->MET=-1;
}

void addVertex(core* c,char name,char op)
{
    c->LUT[name-'a']=c->Vc;
    c->RLUT[c->Vc]=name;
    c->op[c->Vc]=op;
    c->Vc++;
}

void addEdge(core* c,int source,int dest,int weight)
{
    listNode_edge* node=newListNode_edge();
    node->value.weight=weight;
    node->value.source=source;
    c->incidence[dest]=insertFront_edge(c->incidence[dest],node);
}

void delEdge(core* c,int source,int dest)
{
    c->incidence[dest]=remove_edge(c->incidence[dest],&source,edgecompare);
}

int edgecompare(edge e,void* source)
{
    int sc=*((int*)source);
    return e.source==sc;
}

void delVertex(core* c,int id)
{
    char name=nameFromId(c,id);
    for(int i=0;i<(c->Vc);i++)
    {
        if(c->incidence[i]!=NULL)
        {
            delEdge(c,id,i);
        }
    }
    del_edge(c->incidence[id]);
    c->incidence[id]=NULL;
    c->LUT[name-'a']=-1;
    c->RLUT[id]=-1;
}

void clearCore(core* c)
{
    for(int i=0;i<c->Vc;i++)
    {
        if(c->RLUT[i]!=-1)
        {
            delVertex(c,i);
        }
    }
}

void printGraph(core* c,FILE* f)
{
    for(int i=0;i<c->Vc;i++)
    {
        if(c->RLUT[i]!=-1)
        {
            fprintf(f,"Cvor %c, ulazne grane:",nameFromId(c,i));
            iter2_edge(c->incidence[i],printedge,c,f);
            fprintf(f,"\n");
        }
    }
}

void printedge(edge e,void* cp,void* fp)
{
    core* c=(core*) cp;
    FILE* f=(FILE*) fp;
    fprintf(f,"%c-%d ",nameFromId(c,e.source),e.weight);
}

void fillCP(core* c)
{
    for(int i=0;i<(c->Vc);i++)
    {
        if(c->RLUT[i]!=-1)
        {
            c->EST[i]=0;
            listNode_edge* head=c->incidence[i];
            while(head!=NULL)
            {
                c->EST[i]=max(c->EST[i],c->EST[head->value.source]+head->value.weight);
                head=head->next;
            }
            c->MET=max(c->MET,c->EST[i]+getWeight(c->op[i]));
        }
    }
    for(int i=c->Vc-1;i>=0;i--)
    {
        if(c->RLUT[i]!=-1)
        {
            c->LST[i]=c->MET-getWeight(c->op[i]);
        }
    }
    for(int i=c->Vc-1;i>=0;i--)
    {
        if(c->RLUT[i]!=-1)
        {
            listNode_edge* head=c->incidence[i];
            while(head!=NULL)
            {
                c->LST[head->value.source]=min(c->LST[head->value.source],c->LST[i]-head->value.weight);
                head=head->next;
            }
        }
    }
    for(int i=0;i<c->Vc;i++)
    {
        if(c->RLUT[i]!=-1)
        {
            c->L[i]=c->LST[i]-c->EST[i];
        }
    }

}

void CPLEN(core* c)
{
    if(c->MET==-1)
    {
        fillCP(c);
    }
    printf("Duzina kriticnog puta je:%d\n",c->MET);
}

void allcpBFS(core* c)
{
    if(c->MET==-1)
    {
        fillCP(c);
    }
    queue_lni* pq=NULL;
    queue_lni** Q=&pq;
    for(int i=c->Vc-1;i>=0;i--)
    {
        if(c->RLUT[i]!=-1)
        {
            if(c->LST[i]==c->MET-getWeight(c->op[i]) && c->L[i]==0)
            {
                listNode_int* s=newListNode_int();
                s->value=i;
                insert_lni(Q,s);
            }
        }
    }
    while(!emptyQ_lni(Q))
    {
        listNode_int* s=delete_lni(Q);
        if(c->EST[s->value]==0)
        {
            iter1f_int(s,printlistint,c);
            printf("\n");
        }
        listNode_edge* head=c->incidence[s->value];
        while(head!=NULL)
        {
            if(c->L[head->value.source]==0)
            {
                listNode_int* n=copy_int(s);
                listNode_int* tmp=newListNode_int();
                tmp->value=head->value.source;
                n=insertBefore_int(n,tmp);
                insert_lni(Q,n);
            }
            head=head->next;
        }
        del_int(s);
    }
}

void printlistint(int a,void* cp,bool l)
{
    core* c=(core*)cp;
    printf("%c",nameFromId(c,a));
    if(!l){printf("->");}
}

void printsched(core* c)
{
    if(c->MET==-1)
    {
        fillCP(c);
    }
    for(int i=0;i<c->MET;i++)
    {
        printf("%3d:",i);
        for(int j=0;j<c->Vc;j++)
        {
            if(c->RLUT[j]!=-1)
            {
                if(c->EST[j]<=i && c->LST[j]>=i)
                {
                    printf("%c\263",nameFromId(c,j));
                }
                else
                {
                    printf(" \263",nameFromId(c,j));
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

void transitive(core* c,int s)
{
    printf("cvorovi koji indirekno zavise od %c:",nameFromId(c,s));
    for(int i=0;i<c->Vc;i++)
    {
        if(c->RLUT[i]!=-1)
        {
            listNode_edge* head=c->incidence[i];
            while(head!=NULL)
            {
                if(head->value.source==s)
                {
                    if(bfs(c,i,s))
                    {
                        printf("%c ",nameFromId(c,i));
                    }
                }
                head=head->next;
            }
        }
    }
    printf("\n");
}

int bfs(core* c,int src,int des)
{
    queue_int* pq=NULL;
    queue_int** Q=&pq;
    insert_int(Q,src);
    while(!emptyQ_int(Q))
    {
        int cur=delete_int(Q);
        if(cur==des)
        {
            while(!emptyQ_int(Q)){delete_int(Q);}
            return 1;
        }
        listNode_edge* head=c->incidence[cur];
        while(head!=NULL)
        {
            if(cur!=src || head->value.source!=des)
            {
                insert_int(Q,head->value.source);
            }
            head=head->next;
        }
    }
    return 0;
}

void transitivem(core *c)
{
    char n[50];
    printf("Unesite cvor za koji se odredjuje tranzitivna zavisnost:\n");
    scanf("%s", n);
    transitive(c,idFromName(c,n[0]));
}
