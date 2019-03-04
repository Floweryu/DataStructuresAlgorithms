/*
	Name: �����л�������ͷ�ļ� 
	Author: �ſ��� 
	Date: 14/11/18 13:54
	Description: ����ǰͷ�ļ��Ļ����ϼ����˶������Ľṹ�壬�������е����ݶ��󻻳������ڵ㡣 
*/

#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H 


#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<conio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef char TElemType;

typedef struct BinTreeNode
{
	TElemType data;		//����ֵ
	BinTreeNode *lchild, *rchild;		//���Һ���ָ�� 
}BinTreeNode, *BinTree;

typedef int Status;
typedef BinTree QElemType;

typedef struct QNode
{
	QElemType	data;
	QNode 		*next;
}*QueuePtr;

struct LinkQueue
{
	QueuePtr front,rear;		//��ͷ����βָ�� 
};

//��ʼ������һ���յĶ���
Status Init_Queue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr) malloc (sizeof(QNode));
	
	if( ! Q.front)				//�жϿռ��Ƿ�����ɹ� 
		exit(OVERFLOW);
		
	Q.front->next = NULL;		//ͷ���� next ��Ϊ�� 
	
	return OK;
}
 
//�ж��������Ƿ�Ϊ��
Status Empty_Queue(LinkQueue &Q)
{
	if(Q.front->next == NULL)	//���ͷ���� next ��Ϊ�� 
		return TRUE;
	else
		return FALSE;
} 

//����ָ�����ȵ�������
void Create_Queue(LinkQueue &Q, int n)
{
	QueuePtr p;										//���� p ָ�룬�����½ڵ�ռ� 
	int i;											//������ 
	
	for(i = 0; i < n; i++)
	{
		p = (QueuePtr) malloc (sizeof(QNode));		//�����½ڵ�ռ� 
		if( ! p)									//�жϿռ��Ƿ�����ɹ� 
			exit(OVERFLOW);
		
		scanf("%d", &p->data);						//���½ڵ���д������ 
			
		p->next = NULL;								// p �ĺ��ָ��� 
		Q.rear->next = p;							//ԭ����β�ڵ��ָ��ָ���½ڵ� 
		Q.rear = p;									//��βָ��ָ���½ڵ� 
	}
 } 

//�����������
Status Clear_Queue(LinkQueue &Q)
{
	QueuePtr p, q;				//��������ָ�� 
			
	p = Q.front->next;			// p ָ���һ����� 
	while( ! p)					//�ͷŴ洢�ڵ� 
	{		
		q = p;					// q ָ��ָ�� p 
		p = p->next;			// p ָ����һ���ڵ� 
		free(q);				//�ͷ� q �ڵ� 
	}
		
	Q.front = Q.rear;			//�ص���ʼ��״̬ 
	Q.front->next = NULL;
		
	return OK;
} 

//����������
Status Destroy_Queue(LinkQueue &Q)
{
	while(Q.front)				//Q.front��Ϊ�� 
	{
		Q.rear = Q.front->next;	//Q.rear ָ�� Q.front ����һ���ڵ� 
		free(Q.front);			//�ͷ� Q.front 
		Q.front = Q.rear;		// Q.front ָ�� Q.rear 
	}
	return OK;
}

//����еĳ���
int Length_Queue(LinkQueue &Q)
{
	int i = 0;				//������
	QueuePtr p = Q.front;	// p ָ��ͷ��� 
	
	while(p != Q.rear)
	{
		i++;
		p = p->next;		// p ָ����һ���ڵ� 
	} 
	
	return i;
}

//���ض�ͷԪ��
Status GetHead_Queue(LinkQueue &Q, QElemType &e)
{
	QueuePtr p;				//����ָ�� 
	
	if(Q.front == Q.rear)	//�ж϶����Ƿ�Ϊ�� 
		return ERROR;
	
	p = Q.front->next;		// p ָ���һ����� 
	e = p->data;			//����ͷԪ�ظ�ֵ�� e 
	
	return OK;
} 

//����Ԫ�ص���β
Status Insert_Queue(LinkQueue &Q, QElemType e)
{
	QueuePtr p;								//���������½ڵ��ָ�� 
	
	p = (QueuePtr) malloc (sizeof(QNode));	//�����µĴ洢�ռ� 
	if( ! p)								//�жϿռ��Ƿ�����ɹ� 
		exit(OVERFLOW);
		
	p->data = e;							//��Ҫ�����ֵ���� p ָ�� 
	
	p->next = NULL;							//�½ڵ�ĺ��ָ��� 
	Q.rear->next = p;						//��βָ��ĺ��ָ���½ڵ� 
	Q.rear = p;								//��βָ��ָ���½ڵ� 
				
	return OK;
}

//ɾ����ͷԪ��
Status Delete_Queue(LinkQueue &Q, QElemType &e)
{
	QueuePtr p;					//����ָ�� 
	
	if (Q.front == Q.rear)
		return ERROR;
		
	p = Q.front->next;			// p ָ���һ����� 
	e = p->data;				//��Ҫɾ��Ԫ�ظ��� e 
	
	Q.front->next = p->next;	//ͷָ��ĺ��ָ�� p ����һ���ڵ� 
	
	if (Q.rear == p)			//��ɾ�����Ƕ�β�ڵ� 
		Q.rear = Q.front;		//��βָ��ָ��ͷ��� 
		
	free(p);					//�ͷ� p �ڵ� 
			
	return OK;
} 

//�������Ԫ��
void Printf_Queue(LinkQueue &Q)
{
	QueuePtr p;					//�������ָ�� 
	
	p = Q.front->next;			// p ָ���һ����� 
	while(p)			//�� p δָ��δ�ڵ�ʱ 
	{
		printf("%d ",p->data);	//���Ԫ�� 
		p = p->next;
	}
	printf("\n"); 
} 

#endif 
