#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

//Trougaona Matrica
//Adresna funkcija: ofs=((j*(j-1))/2)+i

typedef struct {
    int* array;
    int defaultElement;
    int size;
} Tmatrica;

int noEl(int size);
Tmatrica* initTmatrica(int size);
void freeTmatrica(Tmatrica* tm);
bool validRange(Tmatrica* tm,int i,int j);
bool defaultRange(Tmatrica* tm,int i,int j);
int addrf(Tmatrica* tm,int i,int j);
void TmSet(Tmatrica* tm,int i,int j,int v);
void TmSetDefault(Tmatrica* tm,int v);
int TmGet(Tmatrica* tm,int i,int j);

//Demo Aplikacija

void printMenu();
void handleMenu(Tmatrica** pmat);
void InitMat(Tmatrica** pmat);
void PpvMat(Tmatrica* mat);
void GetMat(Tmatrica* mat);
void SetMat(Tmatrica* mat);
void NrnpMat(Tmatrica* mat);
void PrintMat(Tmatrica* mat);
void SsMat(Tmatrica* mat);
void DelMat(Tmatrica** pmat);

int main()
{
    Tmatrica* mat=NULL;
    while(true)
    {
        printMenu();
        handleMenu(&mat);
    }
    return 0;
}

int noEl(int size)
{
    return (size*(size-1))/2;
}

Tmatrica* initTmatrica(int size)
{
    Tmatrica* ret=(Tmatrica*)malloc(sizeof(Tmatrica));
    ret->defaultElement=0;
    ret->size=size;
    ret->array=(int*)calloc(noEl(size),sizeof(int));
    return ret;
}

void freeTmatrica(Tmatrica* tm)
{
    free(tm->array);
    free(tm);
}

bool validRange(Tmatrica* tm,int i,int j)
{
    return i>=0 && j>=0 && i<tm->size && j<tm->size;
}

bool defaultRange(Tmatrica* tm,int i,int j)
{
    return validRange(tm,i,j) && i>=j;
}

int addrf(Tmatrica* tm,int i,int j)
{
    return ((j*(j-1))/2)+i;
}

void TmSet(Tmatrica* tm,int i,int j,int v)
{
    if(!defaultRange(tm,i,j))
    {
        tm->array[addrf(tm,i,j)]=v;
    }
    else
    {
        printf("Greska: Indeks van opsega\r\n");
    }
}

void TmSetDefault(Tmatrica* tm,int v)
{
    tm->defaultElement=v;
}

int TmGet(Tmatrica* tm,int i,int j)
{
    if(validRange(tm,i,j))
    {
        if(defaultRange(tm,i,j))
        {
            return tm->defaultElement;
        }
        else
        {
            return tm->array[addrf(tm,i,j)];
        }
    }
    else
    {
        printf("Greska: Indeks van opsega\r\n");
        return INT_MIN;
    }
}

void printMenu()
{
    printf("\r\n");
    printf("1. Inicijalizacija matrice\r\n");
    printf("2. Postavljanje podrazumevane vrednosti\r\n");
    printf("3. Dohvatanje elementa\r\n");
    printf("4. Postavljanje elementa\r\n");
    printf("5. Broj ne podrazumevanih elemenata\r\n");
    printf("6. Ispis matrice\r\n");
    printf("7. Usteda prostora\r\n");
    printf("8. Brisanje matrice\r\n");
    printf("9. Kraj rada\r\n");
}

void handleMenu(Tmatrica** pmat)
{
    int in;
    scanf("%d",&in);
    switch(in)
    {
        case 1:{ InitMat(pmat); break;}
        case 2:{ PpvMat(*pmat); break;}
        case 3:{ GetMat(*pmat); break;}
        case 4:{ SetMat(*pmat); break;}
        case 5:{ NrnpMat(*pmat); break;}
        case 6:{ PrintMat(*pmat); break;}
        case 7:{ SsMat(*pmat); break;}
        case 8:{ DelMat(pmat); break;}
        case 9:{ if(*pmat!=NULL){freeTmatrica(*pmat);} exit(0); break;}
        default: {printf("Greska: Nepostojeca opcija\r\n");break;}
    }
}

void InitMat(Tmatrica** pmat)
{
    if(*pmat==NULL)
    {
        printf("Unesite jednu dimenziju kvadratne matrice:\r\n");
        int n;
        scanf("%d",&n);
        *pmat=initTmatrica(n);
        printf("Podrazumevani element je 0\r\n");
        printf("Unesite ne podrazumevane elemente:\r\n");
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i>=j){printf("0 ");}
                else
                {
                    int v;
                    scanf("%d",&v);
                    TmSet(*pmat,i,j,v);
                }
            }
            printf("\r\n");
        }
    }
    else
    {
        printf("Greska: Matrica je vec inicijalizovana\r\n");
    }
}
void PpvMat(Tmatrica* mat)
{
    if(mat!=NULL)
    {
        printf("Unesite podrazumevani element:\r\n");
        int n;
        scanf("%d",&n);
        TmSetDefault(mat,n);
    }
    else
    {
        printf("Greska: Matrica nije inicijalizovana\r\n");
    }
}
void GetMat(Tmatrica* mat)
{
    if(mat!=NULL)
    {
        printf("Unesite indekse elementa:\r\n");
        int i,j;
        scanf("%d %d",&i,&j);
        int v=TmGet(mat,i,j);
        if(v!=INT_MIN)
        {
            printf("%d\r\n",v);
        }
    }
    else
    {
        printf("Greska: Matrica nije inicijalizovana\r\n");
    }
}
void SetMat(Tmatrica* mat)
{
    if(mat!=NULL)
    {
        printf("Unesite indekse elementa i njegovu vrednost:\r\n");
        int i,j,v;
        scanf("%d %d %d",&i,&j,&v);
        TmSet(mat,i,j,v);
    }
    else
    {
        printf("Greska: Matrica nije inicijalizovana\r\n");
    }
}
void NrnpMat(Tmatrica* mat)
{
    if(mat!=NULL)
    {
        int bnp=noEl(mat->size);
        int eq=0;
        for(int i=0;i<bnp;i++)
        {
            if(mat->array[i]==mat->defaultElement){eq++;}
        }
        printf("Ne podrazumevanih elementata ima:%d\r\n",bnp);
        printf("Od njih istu vrednost kao podrazumevani element ima:%d\r\n",eq);
    }
    else
    {
        printf("Greska: Matrica nije inicijalizovana\r\n");
    }
}
void PrintMat(Tmatrica* mat)
{
    if(mat!=NULL)
    {
        int n=mat->size;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                printf("%d ",TmGet(mat,i,j));
            }
            printf("\r\n");
        }
    }
    else
    {
        printf("Greska: Matrica nije inicijalizovana\r\n");
    }
}
void SsMat(Tmatrica* mat)
{
    if(mat!=NULL)
    {
        int sz=mat->size;
        int oz=noEl(sz)+1;
        sz=sz*sz;
        double up=100-(((double)oz/sz)*100);
        printf("Broj elemenata u standardnom zapisu matrice:%d\r\n",sz);
        printf("Broj elemenata u optimizovanom zapisu matrice:%d\r\n",oz);
        printf("procentualna usteda prostora:%.1f%%\r\n",up);
    }
    else
    {
        printf("Greska: Matrica nije inicijalizovana\r\n");
    }
}
void DelMat(Tmatrica** pmat)
{
    if(*pmat!=NULL)
    {
        freeTmatrica(*pmat);
        *pmat=NULL;
    }
    else
    {
        printf("Greska: Matrica nije inicijalizovana\r\n");
    }
}
