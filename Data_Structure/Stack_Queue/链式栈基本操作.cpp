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
typedef int SElemType;		//定义栈中的数据类型 

typedef struct SqStack
{
	SElemType data;	  		//数据域 
	struct SqStack *next;	//指针域 
}SqStack,*LinkStack;

//初始化链栈
/* 建立一个空栈，创建链栈的头结点，将其NULL置空	*/
Status Init_Stack(LinkStack *S)
{
	*S = (LinkStack) malloc (sizeof(SqStack));	//申请头结点空间
	
	if(*S == NULL)								//判断新空间是否分配成功 
		exit(OVERFLOW);
		
	(*S)->next = NULL;							//头结点后继指向空 
	
	return OK;
} 

//向栈里输入数据
Status Create_Stack(LinkStack *S,int n)
{
	LinkStack q;			// q 指针用来申请新的节点 
	int i;					//计数器 
	
	for(i = 0; i < n; i++)	//在栈顶位置依次插入元素 
	{
		q = (LinkStack) malloc (sizeof (SqStack));	//申请空间 
		if(q == NULL)				//判断空间是否申请成功 
			exit(OVERFLOW);	
			
		scanf("%d", &q->data);		//向新空间里输入数据 
		
		q->next = (*S)->next;		// q 的后继指向头结点 S 的后继 
		(*S)->next = q;				//头结点 S 的后继指向 q  
	}
	return OK; 
} 

//判断链栈是否为空 
Status Empty_Stack(LinkStack *S)
{
	LinkStack p;
	
	p = (*S)->next;
	if(!p)				//如果头结点的后继指向NULL，即为空 返回真 
		return OK;
	else
		return FALSE; 	//否则，不为空 
}

//清空链栈
Status Clear_Stack(LinkStack *S)
{
	LinkStack p,q;
	
	p = (*S)->next;			// p 指向第一个节点 
	while(p != NULL)		//当 p 不指向空的时候循环 
	{
		q = p->next;		// q 指向 p 的下一个节点 
		free(p);			//释放 p 节点 
		p = q;				// p 重新指向 q 节点 
	}
	
	(*S)->next = NULL;		//节点释放完后，是栈头结点指向NULL，回到初始化状态 
	return OK;
	
} 

//销毁链栈
Status Destroy_Stack(LinkStack *S)
{
	LinkStack p,q;
	
	p = (*S)->next;		// p 指向第一个节点 
	while(p != NULL)	//当 p 不指向空的时候循环 
	{
		q = p->next;	// q 指向 p 的下一个节点 
		free(p);		//释放 p 节点 
		p = q;			// p 重新指向 q 节点 
	}
	
	free(S);			//再把头结点释放 
	return OK;
} 

//返回链栈元素的个数
Status Length_Stack(LinkStack *S)
{
	if((*S)->next == NULL)	//如果头结点的后继指向NULL，即为空 返回真 
		return ERROR;
		
	LinkStack p;			//定义一个指针用来遍历 
	int len = 0;			//定义一个整形变量，计数器，用来统计栈的长度 ,初始值为0. 
	
	p = (*S)->next;			//p指针指向第一个结点
	while(p != NULL)		//当p还未到NULL的时候遍历 
	{
		len++; 				//计数器加一 
		p = p->next; 		//p指向下一个节点 
	} 
	
	return len;				//返回计数器的值，即链栈的长度 
} 

//若链栈不为空，就返回栈顶元素,并不删除 
Status GetTop_Stack(LinkStack *S)
{
	if((*S)->next == NULL)			//判断链栈是否为空 
		return ERROR;	
	else
	{
		return (*S)->next->data;	//不为空，就返回第一个结点的元素 
	}
} 

//在栈顶插入元素
Status Push_Stack(LinkStack *S,SElemType e)
{
	LinkStack p;			//定义一个指针，用来指向要插入元素 
	
	p = (LinkStack)malloc(sizeof(SqStack));	//为指针 p 申请存储空间
	if(p == NULL)			//判断空间是否申请成功 
		exit(OVERFLOW); 
		
	p->data = e;			// 把要插入的值赋给p的数据域 
	p->next = (*S)->next;	// p 的后继指向头结点的后继 
	(*S)->next = p;			// p 的前驱指向头结点的后继
	
	return OK;				//插入成功，返回真 
} 
 
//删除栈顶元素，并用 e 返回其值 
Status  Pop_Stack(LinkStack *S, SElemType *e)
{
	if((*S)->next == NULL)	//判断链栈是否为空栈 
		return ERROR; 
	
	LinkStack p;
	
	p = (*S)->next;			// p 指向栈顶元素 
	(*S)->next = p->next;	//头结点 S 的后继指向栈顶元素的下一个元素 
	*e = p->data;			//把栈顶存储的值赋给 e 返回 
	
	free(p);				//释放栈顶节点 
	
	return OK;
}

//输出链栈里的全部元素
Status Printf_Stack(LinkStack *S)
{
	if((*S)->next == NULL)		//判断链栈是否为空 
		return ERROR;
		 
	LinkStack p;
	p = (*S)->next;				// p 指向栈顶节点 
	
	while(p != NULL)			//当 p 没有指向空的时候循环 
	{
		printf("%d ",p->data);	//输出 p 所指的元素 
		p = p->next;			//移动 p 指针 
	}	
} 

int main()
{
	printf("******************请按提示进行操作**********************\n");
	printf("***** 初始化链栈,                     enter    'a' *****\n");
	printf("***** 向栈里输入数据，                enter    'b' *****\n");
	printf("***** 判断链栈是否为空，              enter    'c' *****\n");
	printf("***** 清空链栈，                      enter    'd' *****\n");
	printf("***** 销毁链栈 ，                     enter    'e' *****\n");
	printf("***** 返回链栈元素的个数，            enter    'f' *****\n");
	printf("***** 返回栈顶元素,并不删除，         enter    'g' *****\n");
	printf("***** 在栈顶插入元素，                enter    'h' *****\n");
	printf("***** 删除栈顶元素，并用 e 返回其值， enter    'i' *****\n");
	printf("***** 输出链栈里的全部元素，           enter   'j' *****\n");
	printf("********************************************************\n");
	
	LinkStack S;	//定义栈的头 
	SElemType E;	//用来传递值
	int N;
	int back;	//接收函数返回值 
	char str; 	//从键盘接收字符
	do
	{
		printf("\n");
		printf("Please enter a char:    ");
		str=getche();	/*从键盘获取一个字符并显示，不按回车直接执行*/ 
		printf("\n");	/*接收上条语句的回车键，否则回车键也会被认为是字符*/
		switch(str)
		{
			case 'a'://初始化链栈
			{
				back = Init_Stack(&S);
				if(back)
					printf("已为您初始化完成一个空链栈。\n");
				else 
					printf("初始化失败！！\n");	
				break;
			}
			case 'b':// 向栈里输入数据
			{
				printf("请输入数据的个数：  ");
				scanf("%d",&N);
				Create_Stack(&S,N);
				break;
			}
			case 'c'://判断链栈是否为空
			{
				back = Empty_Stack(&S);
				if(back)
					printf("This is an empty stack. \n");
				else
					printf("This is not an empty stack.  \n");
				break;
			}
			case 'd'://清空链栈
			{
				back = Clear_Stack(&S);
				if(back)
					printf("链栈已被清空！！！\n");
				break;
			}
			case 'e'://销毁链栈
			{
				back=Destroy_Stack(&S);
				if(back)
					printf("链栈已被销毁！！！\n");
				break;
			}
			case 'f'://返回链栈元素的个数
			{
				back=Length_Stack(&S);
				printf("链栈的长度是 :     %d\n",back);
				break;
			}
			case 'g'://返回栈顶元素,并不删除
			{
				E=GetTop_Stack(&S);
				printf("栈顶元素为 :   %d\n",E);
				break;
			}
			case 'h'://在栈顶插入元素
			{
				printf("请输入要插入元素的值：    ");
				scanf("%d",&E);
				back=Push_Stack(&S,E);
				if(back)
				{
					printf("插入后栈内元素值变为：  ");
					Printf_Stack(&S);
					printf("\n");
				}
				else
					printf("插入元素失败！！！\n");
				break;
			}
			case 'i'://删除栈顶元素，并用 e 返回其值
			{
				back=Pop_Stack(&S,&E);
				if(back)
					printf("删除的栈顶元素是：   %d\n",E);
				else
					printf("删除失败！！！\n");
				break;
			}
			case 'j'://输出链栈里的全部元素
			{
				Printf_Stack(&S);
				break;
			} 
			default:printf("wrong!\n");
		}
	}while(str!='q');
	return 0;
}
