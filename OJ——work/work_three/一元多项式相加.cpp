#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
 
typedef struct term{
    int cof;
    int inx;
    struct term *next;
}term,*LinkList;
 
typedef LinkList polynomial;
 
//初始化链表 
int InitList(LinkList &L)
{
    L=(LinkList)malloc(sizeof(term));
    if(!L)
        return 0;
    L->next=NULL;
    return 1;
}
 
//判断链表是否为空；空就返回1
int Empty_L(term *L)
{
    /*当只有一个头结点的时候，该链表就为空*/
    if((L->next)==NULL)      //头结点与NULL相连 
    return 1; 
    else
    return 0; 
}
 
//打印多项式链表
void printfPolynomial(polynomial &P)
{
    LinkList q=P->next;
    while(q)
    {
        printf("%d %d ",q->cof,q->inx);
        q=q->next;
    }
    printf("\n");
 } 
  
//创建输入多项式
int CreatePoly(polynomial &L)
{
    LinkList p,q;
    L=(LinkList)malloc(sizeof(term));
    q=L;
    int c,e;
    while(scanf("%d %d",&c,&e)!=EOF&&e>=0)
    {
        p=(LinkList)malloc(sizeof(term));
        p->cof=c;
        p->inx=e;
         
        q->next=p;
        q=q->next;
    }
    q->next=NULL;
 } 
 
//多项式加法
int addPolyn(polynomial pa,polynomial pb)
{
    LinkList qa=pa->next;
    LinkList qb=pb->next;
    LinkList L,qc,s,pc;
    L=pc=(LinkList)malloc(sizeof(term));
    L->next=NULL;
    while(qa!=NULL&&qb!=NULL)
    {
        qc=(LinkList)malloc(sizeof(term));
        //测试点printf("%d %d\n",qa->inx,qb->inx);
        if(qa->inx < qb->inx)  //pa中的指数大于pb 
        {
            qc->cof=qb->cof;  //将小的一项赋给qc 
            qc->inx=qb->inx;
            qb=qb->next; //指向下一个 
        }
        else if(qa->inx > qb->inx)
        {
            qc->cof=qa->cof;  //将小的一项赋给qc 
            qc->inx=qa->inx;
            qa=qa->next;
        }
        else    //如果相等 
        {
            qc->cof=qa->cof+qb->cof;    //系数相加保存到qc 
            qc->inx=qa->inx;  //指数不变 
            qa=qa->next;
            qb=qb->next;
        }
        if((qc->cof)!=0) //如果该项系数不为0 
        {
            qc->next=pc->next;    //将qc插入到新链表 pc中 
            pc->next=qc;
            pc=qc;      //新申请指针向下移 
        }
        else
        free(qc);
    }
    while(qa!=NULL)
    {
        qc=(LinkList)malloc(sizeof(term));
        qc->cof=qa->cof;
        qc->inx=qa->inx;
        qa=qa->next;
        qc->next=pc->next;
        pc->next=qc;
        pc=qc;
    }
    while(qb!=NULL)
    {
        qc=(LinkList)malloc(sizeof(term));
        qc->cof=qb->cof;
        qc->inx=qb->inx;
        qb=qb->next;
        qc->next=pc->next;
        pc->next=qc;
        pc=qc;
    }
    if(Empty_L(L))
    printf("0\n");
    printfPolynomial(L);
 } 
  
 int main()
 {
    LinkList pa,pb;
    CreatePoly(pa);
    //测试点printfPolynomial(pa);
    CreatePoly(pb);
    //测试点printfPolynomial(pb);
    addPolyn(pa,pb);
 }
