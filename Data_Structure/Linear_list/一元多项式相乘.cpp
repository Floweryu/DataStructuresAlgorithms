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
//��������ĳ���
int Length_L(LinkList &L)
{
	term *p;		//����һ��ָ����� 
	int len=0;		//����һ��������������ڵ�ĸ��� 
	p=L->next;		//ָ��pָ������ĵ�һ���ڵ� 
	while(p!=NULL)
	{	
		len++;		//�ȼ�һ�����ƶ�ָ�룬��������pָ��ָ���ռ�ʱ��ʱ����ѭ���Ӷ���������һ 
		p=p->next;	//ָ����� 
	}
	return len;		//���������� 	
 } 

//�ж������Ƿ�Ϊ�գ��վͷ���1
int Empty_L(term *L)
{
	/*��ֻ��һ��ͷ����ʱ�򣬸������Ϊ��*/
	if((L->next)==NULL)		//ͷ�����NULL���� 
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
//�Զ���ʽ���н�������
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
//�Զ���ʽ����ָ����ͬ��ϲ�
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
//����ʽ��� 
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
		
				qc->next=pc->next;		//����˵Ľ������������ 
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
