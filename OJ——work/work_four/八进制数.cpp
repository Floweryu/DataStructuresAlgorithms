#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

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

//判断链栈是否为空 
Status Empty_Stack(LinkStack &S)
{
	if(S->next == NULL)	//如果头结点的后继指向NULL，即为空 返回真 
		return OK;
	else
		return FALSE; 	//否则，不为空 
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
//十进制转换八进制 
void Dec_OctConversion(LinkStack &S, unsigned n)	
{
	Init_Stack(S); 				//初始化一个空的链栈 
	SElemType e;				//定义一个接受返回值的变量
	 
	while(n)					//把余数堆栈 
	{
		Push_Stack(S, n%8);		//把除以 8 的余数进栈 
		n = n / 8;				// n 除以 8 取整 
	}
	
	while( ! Empty_Stack(S))	//余数出栈 
	{	
		Pop_Stack(S, e);		//在出栈的同时删除元素 
		
		printf("%d", e);		//输出出栈的元素 
	}
}

int main()
{
	unsigned n;
	LinkStack s;
	while(scanf("%d", &n) != EOF)
	{
		Dec_OctConversion(s, n);
		printf("\n");
	}
 } 
