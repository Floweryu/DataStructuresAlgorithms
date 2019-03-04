#include<stdio.h>
#include<stdlib.h>
 
#define   TRUE                    1
#define   FALSE                    0
#define   OK                    1
#define   ERROR                    0
#define   OVERFLOW                -2
#define   INFEASIBLE            -1
 
typedef int ElemType;
 
typedef struct  OLNode
{
    int i,j;
    ElemType e;
    struct OLNode  *right, *down;
}OLNode, *OLink;
typedef struct
{
    OLink *rhead, *chead;
    int mu,nu,tu;
}CrossList;
int CreateSMatrix_OL(CrossList *M)
{
    if(M)  free(M);
    int m,n,t=0;
    scanf("%d%d",&m,&n);
    M->mu=m; M->nu=n;
    if(!(M->rhead=(OLink *)malloc((m+1)*sizeof(OLink))))   return ERROR;
    if(!(M->chead=(OLink *)malloc((n+1)*sizeof(OLink))))   return ERROR;
    int a,b;
    for (a=1;a<=m;a++)   M->rhead[a]=NULL;
    for (b=1;b<=n;b++)   M->chead[b]=NULL;
    int i,j,e;
    for(i=1;i<=m;i++)
    {
        for(j=1;j<=n;j++)
        {
            scanf("%d",&e);
            if(e!=0)
            {
                t++;
                OLNode *p,*q;
                if(!(p=(OLNode *)malloc(sizeof(OLNode))))   return ERROR;
                p->i=i; p->j=j; p->e=e; p->down=NULL; p->right=NULL;
                if(M->rhead[i]==NULL||M->rhead[i]->j>j)
                {
                    p->right=M->rhead[i];   M->rhead[i]=p;
                }
                else
                {
                    for(q=M->rhead[i];(q->right)&&q->right->j<j;q=q->right);
                    p->right=q->right;    q->right=p;
                }
                if(M->chead[j]==NULL||M->chead[j]->i>i)
                {
                    p->down=M->chead[j];   M->chead[j]=p;
                }
                else
                {
                   for(q=M->chead[j];(q->down)&&q->down->i<i;q=q->down);
                   p->down=q->down;   q->down=p;
                }
            }
        }
    }
    M->tu=t;
    return OK;
}
void print(CrossList M)
{
    int p,q;
    OLNode *pTemp;
    for(p=1;p<=M.mu;p++)
    {
        pTemp=M.rhead[p];
        for(q=1;q<=M.nu;q++)
        {
            if(pTemp!=NULL&&pTemp->j==q)
            {
                printf("%d ",pTemp->e);
                pTemp=pTemp->right;
            }
            else
                printf("0 ");
        }
        printf("\n");
    }
    return ;
}
int main()
{
    CrossList M;
    CreateSMatrix_OL(&M);
    print(M);
    return 0;
}


