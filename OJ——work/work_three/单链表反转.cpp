#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int ElemType;

typedef struct LNode{
	ElemType	data;	//������ 
	struct LNode	*next;	//ָ���� 
}LNode,*LinkList;

/*�������� Create_L()
  ���ܣ�����Ĵ�����������	*/	
int Create_L(LinkList &L,int n)
{
	LNode *p,*q;
	L=q=(LinkList)malloc(sizeof(LNode));	//����ͷ��㣬��qָ��ָ��ͷ��㣬Ϊ�Ժ���p������ 
		//����һ����ͷ���ĵ����� 
	int i;
	for(i=0;i<n;i++)	
	{
		p=(LinkList)malloc(sizeof(LNode));	//�����½ڵ�
		scanf("%d",&p->data);		//�������� 
		//�������д����൱�ڰ�p�����뵽�����У����Ǵ�ͷ��β��˳����� 
		p->next=NULL;		//p������һ����ַָ��NULL,�����½ڵ��ָ��p����һ����ַ��Զָ��NULL 
		q->next=p;			//q����һ����ַָ��p����ָ��p��ǰ��Ҫ����һ��Ԫ�صĺ������� 
		q=p;		//�ѵ�ǰ�Ѳ���Ľڵ��ַ����q���Ա�������ı��� 
	}
 }

 int Printf_L(LinkList L)
{
	LNode *p;
	p=L->next;		//ʹpָ��ָ������ĵ�һ������
	while(p!=NULL)
	{
		printf("%d ",p->data);
		p=p->next;		//ָ����� 
	} 
	printf("\n");
 } 
/*
 int reP_L(LinkList L)
 {
 	if(L->next!=NULL)
 		reP_L(L->next);
 		printf("%d ",L->data);
 }
 */
 int rePrintf_L(LinkList &L,int n)
 {
 	LNode *p,*s,*q;
 	LinkList L0;
 	L0=(LinkList)malloc(sizeof(LNode));
 	p=L->next;
 	L0->next==NULL;
 	while(p!=NULL)
 	{
 		q=(LinkList)malloc(sizeof(LNode));
 		q->data=p->data;
 		q->next=L0->next;
 		L0->next=q;
 		p=p->next;
 	}
 	s=L0->next;
 	for(int i=0;i<n;i++)
 	{
 		printf("%d ",s->data);
 		s=s->next;
	 }
	 printf("\n");
 }
 int main()
 {
 	LinkList La;
 	int N;
 	while(scanf("%d",&N)!=EOF)
 	{
 		if(!N)
 		printf("list is empty\n");
 		else
 		{
 			Create_L(La,N);
 			Printf_L(La);
 			rePrintf_L(La,N);
 		}
 	}
 	
 }
