#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define N 1000+10

char str[N];
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

//若链栈不为空，就返回栈顶元素,并不删除 
Status GetTop_Stack(LinkStack &S)
{
	if(S->next == NULL)			//判断链栈是否为空 
		return ERROR;	
	else
		return S->next->data;		//不为空，就返回第一个结点的元素 
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

unsigned char Prior[7][7] =
{
	{'>','>','<','<','<','>','>'},
	{'>','>','<','<','<','>','>'},
	{'>','>','>','>','<','>','>'},
	{'>','>','>','>','<','>','>'},
	{'<','<','<','<','<','=',' '},
	{'<','<','<','<','<',' ','>'},
	{'<','<','<','<','<',' ','='}
};

char OPSET[7] = {'+', '-', '*', '/', '(', ')', '#' };

Status precede(int a, char b)//判断优先级函数 
{
	int i = 0, j = 0;
	
	while(OPSET[i] != a)
	{
		i++;
	}

	while(OPSET[j] != b)
	{
		j++;
	}

	return Prior[i][j];
}

Status In(char c,char str[])//判断是否为运算符 
{
	int i = 0;

	while(c != str[i])
	{
		i++;
	}

	if(i < 7)
		return OK;

	return ERROR;
}

Status Opereta(int a,int b,int c)//运算函数 
{
	switch(b)
	{
		case '+':	return a+c;
		case '-':	return a-c;
		case '*':	return a*c;
		case '/':	return a/c;
	} 
}

Status Atoi(char *c)//把字符串转为数字 
{
	int data= 0, d = 0;
	int i = 0;
	
	while(c[i] != '\0')
	{
		data = data*10 + c[i]-'0';
		i++;
	}
	
	return data;
} 

int EvaluateExpression(char *MyExpression)//算法3.4 
{
	LinkStack OPTR;			//运算符栈，字符元素 
	LinkStack OPND;			//运算数栈，实数元素 
	char TempData[20];
	int Data, a, b;
	char *c, Dr[2];
	int theta, x;

	Init_Stack(OPTR);
	
	Push_Stack(OPTR, '#');
	
	Init_Stack(OPND);
	
	c = MyExpression;
	
	TempData[0] = '\0';
	
	while(*c != '#' || GetTop_Stack(OPTR) != '#')
	{
		if( ! In(*c, OPSET))//不是运算符则进栈 
		{
			Dr[0] = *c;
			Dr[1] = '\0';
			
			strcat(TempData, Dr);
			c++; 

			if(In(*c,OPSET))	//是运算符时 
			{
				Data = Atoi(TempData);
				Push_Stack(OPND, Data);
				
				TempData[0] = '\0';
			}
		}
		else
		{
			switch(precede(GetTop_Stack(OPTR), *c))
			{
				case '<':
					Push_Stack(OPTR, *c);
					c++;
					break;

				case '=':
					Pop_Stack(OPTR, x);
					c++;
					break;

				case '>':
					Pop_Stack(OPND, a);
					Pop_Stack(OPND, b);
					Pop_Stack(OPTR, theta);
					Push_Stack(OPND,Opereta(b, theta, a));
					break;
			}
		}
	}
	
	return GetTop_Stack(OPND);
}

int main()
{
	while(scanf("%s", str) != EOF)
	{
		printf("%d\n",EvaluateExpression(str));
	}
	return 0;
}
