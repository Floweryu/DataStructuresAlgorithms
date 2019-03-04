#ifndef CIRCLE_QUEUE_H
#define CIRCLE_QUEUE_H

/*	此循环顺序队列采用队尾指针指向空的方法来实现	*/ 
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

#define MAX_SIZE 1000			//循环队列存储最大值 + 1 
 
typedef struct SqQueue
{
	QElemType	*base;		//初始化动态分配存储空间 
	int front;				//头指针，若队列不为空，指向队列头元素 
	int rear;				//尾指针，若队列不为空，指向尾元素的下一个位置 
}SqQueue;

//构造一个空队列 
Status InitQueue(SqQueue &Q)
{
	Q.base = (QElemType*) malloc (MAX_SIZE*sizeof(QElemType));	//申请节点的存储空间
	if( ! Q.base)			//存储空间分配失败
		exit(OVERFLOW);
		
	Q.front = Q.rear = 0;	//队头指针和队尾指针都指向空 
	
	return OK;
}

//判断队列是否为空
Status EmptyQueue(SqQueue &Q)
{
	if(Q.front == Q.rear)					//队头指针等于队尾指针 
		return TRUE;	
	else
		return FALSE;
} 

//判断队列是否已满
Status FullQueue(SqQueue &Q)
{
	if((Q.rear+1) % MAX_SIZE == Q.front)	//判断队尾指针加一取模是否等于头指针 
		return TRUE;
	else
		return FALSE;
} 
 
//将队列清空
Status ClearQueue(SqQueue &Q)
{
	Q.front = Q.rear = 0;	//队头指针等于队尾指针即为空 
	
	return OK;
} 

//销毁队列
Status DestroyQueue(SqQueue &Q)
{
	if(Q.base)				//如果队列存在
		free(Q.base);		//释放 Q.base 所指的空间
		
	Q.base = NULL;			// Q.base 指向空 
	Q.front = Q.rear = 0; 	//指针都指向空 
	
	return OK; 
} 

//求队列的实际长度
int LengthQueue(SqQueue &Q)
{
	return (Q.rear - Q.front + MAX_SIZE) % MAX_SIZE;	//因为取模，所以要加上 MAX_SIZE 
} 

//返回队头元素
Status GetHeadQueue(SqQueue &Q, QElemType &e)
{
	if(Q.front == Q.rear)	//若队列为空 
		return ERROR;
		
	e = Q.base[Q.front];	//返回队头元素 
	
	return OK;
} 

//得到循环队列中某一位置的元素
Status GetQueue(SqQueue &Q, int i, QElemType &e)
{
	if(Q.front == Q.rear)	//若队列为空 
		return ERROR;
	
	e = Q.base[i];
	
	return OK;
} 

//插入元素到队尾
Status InsertQueue(SqQueue &Q, QElemType e)
{
	if((Q.rear+1) % MAX_SIZE == Q.front)	//队列满
		return ERROR;
		
	Q.base[Q.rear] = e;						//将 e 插在队尾
	Q.rear = (Q.rear+1) % MAX_SIZE;			//将队尾指针向后加一 
	
	return OK; 
}

//删除队头元素
Status DeleteQueue(SqQueue &Q, QElemType &e)
{
	if(Q.front == Q.rear)					//判断队列是否为空 
		return ERROR;
	
	e = Q.base[Q.front];					//把要删除的元素赋值给 e 返回 
	Q.front = (Q.front + 1)%MAX_SIZE;		//移动队头指针，队头指针向后移 
	
	return OK; 
} 

//向队列中输入数据
Status CreateQueue(SqQueue &Q, int n)
{
	int i = Q.rear;							// i 等于队尾指针 
	
	while(i < n)							//当 i 小于 n 的时候循环 
	{
		scanf("%d",&Q.base[i]);				//输入数据 
		i = (i + 1) % MAX_SIZE;				// i 的值加一后取模 
	} 
	Q.rear = i;
	 
	return OK; 
}

//输出队列中的数据
Status PrintfQueue(SqQueue &Q)
{
	int i = Q.front;						// i 等于队头指针 
	
	while(i != Q.rear)						//当 i 不等于队尾指针时循环 
	{
		printf("%d ", Q.base[i]);			//输出元素 
		i = (i + 1) % MAX_SIZE;				// i 的值加一后取模 
	}
	printf("\n");
	
	return OK;
} 

#endif 
