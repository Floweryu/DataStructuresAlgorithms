#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define STACK_INIT_SIZE 200
#define STACK_INCREMENT 10

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef char SElemType;

typedef struct SqStack
{
	SElemType *base;	//在栈构造之前和之后，base的值为NULL 
	SElemType *top;		//栈顶指针(经过测试，此栈顶指针指向栈顶元素的上面，而不是栈顶） 
	int stacksize;		//当前已分配的空间，以实际元素为准 
 } SqStack;

//构造一个空栈 
Status InitStack(SqStack &S)
{
	S.base = (SElemType*) malloc (STACK_INIT_SIZE*sizeof(SElemType));	//分配空间 
	if(!S.base)							//判断申请空间是否成功 
		exit(OVERFLOW);	
			
	S.top = S.base;						//栈顶指针指向栈底 
	S.stacksize = STACK_INIT_SIZE;		// 存储空间为初始分配量
	 
	return OK;
}

//清空栈
Status ClearStack(SqStack &S)
{
	S.top = S.base;		//栈顶指针指向栈底即为空 
	return OK;
} 

//销毁栈
void DestroyStack(SqStack &S)
{
	free(S.base);			//释放栈空间 
	S.top = S.base = NULL;	//栈顶，栈底指针均为空 
	S.stacksize = 0;		//当前分配存储空间为0 
 } 
 
 //插入元素e到栈S的栈顶
Status PushStack(SqStack &S,SElemType e)
{
	if(S.top-S.base == S.stacksize)		//如果此时存储空间已经满了 
	{
		S.base = (SElemType*)realloc(S.base,(S.stacksize+STACK_INCREMENT)&sizeof(SElemType));//追加存储空间
		if(!S.base)						//追加存储空间失败
			return(OVERFLOW);
		S.top = S.base + S.stacksize;	//栈顶指针指向新加后的栈顶 
		S.stacksize += STACK_INCREMENT; //栈存储空间改变 
	}
	
	*S.top = e;							//将e入栈，成为新的栈顶元素，栈顶的指针上移一个存储单元 
	S.top++; 							//栈顶指针指向栈顶元素的上一个 
	return OK;
 } 
 
 //删除S的栈顶元素，并用e返回其值
Status PopStack(SqStack &S,SElemType &e)
{
	if(S.top == S.base)		//判断是否为空栈 
		return ERROR;
		
	S.top--;				//先将指针指向栈顶元素 
	e = *S.top;				//先将栈顶元素赋给e，再将栈顶指针移到下一个单元 
	return OK; 
} 

Status rePrintfStack(SqStack &S)
{
	SElemType *p = S.base;
	
	while(S.top > p)
	{
		printf("%c",*p);
		p++;
	}
}


void LineEdit()
{
	char ch;
	SqStack s;
	InitStack(s);

	ch = getchar();
	
	while(ch != EOF)
	{
		while(ch != EOF && ch != '\n')
		{
			switch(ch)
			{
				case '#':
					PopStack(s, ch);	break;
					
				case '@':
					ClearStack(s);		break;
					
				default:
					PushStack(s, ch);	break;
			}
			ch = getchar();
		}
		
		rePrintfStack(s);
		
		ClearStack(s);
		printf("\n");
		
		if(ch != EOF)
		{
			ch = getchar();
		}
	}
	DestroyStack(s);
 } 
 
int main()
{
	LineEdit();
}
