#ifndef CIRCLE_QUEUE_H
#define CIRCLE_QUEUE_H

/*	��ѭ��˳����в��ö�βָ��ָ��յķ�����ʵ��	*/ 
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<conio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int QElemType;

#define MAX_SIZE 1000			//ѭ�����д洢���ֵ + 1 
 
typedef struct SqQueue
{
	QElemType	*base;		//��ʼ����̬����洢�ռ� 
	int front;				//ͷָ�룬�����в�Ϊ�գ�ָ�����ͷԪ�� 
	int rear;				//βָ�룬�����в�Ϊ�գ�ָ��βԪ�ص���һ��λ�� 
}SqQueue;

//����һ���ն��� 
Status InitQueue(SqQueue &Q)
{
	Q.base = (QElemType*) malloc (MAX_SIZE*sizeof(QElemType));	//����ڵ�Ĵ洢�ռ�
	if( ! Q.base)			//�洢�ռ����ʧ��
		exit(OVERFLOW);
		
	Q.front = Q.rear = 0;	//��ͷָ��Ͷ�βָ�붼ָ��� 
	
	return OK;
}

//�ж϶����Ƿ�Ϊ��
Status EmptyQueue(SqQueue &Q)
{
	if(Q.front == Q.rear)					//��ͷָ����ڶ�βָ�� 
		return TRUE;	
	else
		return FALSE;
} 

//�ж϶����Ƿ�����
Status FullQueue(SqQueue &Q)
{
	if((Q.rear+1) % MAX_SIZE == Q.front)	//�ж϶�βָ���һȡģ�Ƿ����ͷָ�� 
		return TRUE;
	else
		return FALSE;
} 
 
//���������
Status ClearQueue(SqQueue &Q)
{
	Q.front = Q.rear = 0;	//��ͷָ����ڶ�βָ�뼴Ϊ�� 
	
	return OK;
} 

//���ٶ���
Status DestroyQueue(SqQueue &Q)
{
	if(Q.base)				//������д���
		free(Q.base);		//�ͷ� Q.base ��ָ�Ŀռ�
		
	Q.base = NULL;			// Q.base ָ��� 
	Q.front = Q.rear = 0; 	//ָ�붼ָ��� 
	
	return OK; 
} 

//����е�ʵ�ʳ���
int LengthQueue(SqQueue &Q)
{
	return (Q.rear - Q.front + MAX_SIZE) % MAX_SIZE;	//��Ϊȡģ������Ҫ���� MAX_SIZE 
} 

//���ض�ͷԪ��
Status GetHeadQueue(SqQueue &Q, QElemType &e)
{
	if(Q.front == Q.rear)	//������Ϊ�� 
		return ERROR;
		
	e = Q.base[Q.front];	//���ض�ͷԪ�� 
	
	return OK;
} 

//�õ�ѭ��������ĳһλ�õ�Ԫ��
Status GetQueue(SqQueue &Q, int i, QElemType &e)
{
	if(Q.front == Q.rear)	//������Ϊ�� 
		return ERROR;
	
	e = Q.base[i];
	
	return OK;
} 

//����Ԫ�ص���β
Status InsertQueue(SqQueue &Q, QElemType e)
{
	if((Q.rear+1) % MAX_SIZE == Q.front)	//������
		return ERROR;
		
	Q.base[Q.rear] = e;						//�� e ���ڶ�β
	Q.rear = (Q.rear+1) % MAX_SIZE;			//����βָ������һ 
	
	return OK; 
}

//ɾ����ͷԪ��
Status DeleteQueue(SqQueue &Q, QElemType &e)
{
	if(Q.front == Q.rear)					//�ж϶����Ƿ�Ϊ�� 
		return ERROR;
	
	e = Q.base[Q.front];					//��Ҫɾ����Ԫ�ظ�ֵ�� e ���� 
	Q.front = (Q.front + 1)%MAX_SIZE;		//�ƶ���ͷָ�룬��ͷָ������� 
	
	return OK; 
} 

//���������������
Status CreateQueue(SqQueue &Q, int n)
{
	int i = Q.rear;							// i ���ڶ�βָ�� 
	
	while(i < n)							//�� i С�� n ��ʱ��ѭ�� 
	{
		scanf("%d",&Q.base[i]);				//�������� 
		i = (i + 1) % MAX_SIZE;				// i ��ֵ��һ��ȡģ 
	} 
	Q.rear = i;
	 
	return OK; 
}

//��������е�����
Status PrintfQueue(SqQueue &Q)
{
	int i = Q.front;						// i ���ڶ�ͷָ�� 
	
	while(i != Q.rear)						//�� i �����ڶ�βָ��ʱѭ�� 
	{
		printf("%d ", Q.base[i]);			//���Ԫ�� 
		i = (i + 1) % MAX_SIZE;				// i ��ֵ��һ��ȡģ 
	}
	printf("\n");
	
	return OK;
} 

#endif 
