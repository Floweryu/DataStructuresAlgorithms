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
	if((L->next)==NULL)		//头结点与NULL相连 
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

//多项式减法 
int addPolyn(polynomial pa,polynomial pb)
{
	LinkList qa=pa->next;	//qa指向第一个结点 
	LinkList qb=pb->next;	//qb指向第一个结点 
	LinkList L,qc,s,pc;
	L=pc=(LinkList)malloc(sizeof(term));	//定义一个存储和的新链表 
	L->next=NULL;	
	while(qa!=NULL&&qb!=NULL)
	{
		qc=(LinkList)malloc(sizeof(term));	//为新链表申请一个结点 
		//测试点printf("%d %d\n",qa->inx,qb->inx);
		if(qa->inx < qb->inx)	//pa中的指数小于pb 
		{
			qc->cof=qb->cof;	//将大的一项赋给qc 
			qc->inx=qb->inx;
			qb=qb->next;	//移动大的一项的指针 
		}
		else if(qa->inx > qb->inx)
		{
			qc->cof=qa->cof;	//将大的一项赋给qc 
			qc->inx=qa->inx;
			qa=qa->next;	//移动大的一项的指针 
		}
		else	//如果相等 
		{
			qc->cof=qa->cof - qb->cof;	 //系数相加保存到qc 
			qc->inx=qa->inx;	//指数不变 
			qa=qa->next;
			qb=qb->next;
		}
		if((qc->cof)!=0)	//如果该项系数不为0 
		{
			qc->next=pc->next;	//将qc插入到新链表 pc中 
			pc->next=qc;
			pc=qc;		//新申请指针向下移 
		}
		else
		free(qc);
	}
	while(qa!=NULL)	//当qa链表中还有多余的数据时 
	{
		qc=(LinkList)malloc(sizeof(term));	//申请新节点 
		qc->cof=qa->cof;	//把多余数据的系数赋给qc 
		qc->inx=qa->inx;	//把多余数据的指数赋给qc 
		qa=qa->next;		//qa指针向后移 
		qc->next=pc->next;	//qc的指针也向后移 
		pc->next=qc;	//pc指针跟随新节点 
		pc=qc;
	}
	while(qb!=NULL)	//当qb链表中还有多余的数据时，多余项要变成负数 
	{
		qc=(LinkList)malloc(sizeof(term));
		qc->cof=0-qb->cof;		//多余项要变成负数 
		qc->inx=qb->inx;
		qb=qb->next;
		qc->next=pc->next;
		pc->next=qc;
		pc=qc;
	}
	if(Empty_L(L))	//如果链表为空	 
	printf("0\n");	//输出0 
	printfPolynomial(L);	//输出结果 
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
