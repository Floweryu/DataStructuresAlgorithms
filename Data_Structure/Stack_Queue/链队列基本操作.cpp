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

int main()
{
	printf("******************请按提示进行操作************************\n");
	printf("***** 初始化链队列,                     enter    'a' *****\n");
	printf("***** 向队列里输入数据，                enter    'b' *****\n");
	printf("***** 判断链队列是否为空，              enter    'c' *****\n");
	printf("***** 清空链队列，                      enter    'd' *****\n");
	printf("***** 销毁链队列 ，                     enter    'e' *****\n");
	printf("***** 返回链队列元素的个数，            enter    'f' *****\n");
	printf("***** 返回队头元素,并不删除，           enter    'g' *****\n");
	printf("***** 在队尾插入元素，                  enter    'h' *****\n");
	printf("***** 删除队头元素，并用返回其值，      enter    'i' *****\n");
	printf("***** 输出链队列里的全部元素，          enter    'j' *****\n");
	printf("**********************************************************\n");
	
	LinkQueue Q;		//定义队列的头 
	QElemType E;		//用来传递值
	int N;				//定义个数 
	int back;			//接收函数返回值 
	char str; 			//从键盘接收字符
	
	do
	{
		printf("\n");
		printf("Please enter a char:    ");
		str=getche();		/*从键盘获取一个字符并显示，不按回车直接执行*/ 
		printf("\n");
		switch(str)
		{
			case 'a'://初始化链队列
			{
				back = Init_Queue(Q);
				if(back)
					printf("已为您初始化完成一个空链队列。\n");
				else 
					printf("初始化失败！！\n");	
				break;
			}
			case 'b':// 向链队列里输入数据
			{
				printf("请输入数据的个数：  ");
				scanf("%d",&N);
				Create_Queue(Q, N);
				break;
			}
			case 'c'://判断链队列是否为空
			{
				back = Empty_Queue(Q);
				if(back)
					printf("This is an empty stack. \n");
				else
					printf("This is not an empty stack.  \n");
				break;
			}
			case 'd'://清空链队列
			{
				back = Clear_Queue(Q);
				if(back)
					printf("链队列已被清空！！！\n");
				else
					printf("此队列已是空的，不需要清空！！！\n");
				break;
			}
			case 'e'://销毁链队列
			{
				back = Destroy_Queue(Q);
				if(back)
					printf("链队列已被销毁！！！\n");
				else
					printf("销毁失败！！！\n");
				break;
			}
			case 'f'://返回链队列元素的个数
			{
				back=Length_Queue(Q);
				printf("链队列的长度是 :     %d\n",back);
				break;
			}
			case 'g'://返回队头元素,并不删除
			{
				GetHead_Queue(Q, E);
				printf("队头元素为 :   %d\n",E);
				break;
			}
			case 'h'://在队尾插入元素
			{
				printf("请输入要插入元素的值：    ");
				scanf("%d",&E);
				back=Insert_Queue(Q,E);
				if(back)
				{
					printf("插入后栈内元素值变为：  ");
					Printf_Queue(Q);
					printf("\n");
				}
				else
					printf("插入元素失败！！！\n");
				break;
			}
			case 'i'://删除队头元素，并用 e 返回其值
			{
				back=Delete_Queue(Q,E);
				if(back)
					printf("删除的栈顶元素是：   %d\n",E);
				else
					printf("栈为空，没有元素！！！\n");
				break;
			}
			case 'j'://输出链队列里的全部元素
			{
				Printf_Queue(Q);
				break;
			} 
			default:printf("wrong!\n");
		}
	}while(str!='q');
	return 0;
}
