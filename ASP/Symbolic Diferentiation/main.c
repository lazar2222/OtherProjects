#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "string.c"

#define NOTES

#define STEP 10

//Napomene u funkciji printNotes()

//Test primeri
//ln(tg(min(A*D,(-(B^C)))))*(Q+W)/(Q-(-W))
//X ^ Y / (P * Z) + D

#define TYPE char
#define TYPEN char
#include "stack.c"
#undef TYPE
#undef TYPEN
#define TYPE double
#define TYPEN double
#include "stack.c"
#undef TYPE
#undef TYPEN
#define TYPE int
#define TYPEN int
#include "vector.c"
#undef TYPE
#undef TYPEN

typedef struct snode
{
    union
    {
        char op;
        double num;
    }value;
    enum {CHAR,FLOAT}type;
    int level;
    struct snode* left;
    struct snode* right;
} node;

typedef struct
{
    node** arr;
    char** names;
    int csel;
    int size;
    double sym[30];
} treesel;

#define TYPE node*
#define TYPEN nodep
#include "stack.c"
#undef TYPE
#undef TYPEN

void printNotes();
void printMenu(treesel* ts);
void handleMenu(treesel* ts);
void inputTree(treesel* ts);
char* preprocess(char* in);
char* formPostfix(char* in);
bool isOperator(char c);
bool isOperand(char c);
bool isUnary(char c);
int stackPriority(char c);
int inputPriority(char c);
node* formTree(char* pos);
node* enode();
node* cnode(char c);
node* dnode(double d);
void deleteTree(node* root);
void deleteNode(node* node);
void genericPostfix(node* root,void (*fun)(node*));
void insertTree(treesel* ts,node* root,char* name);
void selectTree(treesel* ts);
void printTree(treesel* ts);
void printNode(node* node,int level,bool side,bool u,vector_int* inc,vector_int* nl);
void printNodeContents(node* node);
void printPrefx(treesel* ts);
void printSymbols(treesel* ts);
void inputSymbols(treesel* ts);
void evaluateTree(treesel* ts);
void evaluateNode(treesel* ts,node* node,stack_double** s);
void differentiateTree(treesel* ts);
node* copyTree(node* root);
void copyNode(node* dst,node* src);
void differentiateRoot(node* root,char d);
void differentiateNode(node* root,char d,stack_nodep** td);
bool containsD(node* root,char d);
void reduceTree(node* root);
void reduceNode(node* root);
bool isConstant(node* root);
bool isLeftNeutral(node* root);
bool isRightNeutral(node* root);
double evalConstant(node* root);
void deallocTs(treesel* ts);

int main()
{
    treesel* ts=malloc(sizeof(treesel));
    ts->csel=-1;
    ts->size=0;
    ts->arr=NULL;
    ts->names=NULL;
    for(int i=0;i<30;i++)
    {
        ts->sym[i]=0;
    }
    printNotes();
    while(true)
    {
        printMenu(ts);
        handleMenu(ts);
    }
    return 0;
}

void printNotes()
{
#ifdef NOTES
    printf("NAPOMENE:\r\n");
    printf("Unoz izraza ignorise blanko kraraktere i podrzava sledece operacije +,-,/,*,^,unarni minus (mora biti okruzen zagradama) i sledece funkcije ln,tg,min,cos,sin,sgn ciji se argumenti navode u zagradama i u slucaju funkcija sa vise argumenata se razdvajaju zarezom npr. min(A,B).\r\n\
Nakon unosa stablo se dodaje u listu stabala gde je uz pomoc druge opcije u meniju moguce izabrati trenutno izabrano stablo nad kome ce se izvrsavati ostale naredbe, ime trenutno izabranog stabla se takodje ispisuje pre svakog ispisa menija (ime stabla je njegova infiksna reprezentacija tacno onako kako je uneta).\r\n\
Prikaz trenutno izabranog stabla se ostvaruje graficki gde cu cvorovi pravilno uvuceni u zavisnosti od njihovog nivoa i linijama su spojeni sa svojim roditeljem i bratom, pri ispisu samog cvora prvo se ispisuje njegov nivo i da li je levi sin 'L' ili desni sin 'D' ili koren stabla 'K' pa nakon dvotacke i njegova sadrzina (brojevne konstante i unarni minus su okruzeni zagradama).\r\n\
Prefiksni ispis se vodi istim pravilima za ispis sadrzine cvora (brojevne konstante i unarni minus su okruzeni zagradama) i kako sam smatrao da nece biti zabune izmedju funkcija cak i ako su napisane jedna pored druge bez razmaka izmedju a radi konciznijeg ispisa, izmedju elemenata se ne nalazi blanko znak.\r\n\
Peta opcija ne zahteva neke posebne napomene osim cinjenice da su vrednosti simbola tipa double.\r\n\
Unos simbola se odvija na malo specifican nacin, nakon izbora opcije unosi se proizvoljan broj parova karaktera koji predstavlja ime simbola i double vrednosti simbola koji su obavezno razdvojeni blanko znakom, unos se prekida pri prvom karakteru koji ne predstavlja ime simbola npr. A 3 B -5 F 0.35 x.\r\n\
Evaluacija opet ne zahteva neke posebne komentare osim da se specijalne vrednosti tipa +/- inf i NaN ispisuju u podrazumevanom formatu npr. NaN se ispisuje kao 1.#QNAN.\r\n\
Za diferenciranje izraza se nakon izbora opcije unosi tacno jedan karakter koji predstavlja simbol po kome se diferencira nakon toga se izraz diferencira i rezultat se cuva u novom stablu koje ce automatski biti izabrano kao trenutno izabrano stablo i cije ime ce biti ime diferenciranog stabla sa prefiksom formata dX| gde je X ime simbola po kome je diferencirano.\r\n\
Algoritam za diferenciranje podrzava sve operacije i funkcije kao i unos izraza i dodatno ima eksperimentalnu podrsku za logaritamsko diferenciranje (u slucaju detekcije logaritamskog diferenciranja poruka koja obavestava korisnika ce biti ispisana).\r\n\
Nakon diferenciranja stablo se automatsi biti redukovano izracunavanjem cvorova kojima su sva deca konstante i uklanjanjem operacija kojima je jedan operand neutralan element (npr. 0+A) ili rezultat ne zavisi od drugog operanda (npr. 0*A)\r\n");
#endif
}

void printMenu(treesel* ts)
{
    if(ts->csel!=-1)
    {
        printf("\r\n");
        printf("Trenutno izabrano stablo: %s\r\n",ts->names[ts->csel]);
    }
    printf("\r\n");
    printf("1. Unos izraza i kreiranje stabla\r\n");
    printf("2. Promena trenutno izabranog stabla\r\n");
    printf("3. Prikaz trenutno izabranog stabla\r\n");
    printf("4. Prefiksni ispis trenutno izabranog stabla\r\n");
    printf("5. Ispis tabele simbola\r\n");
    printf("6. Promena tabele simbola\r\n");
    printf("7. Evaluacija trenutno izabranog stabla\r\n");
    printf("8. Diferenciranje trenutno izabranog stabla\r\n");
    printf("9. Kraj rada\r\n");
}

void handleMenu(treesel* ts)
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
        case 1:{inputTree(ts); break;}
        case 2:{selectTree(ts); break;}
        case 3:{printTree(ts); break;}
        case 4:{printPrefx(ts); break;}
        case 5:{printSymbols(ts);break;}
        case 6:{inputSymbols(ts);break;}
        case 7:{evaluateTree(ts); break;}
        case 8:{differentiateTree(ts); break;}
        case 9:{deallocTs(ts); exit(0);break;}
        default:{printf("Greska: Nepostojeca opcija\r\n"); break;}
    }
}

void inputTree(treesel* ts)
{
    printf("Unesite izraz:\r\n");
    char* s=readLine();
    char* pos=malloc(strlen(s)*sizeof(char)+1);
    memcpy(pos,s,strlen(s)*sizeof(char)+1);
    pos=preprocess(pos);
    pos=formPostfix(pos);
    if(pos!=NULL){
        node* root=formTree(pos);
        if(root!=NULL)
        {
        insertTree(ts,root,s);
        free(pos);
        }
        else
        {
            free(s);
        }
    }
    else
    {
        free(s);
    }
}

char* preprocess(char* in)
{
    //ln->l tg->t min->m cos->c sin->s sgn->g
    int j=0;
    for(int i=0;i<strlen(in);i++)
    {
        if(i+1<strlen(in) && in[i]=='(' && in[i+1]=='-')
        {
            in[j++]='(';
            in[j++]='!';
            i+=1;
        }
        else if(i+1<strlen(in) && in[i]=='l' && in[i+1]=='n')
        {
            in[j++]='l';
            i+=1;
        }
        else if(i+1<strlen(in) && in[i]=='t' && in[i+1]=='g')
        {
            in[j++]='t';
            i+=1;
        }
        else if(i+2<strlen(in) && in[i]=='m' && in[i+1]=='i' && in[i+2]=='n')
        {
            i+=2;
        }
        else if(i+2<strlen(in) && in[i]=='c' && in[i+1]=='o' && in[i+2]=='s')
        {
            in[j++]='c';
            i+=2;
        }
        else if(i+2<strlen(in) && in[i]=='s' && in[i+1]=='i' && in[i+2]=='n')
        {
            in[j++]='s';
            i+=2;
        }
        else if(i+2<strlen(in) && in[i]=='s' && in[i+1]=='g' && in[i+2]=='n')
        {
            in[j++]='g';
            i+=2;
        }
        else if(in[i]==',')
        {
            if(j<=i-3)
            {
                in[j++]=')';
                in[j++]='m';
                in[j++]='(';
            }
        }
        else if(in[i]!=' ')
        {
            in[j++]=in[i];
        }
    }
    in[j++]='\0';
    return realloc(in,j*sizeof(char));
}

char* formPostfix(char* in)
{
    stack_char* st=NULL;
    stack_char** s=&st;
    int j=0;
    for(int i=0;i<strlen(in);i++)
    {
        if(isOperand(in[i]))
        {
            in[j++]=in[i];
        }
        else if(isOperator(in[i]))
        {
            if(empty_char(s))
            {
                push_char(s,in[i]);
            }
            else
            {
                while(!empty_char(s) && stackPriority(top_char(s))>=inputPriority(in[i]))
                {
                    char c=pop_char(s);
                    in[j++]=c;
                }
                if(in[i]==')' &&!empty_char(s))
                {
                    pop_char(s);
                }
                else
                {
                    push_char(s,in[i]);
                }
            }
        }
        else{
                printf("Greska: Nepravilan unos\r\n");
                free(in);
                while(!empty_char(s)){pop_char(s);}
                return NULL;
        }
    }
    while(!empty_char(s))
    {
        char c=pop_char(s);
        in[j++]=c;
    }
    in[j++]='\0';
    return realloc(in,j*sizeof(char));
}

bool isOperator(char c)
{
    return c=='+' || c=='-' || c=='*' || c=='/' || c=='^' || c=='!' ||
        c=='l' || c=='t' || c=='m' || c=='s' || c=='c' || c=='g' || c=='(' || c==')';
}

bool isOperand(char c)
{
    return c>='A' && c<='Z';
}

bool isUnary(char c)
{
    return c=='!' || c=='l' || c=='t' || c=='c' || c=='s' || c=='g';
}

int stackPriority(char c)
{
    switch (c)
    {
        case '+':case '-': return 2;
        case '*':case '/': return 3;
        case '^': return 4;
        case '!': return 6;
        case 'l': case 't': case 'm': case 's':case 'c': case'g': return 7;
        case '(': return 0;
    }
    return -1;
}

int inputPriority(char c)
{
    switch (c)
    {
        case '+':case '-': return 2;
        case '*':case '/': return 3;
        case '^': return 5;
        case '!': return 6;
        case 'l': case 't': case 'm': case 's':case 'c': case'g': return 7;
        case '(': return 8;
        case ')': return 1;
    }
    return -1;
}

node* formTree(char* pos)
{
    stack_nodep* st= NULL;
    stack_nodep** s=&st;
    for(int i=0;i<strlen(pos);i++)
    {
        if(isOperand(pos[i]))
        {
            node* t=cnode(pos[i]);
            push_nodep(s,t);
        }
        else
        {
            if(isUnary(pos[i]))
            {
                if(empty_nodep(s))
                {
                    printf("Greska: Stack underflow\r\n");
                    free(pos);
                    return NULL;
                }
                node* l=pop_nodep(s);
                node* t=cnode(pos[i]);
                t->left=l;
                push_nodep(s,t);
            }
            else
            {
                if(empty_nodep(s))
                {
                    printf("Greska: Stack underflow\r\n");
                    free(pos);
                    return NULL;
                }
                node* r=pop_nodep(s);
                if(empty_nodep(s))
                {
                    deleteTree(r);
                    printf("Greska: Stack underflow\r\n");
                    free(pos);
                    return NULL;
                }
                node* l=pop_nodep(s);
                node* t=cnode(pos[i]);
                t->left=l;
                t->right=r;
                push_nodep(s,t);
            }
        }
    }
    node* r;
    if(!empty_nodep(s))
    {
        r=pop_nodep(s);
        if(!empty_nodep(s))
        {
            while(!empty_nodep(s)){deleteTree(pop_nodep(s));}
            deleteTree(r);
            printf("Greska: Stack overflow\r\n");
            free(pos);
            return NULL;
        }
        else
        {
            return r;
        }
    }
    else
    {
        printf("Greska: Stack underflow\r\n");
        free(pos);
        return NULL;
    }
}

node* enode()
{
    node* res=malloc(sizeof(node));
    res->type=CHAR;
    res->value.op=0;
    res->left=NULL;
    res->right=NULL;
    return res;
}

node* cnode(char c)
{
    node* res=enode();
    res->value.op=c;
    return res;
}

node* dnode(double d)
{
    node* res=enode();
    res->type=FLOAT;
    res->value.num=d;
    return res;
}

void deleteTree(node* root)
{
    genericPostfix(root,deleteNode);
}

void deleteNode(node* node)
{
    free(node);
}

void genericPostfix(node* root,void (*fun)(node*))
{
    stack_nodep* st= NULL;
    stack_nodep** s=&st;
    while(root!=NULL)
    {
        if(root->right!=NULL)
        {
            push_nodep(s,root->right);
        }
        push_nodep(s,root);
        root=root->left;
    }
    while(!empty_nodep(s))
    {
        root=pop_nodep(s);
        if(!empty_nodep(s) && root->right==top_nodep(s))
        {
            node* t=pop_nodep(s);
            push_nodep(s,root);
            root=t;
        }
        else
        {
            fun(root);
            root=NULL;
        }
        while(root!=NULL)
        {
            if(root->right!=NULL)
            {
                push_nodep(s,root->right);
            }
            push_nodep(s,root);
            root=root->left;
        }
    }
}

void insertTree(treesel* ts,node* root,char* name)
{
    if(ts->size%STEP==0)
    {
        ts->arr=realloc(ts->arr,((ts->size/STEP)+1)*STEP*sizeof(node*));
        ts->names=realloc(ts->names,((ts->size/STEP)+1)*STEP*sizeof(char*));
    }
    ts->arr[ts->size]=root;
    ts->names[ts->size]=name;
    ts->csel=ts->size;
    ts->size++;
}

void selectTree(treesel* ts)
{
    printf("\r\n");
    for(int i=0;i<ts->size;i++)
    {
        printf("%d. %s\r\n",i+1,ts->names[i]);
    }
    printf("Unesite redni broj stabla koje zelite da izaberete:\r\n");
    int in;
    if(scanf("%d",&in)==0)
    {
        scanf("%*[^\n]%*c");
        printf("Greska: Nepostojece stablo\r\n");
        return;
    }
    if(in>0 && in<=ts->size)
    {
        ts->csel=in-1;
    }
    else
    {
        printf("Greska: Nepostojece stablo\r\n");
    }
}

void printTree(treesel* ts)
{
    printf("\r\n");
    if(ts->csel!=-1)
    {
        node* root=ts->arr[ts->csel];
        stack_nodep* st= NULL;
        stack_nodep** s=&st;
        vector_int* inc=initVector_int();
        vector_int* nl=initVector_int();
        int level=1;
        while(root!=NULL)
        {
            printNode(root,level,true,root->right==NULL,inc,nl);
            level++;
            if(root->right!=NULL)
            {
                root->right->level=level;
                push_nodep(s,root->right);
            }
            root=root->left;
        }
        while(!empty_nodep(s))
        {
            root=pop_nodep(s);
            level=root->level;
            printNode(root,level,false,root->right==NULL,inc,nl);
            level++;
            if(root->right!=NULL)
            {
                root->right->level=level;
                push_nodep(s,root->right);
            }
            root=root->left;
            while(root!=NULL)
            {
                printNode(root,level,true,root->right==NULL,inc,nl);
                level++;
                if(root->right!=NULL)
                {
                    root->right->level=level;
                    push_nodep(s,root->right);
                }
                root=root->left;
            }
        }
        freeVector_int(inc);
        freeVector_int(nl);
    }
    else
    {
        printf("Greska: Nije uneto stablo\r\n");
    }
}

void printNode(node* node,int level,bool side,bool u,vector_int* inc,vector_int* nl)
{
    set_int(inc,level+1,u?2:1);
    set_int(nl,level,get_int(nl,level)+get_int(inc,level));
    printf(" ");
    for(int i=1;i<level;i++)
    {
        printf("%c",get_int(nl,i+1)%2==0?(i==level-1?'\300':' '):(i==level-1?'\303':'\263'));
    }
    printf("%d%c:",level,level==1?'K':side?'L':'D');
    printNodeContents(node);
    printf("\r\n");
}

void printNodeContents(node* node)
{
    if(node->type==CHAR)
    {
        char c=node->value.op;
        if(c>='A'&&c<='Z')
        {
            printf("%c",c);
        }
        else
        {
            char* out;
            switch (c)
            {
                case '+':{out="+"; break;}
                case '-':{out="-"; break;}
                case '*':{out="*"; break;}
                case '/':{out="/"; break;}
                case '^':{out="^"; break;}
                case '!':{out="(-)"; break;}
                case 'l':{out="ln"; break;}
                case 't':{out="tg"; break;}
                case 'm':{out="min"; break;}
                case 's':{out="sin"; break;}
                case 'c':{out="cos"; break;}
                case 'g':{out="sgn"; break;}
            }
            printf("%s",out);
        }
    }
    else
    {
        printf("(");
        smartDouble(node->value.num);
        printf(")");
    }
}

void printPrefx(treesel* ts)
{
    printf("\r\n");
    if(ts->csel!=-1)
    {
        node* root=ts->arr[ts->csel];
        stack_nodep* st= NULL;
        stack_nodep** s=&st;
        while(root!=NULL)
        {
            printNodeContents(root);
            if(root->right!=NULL)
            {
                push_nodep(s,root->right);
            }
            root=root->left;
        }
        while(!empty_nodep(s))
        {
            root=pop_nodep(s);
            while(root!=NULL)
            {
                printNodeContents(root);
                if(root->right!=NULL)
                {
                    push_nodep(s,root->right);
                }
                root=root->left;
            }
        }
        printf("\r\n");
    }
    else
    {
        printf("Greska: Nije uneto stablo\r\n");
    }
}

void printSymbols(treesel* ts)
{
    printf("Tabela simbola:\r\n");
    for(int i='A';i<='Z';i++)
    {
        printf("%c: ",i);
        smartDouble(ts->sym[i-'A']);
        printf("\r\n");
    }
}

void inputSymbols(treesel* ts)
{
    double v;
    char c;
    while(true)
    {
        scanf(" %c",&c);
        if(c>='A' && c<='Z')
        {
            if(scanf(" %lf",&v)==0)
            {
                scanf("%*[^\n]%*c");
                break;
            }
            ts->sym[c-'A']=v;
        }
        else{break;}
    }
}

void evaluateTree(treesel* ts)
{
    printf("\r\n");
    if(ts->csel!=-1)
    {
        node* root=ts->arr[ts->csel];
        stack_nodep* st= NULL;
        stack_nodep** s=&st;
        stack_double* std= NULL;
        stack_double** sd=&std;
        while(root!=NULL)
        {
            if(root->right!=NULL)
            {
                push_nodep(s,root->right);
            }
            push_nodep(s,root);
            root=root->left;
        }
        while(!empty_nodep(s))
        {
            root=pop_nodep(s);
            if(!empty_nodep(s) && root->right==top_nodep(s))
            {
                node* t=pop_nodep(s);
                push_nodep(s,root);
                root=t;
            }
            else
            {
                evaluateNode(ts,root,sd);
                root=NULL;
            }
            while(root!=NULL)
            {
                if(root->right!=NULL)
                {
                    push_nodep(s,root->right);
                }
                push_nodep(s,root);
                root=root->left;
            }
        }
        double res;
        if(!empty_double(sd))
        {
            res=pop_double(sd);
            if(!empty_double(sd))
            {
                while(!empty_double(sd)){pop_double(sd);}
                printf("Greska: Stack overflow\r\n");
            }
            else
            {
                smartDouble(res);
                printf("\r\n\r\n");
            }
        }
        else
        {
            printf("Greska: Stack underflow\r\n");
        }
    }
    else
    {
        printf("Greska: Nije uneto stablo\r\n");
    }
}

void evaluateNode(treesel* ts,node* node,stack_double** s)
{
    if(node->type==FLOAT)
    {
        push_double(s,node->value.num);
    }
    else
    {
        if(isOperand(node->value.op))
        {
            push_double(s,ts->sym[node->value.op-'A']);
        }
        else
        {
            if(isUnary(node->value.op))
            {
                if(!empty_double(s))
                {
                    double a=pop_double(s);
                    switch(node->value.op)
                    {
                        case '!':{push_double(s,-a); break;}
                        case 'l':{push_double(s,log(a)); break;}
                        case 't':{push_double(s,tan(a)); break;}
                        case 'c':{push_double(s,cos(a)); break;}
                        case 's':{push_double(s,sin(a)); break;}
                        case 'g':{push_double(s,a==0?0:a>0?1:-1); break;}
                    }
                }
            }
            else
            {
                if(!empty_double(s))
                {
                    double a=pop_double(s);
                    if(!empty_double(s))
                    {
                        double b=pop_double(s);
                        switch(node->value.op)
                        {
                            case '+':{push_double(s,b+a); break;}
                            case '-':{push_double(s,b-a); break;}
                            case '/':{push_double(s,b/a); break;}
                            case '*':{push_double(s,b*a); break;}
                            case '^':{push_double(s,pow(b,a)); break;}
                            case 'm':{push_double(s,fmin(b,a)); break;}
                        }
                    }
                }
            }
        }
    }
}

void differentiateTree(treesel* ts)
{
    printf("\r\n");
    if(ts->csel!=-1)
    {
        printf("Unesite simbol po kome se diferencira:\r\n");
        char d;
        scanf(" %c",&d);
        scanf("%*[^\n]%*c");
        if(isOperand(d))
        {
            node* root=copyTree(ts->arr[ts->csel]);
            differentiateRoot(root,d);
            reduceTree(root);
            char* nn=malloc((strlen(ts->names[ts->csel])+4)*sizeof(char));
            sprintf(nn,"d%c|%s",d,ts->names[ts->csel]);
            insertTree(ts,root,nn);
        }
        else
        {
            printf("Greska: Nije validan simbol\r\n");
        }
    }
    else
    {
        printf("Greska: Nije uneto stablo\r\n");
    }
}

node* copyTree(node* root)
{
    stack_nodep* sts= NULL;
    stack_nodep** ss=&sts;
    stack_nodep* std= NULL;
    stack_nodep** sd=&std;
    node* dest=enode();
    node* t=dest;
    while(root!=NULL)
    {
        copyNode(t,root);
        if(root->right!=NULL)
        {
            push_nodep(ss,root->right);
            t->right=enode();
            push_nodep(sd,t->right);
        }
        root=root->left;
        if(root!=NULL){t->left=enode();}
        t=t->left;
    }
    while(!empty_nodep(ss))
    {
        root=pop_nodep(ss);
        t=pop_nodep(sd);
        while(root!=NULL)
        {
            copyNode(t,root);
            if(root->right!=NULL)
            {
                push_nodep(ss,root->right);
                t->right=enode();
                push_nodep(sd,t->right);
            }
            root=root->left;
            if(root!=NULL){t->left=enode();}
            t=t->left;
        }
    }
    return dest;
}

void copyNode(node* dst,node* src)
{
    dst->type=src->type;
    dst->value=src->value;
    dst->level=src->level;
    dst->left=src->left;
    dst->right=src->right;
}

void differentiateRoot(node* root,char d)
{
    stack_nodep* tdd= NULL;
    stack_nodep** td=&tdd;
    push_nodep(td,root);
    while(!empty_nodep(td))
    {
        root=pop_nodep(td);
        differentiateNode(root,d,td);
    }
}

void differentiateNode(node* root,char d,stack_nodep** td)
{
    if(root->type==FLOAT)
    {
        root->value.num=0;
    }
    else
    {
        if(isOperand(root->value.op))
        {
            if(root->value.op==d)
            {
                root->type=FLOAT;
                root->value.num=1;
            }
            else
            {
                root->type=FLOAT;
                root->value.num=0;
            }
        }
        else
        {
            switch(root->value.op)
            {
                case '+':{push_nodep(td,root->left);push_nodep(td,root->right); break;}
                case '-':{push_nodep(td,root->left);push_nodep(td,root->right); break;}
                case '*':{
                    node* rl=root->left;
                    node* rr=root->right;
                    root->value.op='+';
                    root->left=cnode('*');
                    root->right=cnode('*');
                    root->left->left=rl;
                    root->left->right=rr;
                    root->right->left=copyTree(rl);
                    root->right->right=copyTree(rr);
                    push_nodep(td,root->left->left);
                    push_nodep(td,root->right->right);
                    break;}
                case '/':{
                    node* rl=root->left;
                    node* rr=root->right;
                    root->right=cnode('^');
                    root->right->right=dnode(2);
                    root->right->left=copyTree(rr);
                    root->left=cnode('-');
                    root=root->left;
                    root->left=cnode('*');
                    root->right=cnode('*');
                    root->left->left=rl;
                    root->left->right=rr;
                    root->right->left=copyTree(rl);
                    root->right->right=copyTree(rr);
                    push_nodep(td,root->left->left);
                    push_nodep(td,root->right->right);
                    break;}
                case '^':{
                    bool lx=containsD(root->left,d);
                    bool dx=containsD(root->right,d);
                    if(lx && dx)
                    {
                        printf("Pronadjen i izracunat logaritamski izvod\r\n");
                        node* x=root->left;
                        node* y=root->right;
                        root->left=copyTree(root);
                        root->right=cnode('*');
                        root->value.op='*';
                        root->right->left=cnode('l');
                        root->right->left->left=x;
                        root->right->right=y;
                        push_nodep(td,root->right);
                    }
                    else if(lx)
                    {
                        node* x=root->left;
                        node* a=root->right;
                        root->value.op='*';
                        root->left=a;
                        root->right=cnode('*');
                        root->right->right=x;
                        push_nodep(td,root->right->right);
                        root->right->left=cnode('^');
                        root->right->left->right=cnode('-');
                        root->right->left->right->right=dnode(1);
                        root->right->left->right->left=copyTree(a);
                        root->right->left->left=copyTree(x);
                    }
                    else if(dx)
                    {
                        node* a=root->left;
                        node* x=root->right;
                        root->value.op='*';
                        root->left=cnode('l');
                        root->left->left=a;
                        root->right=cnode('*');
                        root->right->left=cnode('^');
                        root->right->left->left=copyTree(a);
                        root->right->left->right=copyTree(x);
                        root->right->right=copyTree(x);
                        push_nodep(td,root->right->right);
                    }
                    else
                    {
                        root->type=FLOAT;
                        root->value.num=0;
                        deleteTree(root->left);
                        deleteTree(root->right);
                        root->left=NULL;
                        root->right=NULL;
                    }
                    break;}
                case '!':{push_nodep(td,root->left); break;}
                case 'l':{
                    node* x=root->left;
                    root->value.op='*';
                    root->left=cnode('/');
                    root->left->left=dnode(1);
                    root->left->right=copyTree(x);
                    root->right=x;
                    push_nodep(td,root->right);
                    break;}
                case 't':{
                    node* x=root->left;
                    root->value.op='*';
                    root->left=cnode('/');
                    root->left->left=dnode(1);
                    root->left->right=cnode('^');
                    root->left->right->left=cnode('c');
                    root->left->right->left->left=copyTree(x);
                    root->left->right->right=dnode(2);
                    root->right=x;
                    push_nodep(td,root->right);
                    break;}
                case 'm':{
                    node* a=root->left;
                    node* b=root->right;
                    root->value.op='*';
                    root->left=cnode('-');
                    root->left->left=cnode('+');
                    root->left->left->left=a;
                    push_nodep(td,root->left->left->left);
                    root->left->left->right=b;
                    push_nodep(td,root->left->left->right);
                    root->left->right=cnode('*');
                    root->left->right->left=cnode('g');
                    root->left->right->left->left=cnode('-');
                    root->left->right->left->left->left=copyTree(a);
                    root->left->right->left->left->right=copyTree(b);
                    root->left->right->right=cnode('-');
                    root->left->right->right->left=copyTree(a);
                    push_nodep(td,root->left->right->right->left);
                    root->left->right->right->right=copyTree(b);
                    push_nodep(td,root->left->right->right->right);
                    root->right=dnode(0.5);
                    break;}
                case 'c':{
                    node* x=root->left;
                    root->value.op='!';
                    root->left=cnode('*');
                    root->left->left=cnode('s');
                    root->left->left->left=copyTree(x);
                    root->left->right=x;
                    push_nodep(td,root->left->right);
                    break;}
                case 's':{
                    node* x=root->left;
                    root->value.op='*';
                    root->left=cnode('c');
                    root->left->left=copyTree(x);
                    root->right=x;
                    push_nodep(td,root->right);
                    break;}
                case 'g':{
                    node* x=root->left;
                    root->type=FLOAT;
                    root->value.num=0;
                    root->left=NULL;
                    root->right=NULL;
                    deleteTree(x);
                    break;}
            }
        }
    }
}

bool containsD(node* root,char d)
{
    bool res=false;
    stack_nodep* st= NULL;
    stack_nodep** s=&st;
    while(root!=NULL)
    {
        if(root->right!=NULL)
        {
            push_nodep(s,root->right);
        }
        push_nodep(s,root);
        root=root->left;
    }
    while(!empty_nodep(s))
    {
        root=pop_nodep(s);
        if(!empty_nodep(s) && root->right==top_nodep(s))
        {
            node* t=pop_nodep(s);
            push_nodep(s,root);
            root=t;
        }
        else
        {
            if(root->type==CHAR && root->value.op==d){res=true;break;}
            root=NULL;
        }
        while(root!=NULL)
        {
            if(root->right!=NULL)
            {
                push_nodep(s,root->right);
            }
            push_nodep(s,root);
            root=root->left;
        }
    }
    while(!empty_nodep(s)){pop_nodep(s);}
    return res;
}

void reduceTree(node* root)
{
    genericPostfix(root,reduceNode);
}

void reduceNode(node* root)
{
    if(root->type==CHAR && isOperator(root->value.op))
    {
        if(isConstant(root))
        {
            double res=evalConstant(root);
            deleteNode(root->left);
            deleteNode(root->right);
            root->type=FLOAT;
            root->value.num=res;
            root->left=NULL;
            root->right=NULL;
        }
        else if(!isUnary(root->value.op))
        {
            if(isLeftNeutral(root))
            {
                switch(root->value.op)
                {
                    case '+':{
                        deleteNode(root->left);
                        node* t=root->right;
                        root->type=t->type;
                        root->value.op=t->value.op;
                        root->left=t->left;
                        root->right=t->right;
                        t->left=NULL;
                        t->right=NULL;
                        deleteNode(t);
                        break;}
                    case '-':{
                        deleteNode(root->left);
                        root->left=root->right;
                        root->right=NULL;
                        root->value.op='!';
                        break;}
                    case '*':{
                        if(root->left->value.num==1)
                        {
                            deleteNode(root->left);
                            node* t=root->right;
                            root->type=t->type;
                            root->value.op=t->value.op;
                            root->left=t->left;
                            root->right=t->right;
                            t->left=NULL;
                            t->right=NULL;
                            deleteNode(t);
                        }
                        else
                        {
                            deleteTree(root->left);
                            deleteTree(root->right);
                            root->type=FLOAT;
                            root->value.num=0;
                            root->left=NULL;
                            root->right=NULL;
                        }
                        break;}
                    case '^':{
                        root->type=FLOAT;
                        root->value.num=root->left->value.num;
                        deleteTree(root->left);
                        deleteTree(root->right);
                        root->left=NULL;
                        root->right=NULL;
                        break;}
                }
            }
            else if(isRightNeutral(root))
            {
                switch(root->value.op)
                {
                    case '+':{
                        deleteNode(root->right);
                        node* t=root->left;
                        root->type=t->type;
                        root->value.op=t->value.op;
                        root->left=t->left;
                        root->right=t->right;
                        t->left=NULL;
                        t->right=NULL;
                        deleteNode(t);
                        break;}
                    case '-':{
                        deleteNode(root->right);
                        node* t=root->left;
                        root->type=t->type;
                        root->value.op=t->value.op;
                        root->left=t->left;
                        root->right=t->right;
                        t->left=NULL;
                        t->right=NULL;
                        deleteNode(t);
                        break;}
                    case '*':{
                        if(root->right->value.num==1)
                        {
                            deleteNode(root->right);
                            node* t=root->left;
                            root->type=t->type;
                            root->value.op=t->value.op;
                            root->left=t->left;
                            root->right=t->right;
                            t->left=NULL;
                            t->right=NULL;
                            deleteNode(t);
                        }
                        else
                        {
                            deleteTree(root->left);
                            deleteTree(root->right);
                            root->type=FLOAT;
                            root->value.num=0;
                            root->left=NULL;
                            root->right=NULL;
                        }
                        break;}
                    case '^':{
                        if(root->right->value.num==1)
                        {
                            deleteNode(root->right);
                            node* t=root->left;
                            root->type=t->type;
                            root->value.op=t->value.op;
                            root->left=t->left;
                            root->right=t->right;
                            t->left=NULL;
                            t->right=NULL;
                            deleteNode(t);
                        }
                        else
                        {
                            deleteTree(root->left);
                            deleteTree(root->right);
                            root->type=FLOAT;
                            root->value.num=1;
                            root->left=NULL;
                            root->right=NULL;
                        }
                        break;}
                }
            }
        }
    }
}

bool isConstant(node* root)
{
    if(isUnary(root->value.op))
    {
        return root->left->type==FLOAT;
    }
    else
    {
        return root->left->type==FLOAT && root->right->type==FLOAT;
    }
}

bool isLeftNeutral(node* root)
{
    if(root->left->type==FLOAT)
    {
        switch(root->value.op)
        {
            case '+':{return root->left->value.num==0;}
            case '-':{return root->left->value.num==0;}
            case '/':{return false;}
            case '*':{return root->left->value.num==1 || root->left->value.num==0;}
            case '^':{return root->left->value.num==1 || root->left->value.num==0;}
            case 'm':{return false;}
        }
        return false;
    }
    else{return false;}
}

bool isRightNeutral(node* root)
{
    if(root->right->type==FLOAT)
    {
        switch(root->value.op)
        {
            case '+':{return root->right->value.num==0;}
            case '-':{return root->right->value.num==0;}
            case '/':{return root->right->value.num==1;}
            case '*':{return root->right->value.num==1 || root->right->value.num==0;}
            case '^':{return root->right->value.num==1 || root->right->value.num==0;}
            case 'm':{return false; break;}
        }
        return false;
    }
    else{return false;}
}

double evalConstant(node* root)
{
    if(isUnary(root->value.op))
    {
        double a=root->left->value.num;
        switch(root->value.op)
        {
            case '!':{return -a;}
            case 'l':{return log(a);}
            case 't':{return tan(a);}
            case 'c':{return cos(a);}
            case 's':{return sin(a);}
            case 'g':{return a==0?0:a>0?1:-1;}
        }
    }
    else
    {
        double a=root->left->value.num;
        double b=root->right->value.num;
        switch(root->value.op)
        {
            case '+':{return a+b;}
            case '-':{return a-b;}
            case '/':{return a/b;}
            case '*':{return a*b;}
            case '^':{return pow(a,b);}
            case 'm':{return fmin(a,b);}
        }
    }
    return 0;
}

void deallocTs(treesel* ts)
{
    for(int i=0;i<ts->size;i++)
    {
        deleteTree(ts->arr[i]);
        free(ts->names[i]);
    }
    free(ts->arr);
    free(ts->names);
    free(ts);
}
