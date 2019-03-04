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

#define MAX_SIZE 5			//循环队列存储最大值 + 1 
 
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
 
 
int main()
{
	printf("******************请按提示进行操作************************\n");
	printf("***** 初始化队列,                       enter    'a' *****\n");
	printf("***** 向队列里输入数据，                enter    'b' *****\n");
	printf("***** 判断队列是否为空，                enter    'c' *****\n");
	printf("***** 判断队列是否已满？                enter    'd' *****\n");
	printf("***** 清空队列，                        enter    'e' *****\n");
	printf("***** 销毁队列 ，                       enter    'f' *****\n");
	printf("***** 返回队列元素的个数，              enter    'g' *****\n");
	printf("***** 返回队头元素,并不删除，           enter    'h' *****\n");
	printf("***** 在队尾插入元素，                  enter    'i' *****\n");
	printf("***** 删除队头元素，并用返回其值，      enter    'j' *****\n");
	printf("***** 输出队列里的全部元素，            enter    'k' *****\n");
	printf("**********************************************************\n");
	
	SqQueue Q;		//定义队列名
	int N, back;	// N 输入的数据长度 ，back 接受返回 bool 值 
	QElemType E;	//插入值 或 接受返回值
	char str; 		//从键盘接受字符
	
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
				back = InitQueue(Q);
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
				if(N < MAX_SIZE)
					CreateQueue(Q, N);
				else
					printf("数据个数大于已定义的最大容量！！！\n");
				break;
			}
			case 'c'://判断队列是否为空
			{
				back = EmptyQueue(Q);
				if(back)
					printf("This is an empty stack. \n");
				else
					printf("This is not an empty stack.  \n");
				break;
			}
			case 'd'://判断队列是否已满
			{
				back = FullQueue(Q);
				if(back)
					printf("The queue is FULL.\n");
				else
					printf("The queue is unFULL. \n");
				break;
			} 
			case 'e'://清空队列
			{
				back = ClearQueue(Q);
				if(back)
					printf("链队列已被清空！！！\n");
				else
					printf("此队列已是空的，不需要清空！！！\n");
				break;
			}
			case 'f'://销毁队列
			{
				back = DestroyQueue(Q);
				if(back)
					printf("链队列已被销毁！！！\n");
				else
					printf("销毁失败！！！\n");
				break;
			}
			case 'g'://返回队列元素的个数
			{
				back = LengthQueue(Q);
				printf("链队列的长度是 :     %d\n",back);
				break;
			}
			case 'h'://返回队头元素,并不删除
			{
				GetHeadQueue(Q, E);
				printf("队头元素为 :   %d\n",E);
				break;
			}
			case 'i'://在队尾插入元素
			{
				printf("请输入要插入元素的值：    ");
				scanf("%d",&E);
				back = InsertQueue(Q,E);
				if(back)
				{
					printf("插入后栈内元素值变为：  ");
					PrintfQueue(Q);
					printf("\n");
				}
				else
					printf("插入元素失败！！！\n");
				break;
			}
			case 'j'://删除队头元素，并用 e 返回其值
			{
				back=DeleteQueue(Q,E);
				if(back)
					printf("删除的队头元素是：   %d\n",E);
				else
					printf("队列为空，没有元素！！！\n");
				break;
			}
			case 'k'://输出队列里的全部元素
			{
				PrintfQueue(Q);
				break;
			} 
			default:printf("wrong!\n");
		}	//end switch
	}while(str != 'q');
	return 0;
}
	
