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
//返回链表的长度
int Length_L(LinkList &L)
{
	term *p;		//定义一个指针变量 
	int len=0;		//定义一个计数器，计算节点的个数 
	p=L->next;		//指针p指向链表的第一个节点 
	while(p!=NULL)
	{	
		len++;		//先加一，再移动指针，这样能在p指针指到空集时及时跳出循环从而不会多加上一 
		p=p->next;	//指针后移 
	}
	return len;		//返回链表长度 	
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
//对多项式进行降幂排序
int SortPolyn(polynomial &L) 
{
	LinkList p1,p2;
	int coff,inxx;
	p1=L->next;
	while(p1)
	{
		p2=p1->next;
		while(p2)
		{
			if(p1->inx < p2->inx)
			{
				coff=p2->cof;
				p2->cof=p1->cof;
				p1->cof=coff;
				
				inxx=p2->inx;
				p2->inx=p1->inx;
				p1->inx=inxx;
			}
			p2=p2->next;
		}
		p1=p1->next;
	}
}
//对多项式进行指数相同项合并
int MergePolyn(polynomial &L) 
{
	LinkList p1,p2,p3;
	p1=L->next;
	while(p1)
	{
		p3=p1;
		p2=p3->next;
		while(p2)
		{
			if(p1->inx == p2->inx)
			{
				
				p1->cof+=p2->cof;
				p3->next=p2->next;
				free(p2);
				p3=p3->next;
				p2=p3->next;
			}
			else
			{
				p3=p3->next;
				p2=p3->next;
			}
		}
		p1=p1->next;
	}
}
//多项式相乘 
int MulPolyn(polynomial pa,polynomial pb,LinkList &L)
{
	LinkList qa=pa->next;
	LinkList qb=pb->next;
	LinkList qc,s,pc;
	L=pc=(LinkList)malloc(sizeof(term));
	L->next=NULL;
	int i,j,cof1,inx1;
	while(qa)
	{
		cof1=qa->cof;
		inx1=qa->inx;
		qa=qa->next;
		while(qb)
		{
			qc=(LinkList)malloc(sizeof(term));

			//printf("%d %d\n",qb->cof,qb->inx);
			qc->cof=cof1*(qb->cof);
			qc->inx=inx1+qb->inx;
			//printf("%d %d\n",qc->cof,qc->inx);
			if(qc->cof==0)
			{
				free(qc);
			}
			else
			{
		
				qc->next=pc->next;		//将相乘的结果插入新链表 
				pc->next=qc;
				pc=qc;
			}
			qb=qb->next;
		}
		qb=pb->next;
	} 	

 } 
 
 int main()
 {
 	LinkList pa,pb,L;
 //	InitList(L);
 	CreatePoly(pa);
 	//printfPolynomial(pa);
 	CreatePoly(pb);
 	//printfPolynomial(pb);
	MulPolyn(pa,pb,L);
	if(Empty_L(L))
		printf("0");
	MergePolyn(L);
	SortPolyn(L);
	printfPolynomial(L);
 }
