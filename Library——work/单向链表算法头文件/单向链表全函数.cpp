#include "stdio.h"
#include "stdlib.h"
#include "conio.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int ElemType;

typedef struct LNode{
	ElemType	data;	//������ 
	struct LNode	*next;	//ָ���� 
}LNode,*LinkList;

//��ʼ������ 
void InitList(LNode *L)
{
	L=(LinkList)malloc(sizeof(LNode));
	if(!L)
		exit(OVERFLOW);
	L->next=NULL;
 } 
//����Ĵ�����������	
int Create_L(LNode *L,int n)
{
	LNode *p,*q;
	q=L;
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
 
//���򴴽�һ�������� 
int reCreate_L(LNode *L,int n)
{
	LNode *p;
	L=(LinkList)malloc(sizeof(LNode));	//����ͷ��㣬��qָ��ָ��ͷ��㣬Ϊ�Ժ���p������ 
		//����һ����ͷ���ĵ�����
	L->next=NULL;
	int i;
	for(i=0;i<n;i++)	
	{
		p=(LinkList)malloc(sizeof(LNode));	//�����½ڵ�
		scanf("%d",&p->data);		//�������� 
		p->next=L->next;
		L->next=p;
	}
 } 
 
//��ӡ��������е�����
int Printf_L(LNode *L)
{
	LNode *p;
	p=L->next;		//ʹpָ��ָ������ĵ�һ������
	while(p!=NULL)
	{
		printf("%d ",p->data);
		p=p->next;		//ָ����� 
	} 
 } 
 
//��������ĳ���
int Length_L(LNode *L)
{
	LNode *p;		//����һ��ָ����� 
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
int Empty_L(LNode *L)
{
	/*��ֻ��һ��ͷ����ʱ�򣬸������Ϊ��*/
	if((L->next)==NULL)		//ͷ�����NULL���� 
	return OK; 
	else
	return ERROR; 
}

//����i��Ԫ�ش���ʱ������ֵ����e������OK
int iGetElem_L(LNode *L,int i,ElemType *e)
{
	LNode *p;
	p=L->next;		//ʹpָ��ͷ��� 
	int j=1;		//jΪ������ 
	while(p&&j<i)	//˳ָ�������ң�֪��pָ���i��Ԫ�ػ�pΪ�� 
	{
		p=p->next;   //�������� 
		j++;		//��¼������λ�úʹ��� 
	}
	if(!p||j>i)
		return ERROR;
	*e=p->data;		//�˳�while()ѭ��ʱp��ָ���Ѿ�ָ����һ��Ԫ�ص�ַ 
	return OK; 
}

//��ֵ����Ѱ��Ԫ��e������e��λ��
int eGetElem_L(LNode *L,ElemType e)
{
	LNode *p;
	p=L->next;		//p����ͷ��� 
	int count=0;
	while(p!=NULL)
	{
		count++;	//λ���ȼ�һ����������ѭ�����һ 
		if(p->data==e)	//�ж� 
		return (count);		//����λ��ֵ 
		p=p->next;		//pָ����һ����� 
	}
	return ERROR;
 } 
 

//��������ָ��λ��i��֮ǰ����������
//���а����ڱ�ͷ���롢�ڱ�β���롢�ڱ��в�������λ��
int Insert_L(LNode *L,int i,ElemType *e)
{
	LNode *p,*s;
	p=L;
	int j=0;
	while(p&&j<i-1)		//������L���ǿձ�ʱ���ҵ�ǰλ��С��i-1 
	{  //Ҫ�ҵ���i-1���ڵ��λ�þ�Ҫ�ڵ�i-2���ڵ㴦ֹͣѭ������Ϊѭ�����������ƶ�ָ����һ��ָ���j�ȵ�i-1�� 
		p=p->next;		//�������� 
		j++;
	}			//������ѭ��ʱpָ��ָ���i-1��Ԫ�� 
	if(!p||j>i-1)
	return ERROR;
	s=(LinkList)malloc(sizeof(LNode));
	s->data=*e;		//��Ҫ��������ݸ��� sָ�� 
	s->next=p->next;	//p->nextָ���i��Ԫ�أ��ѵ�i��Ԫ�ص�ǰ���ӵ�Ҫ����ڵ�ĺ��� 
	p->next=s;		//��i-1�ڵ�ĺ����ӵ�Ҫ����Ԫ�ص�ǰ�� 
	return OK;
 } 
 
//ɾ����i��Ԫ�أ�����e������ֵ��
//���а���ɾ���Ľڵ��Ǳ�ͷ�����м�
int Delete_L(LNode *L,int i,ElemType *e)
{
	LNode *p,*s;
	int j=0;
	p=L;
	while(p->next&&j<i-1)
	{
		p=p->next;
		j++;
	}		//����ѭ��ʱpָ���i-1���ڵ� 
	if(!p->next||j>i-1)
	return ERROR;
	s=p->next;   //sָ��ָ���i���ڵ� 
	p->next=s->next;//��i-1���ڵ�ĺ������i���ڵ����������i+1���ڵ��ǰ���� 
	*e=s->data;	//�ѵ�i���ڵ��ֵ����e���� 
	free(s);	//�ͷŵ�i���ڵ�Ŀռ� 
	return OK;
}

//ɾ�������������е��ظ�Ԫ��	
int reDelete_L(LNode *L)
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

//�Ե��������������� 
/*��Ҫ˼�룺��ԭ��������ݴ�ͷ��βͨ���������������Ӻ���룩���뵽�������У�
			(�൱������������),Ȼ�������������*/ 
int rePrintf_L(LNode *L,int n)
 {
 	LNode *p,*s,*q;
 	LinkList L0;		/*����һ���µ����������洢��ת�������*/ 
 	L0=(LinkList)malloc(sizeof(LNode));
 	p=L->next;		/*pָ��ԭ�������һ��*/ 
 	L0->next==NULL;	/*��������г�ʼ��*/ 
 	while(p!=NULL)	/*ָ��û���ռ�ʱѭ��*/ 
 	{
 		q=(LinkList)malloc(sizeof(LNode));/*����һ���½ڵ������洢��תԪ��*/ 
 		q->data=p->data;	/*��ԭ��L��������ݰ���ͷ��㵽β��˳�򸳸�������L0�ڵ�q��*/ 
 		q->next=L0->next;	/*���½ڵ���β�巨����������L0�ĺ��濪ʼ�洢*/ 
 		L0->next=q;		
 		p=p->next;	/*����ԭ����L*/ 
 	}
 	s=L0->next;		/*��������L0�������*/ 
 	for(int i=0;i<n;i++)	/*������while(p!=NULL)�����������ѭ��(û������)�������ֵ��Ŀǰ��֪����ô��*/ 
 	{
 		printf("%d ",s->data);
 		s=s->next;
	 }
	 printf("\n");
 }


