/*
	Name: 链队列基本操作头文件 
	Author: 张俊峰 
	Date: 14/11/18 13:54
	Description: 在以前头文件的基础上加入了二叉树的结构体，把链队列的数据对象换成了树节点。 
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
	TElemType data;		//结点的值
	BinTreeNode *lchild, *rchild;		//左右孩子指针 
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
	QueuePtr front,rear;		//队头，队尾指针 
};

//初始化定义一个空的队列
Status Init_Queue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr) malloc (sizeof(QNode));
	
	if( ! Q.front)				//判断空间是否申请成功 
		exit(OVERFLOW);
		
	Q.front->next = NULL;		//头结点的 next 域为空 
	
	return OK;
}
 
//判断链队列是否为空
Status Empty_Queue(LinkQueue &Q)
{
	if(Q.front->next == NULL)	//如果头结点的 next 域为空 
		return TRUE;
	else
		return FALSE;
} 

//创建指定长度的链队列
void Create_Queue(LinkQueue &Q, int n)
{
	QueuePtr p;										//定义 p 指针，申请新节点空间 
	int i;											//计数器 
	
	for(i = 0; i < n; i++)
	{
		p = (QueuePtr) malloc (sizeof(QNode));		//申请新节点空间 
		if( ! p)									//判断空间是否申请成功 
			exit(OVERFLOW);
		
		scanf("%d", &p->data);						//向新节点中写入数据 
			
		p->next = NULL;								// p 的后继指向空 
		Q.rear->next = p;							//原来队尾节点的指针指向新节点 
		Q.rear = p;									//队尾指针指向新节点 
	}
 } 

//将链队列清空
Status Clear_Queue(LinkQueue &Q)
{
	QueuePtr p, q;				//定义两个指针 
			
	p = Q.front->next;			// p 指向第一个结点 
	while( ! p)					//释放存储节点 
	{		
		q = p;					// q 指针指向 p 
		p = p->next;			// p 指向下一个节点 
		free(q);				//释放 q 节点 
	}
		
	Q.front = Q.rear;			//回到初始化状态 
	Q.front->next = NULL;
		
	return OK;
} 

//销毁链队列
Status Destroy_Queue(LinkQueue &Q)
{
	while(Q.front)				//Q.front不为空 
	{
		Q.rear = Q.front->next;	//Q.rear 指向 Q.front 的下一个节点 
		free(Q.front);			//释放 Q.front 
		Q.front = Q.rear;		// Q.front 指向 Q.rear 
	}
	return OK;
}

//求队列的长度
int Length_Queue(LinkQueue &Q)
{
	int i = 0;				//计数器
	QueuePtr p = Q.front;	// p 指向头结点 
	
	while(p != Q.rear)
	{
		i++;
		p = p->next;		// p 指向下一个节点 
	} 
	
	return i;
}

//返回队头元素
Status GetHead_Queue(LinkQueue &Q, QElemType &e)
{
	QueuePtr p;				//定义指针 
	
	if(Q.front == Q.rear)	//判断队列是否为空 
		return ERROR;
	
	p = Q.front->next;		// p 指向第一个结点 
	e = p->data;			//将队头元素赋值给 e 
	
	return OK;
} 

//插入元素到队尾
Status Insert_Queue(LinkQueue &Q, QElemType e)
{
	QueuePtr p;								//定义申请新节点的指针 
	
	p = (QueuePtr) malloc (sizeof(QNode));	//申请新的存储空间 
	if( ! p)								//判断空间是否申请成功 
		exit(OVERFLOW);
		
	p->data = e;							//将要插入的值赋给 p 指针 
	
	p->next = NULL;							//新节点的后继指向空 
	Q.rear->next = p;						//队尾指针的后继指向新节点 
	Q.rear = p;								//队尾指针指向新节点 
				
	return OK;
}

//删除队头元素
Status Delete_Queue(LinkQueue &Q, QElemType &e)
{
	QueuePtr p;					//定义指针 
	
	if (Q.front == Q.rear)
		return ERROR;
		
	p = Q.front->next;			// p 指向第一个结点 
	e = p->data;				//将要删除元素赋给 e 
	
	Q.front->next = p->next;	//头指针的后继指向 p 的下一个节点 
	
	if (Q.rear == p)			//若删除的是队尾节点 
		Q.rear = Q.front;		//队尾指针指向头结点 
		
	free(p);					//释放 p 节点 
			
	return OK;
} 

//输出队列元素
void Printf_Queue(LinkQueue &Q)
{
	QueuePtr p;					//定义遍历指针 
	
	p = Q.front->next;			// p 指向第一个结点 
	while(p)			//当 p 未指向未节点时 
	{
		printf("%d ",p->data);	//输出元素 
		p = p->next;
	}
	printf("\n"); 
} 

#endif 
