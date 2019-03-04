#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int SElemType;			//定义栈中的数据类型 

typedef struct SqStack
{
	SElemType data;				//数据域 
	struct SqStack *next;		//指针域 
}SqStack,*LinkStack;

//初始化链栈
/* 建立一个空栈，创建链栈的头结点，将其NULL置空	*/
Status Init_Stack(LinkStack &S)
{
	S = (LinkStack)malloc(sizeof(SqStack));		//申请头结点空间
	
	if(S == NULL)								//判断新空间是否分配成功 
		exit(OVERFLOW);
		
	S->next = NULL;								//头结点后继指向空 
	
	return OK;
} 

//清空链栈
Status Clear_Stack(LinkStack &S)
{

	LinkStack p,q;				//定义 p q 指针 
	
	p = S->next;				// p 指向第一个节点 
	while(p != NULL)			//当 p 不指向空的时候循环 
	{
		q = p->next;			// q 指向 p 的下一个节点 
		free(p);				//释放 p 节点 
		p = q;					// p 重新指向 q 节点 
	}
	
	S->next = NULL;				//节点释放完后，是栈头结点指向NULL，回到初始化状态 
	
	return OK;
} 

//在栈顶插入元素
Status Push_Stack(LinkStack &S,SElemType e)
{
	LinkStack p;			//定义一个指针，用来指向要插入元素 
	
	p = (LinkStack) malloc (sizeof(SqStack));	//为指针 p 申请存储空间
	if(p ==  NULL)			//判断空间是否申请成功 
		exit(OVERFLOW); 
		
	p->data = e;			// 把要插入的值赋给p的数据域 
	p->next = S->next;		// p 的后继指向头结点的后继 
	S->next = p;			// p 的前驱指向头结点的后继
	
	return OK;				//插入成功，返回真 
} 

//删除栈顶元素，并用 e 返回其值 
Status  Pop_Stack(LinkStack &S, SElemType &e)
{
	if(S->next == NULL)		//判断链栈是否为空栈 
		return ERROR; 
	
	LinkStack p;
	
	p = S->next;			// p 指向栈顶元素 
	S->next = p->next;		//头结点 S 的后继指向栈顶元素的下一个元素
	 
	e = p->data;			//把栈顶存储的值赋给 e 返回
	 
	free(p);				//释放栈顶节点 
	
	return OK;
}

int main()
{
	LinkStack S;
	Init_Stack(S);
	char str[1000];
	SElemType E;
	int back, j, len;
	
	while(scanf("%s",str) != EOF)
	{
		int i = 1;
		len = strlen(str);

		for (j = 0; j < len; j++)
		{
			if(str[j] == 'P')
			{
				Push_Stack(S, i);
				i++;
			}
			else if(str[j] == 'Q')
			{
				back = Pop_Stack(S, E);
				if(back)
					printf("%d ",E);
				else
				{
					printf("error");
					break;
				}
			}
		}
		printf("\n");
		Clear_Stack(S);
	}
}

