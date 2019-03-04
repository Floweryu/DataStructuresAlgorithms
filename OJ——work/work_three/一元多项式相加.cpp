#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
 
typedef struct term{
    int cof;
    int inx;
    struct term *next;
}term,*LinkList;
 
typedef LinkList polynomial;
 
//��ʼ������ 
int InitList(LinkList &L)
{
    L=(LinkList)malloc(sizeof(term));
    if(!L)
        return 0;
    L->next=NULL;
    return 1;
}
 
//�ж������Ƿ�Ϊ�գ��վͷ���1
int Empty_L(term *L)
{
    /*��ֻ��һ��ͷ����ʱ�򣬸������Ϊ��*/
    if((L->next)==NULL)      //ͷ�����NULL���� 
    return 1; 
    else
    return 0; 
}
 
//��ӡ����ʽ����
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
  
//�����������ʽ
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
 
//����ʽ�ӷ�
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
        //���Ե�printf("%d %d\n",qa->inx,qb->inx);
        if(qa->inx < qb->inx)  //pa�е�ָ������pb 
        {
            qc->cof=qb->cof;  //��С��һ���qc 
            qc->inx=qb->inx;
            qb=qb->next; //ָ����һ�� 
        }
        else if(qa->inx > qb->inx)
        {
            qc->cof=qa->cof;  //��С��һ���qc 
            qc->inx=qa->inx;
            qa=qa->next;
        }
        else    //������ 
        {
            qc->cof=qa->cof+qb->cof;    //ϵ����ӱ��浽qc 
            qc->inx=qa->inx;  //ָ������ 
            qa=qa->next;
            qb=qb->next;
        }
        if((qc->cof)!=0) //�������ϵ����Ϊ0 
        {
            qc->next=pc->next;    //��qc���뵽������ pc�� 
            pc->next=qc;
            pc=qc;      //������ָ�������� 
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
    //���Ե�printfPolynomial(pa);
    CreatePoly(pb);
    //���Ե�printfPolynomial(pb);
    addPolyn(pa,pb);
 }
