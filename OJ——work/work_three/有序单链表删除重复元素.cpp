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
 
 /*��������reDelete_L 
 	���ܣ�ɾ�������������е��ظ�Ԫ��	*/
int reDelete_L(LinkList &L)
{
	LNode *p,*s,*q;
	p=L->next;
	q=p->next;
	while(q!=NULL)
	{
		if(p->data==q->data)
		{
			p->next=q->next;
			s=q;
			q=q->next;
			free(s);
		}
		else
		{
			p=p->next;
			q=q->next;
		}
	}
 } 
 
 int Printf_L(LinkList &L)
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
 			reDelete_L(La);
 			Printf_L(La);
 		}
 	}
 }
