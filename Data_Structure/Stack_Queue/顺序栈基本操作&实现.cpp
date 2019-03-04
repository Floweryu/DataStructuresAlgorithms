#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<conio.h>

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int SElemType;

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
 
//判断栈是否为空
//空栈返回1，否则返回0 
Status EmptyStack(SqStack &S)
{
	if(S.top == S.base)		//判空条件，栈顶指针是否指向栈底 
		return TRUE;
	else
		return FALSE;
} 

//返回栈元素的个数
Status LengthStack(SqStack &S)
{
	return S.top-S.base;	//栈顶指针减去栈底指针（可以看出栈底指针指向空，即0） 
}

//若栈不为空，返回栈顶元素，并返回OK，否则，返回FALSE
Status GetTopStack(SqStack &S,SElemType &e)
{
	if(S.top == S.base)	//判断栈是否为空 
		return ERROR;
	else
	{
		S.top--;		//指向栈顶元素 
		e = *(S.top);	//将值返回给e 
		S.top++;
		return OK;
	}
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
 
//向栈里输入数据
Status CreateStack(SqStack &S,int n)
{
	int m, i;
	for(i = 0; i < n; i++)
	{
		scanf("%d",&m);		//输入数据 
		PushStack(S, m);	//将数据插入到栈顶， 
	}
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

//遍历栈并输出
Status PrintfStack(SqStack &S)
{
	if(S.base == S.top)		//判断是否为空栈 
		return ERROR;
	while(S.top != S.base)	//当栈顶指针未指向栈底时 
	{
		S.top--;			//栈顶指针指向栈顶元素 
		printf("%d ",*S.top);
	}
	return OK;
 } 
 
//从栈底到栈顶输出元素，相当于逆序输出 
Status rePrintfStack(SqStack &S)
{
	SElemType *p = S.base;	//定义 p 指针指向栈底 
		
	while(S.top > p)		//当 p 指针未指到栈顶时 
	{
		printf("%d ",*p);	//输出元素值 
		p++;				//指针加一向上移动 
	}
	printf("\n");
}
int main()
{
	printf("****** 构建一个空栈，enter               'a'    ******\n");
	printf("****** 销毁栈，enter                     'b'    ******\n");
	printf("****** 返回栈的长度，enter               'c'    ******\n");
	printf("****** 判断栈是否为空，enter             'd'    ******\n");
	printf("****** 返回栈顶元素，enter               'e'    ******\n");
	printf("****** 在栈顶插入一个元素，enter         'f'    ******\n");
	printf("****** 删除栈顶元素，enter               'g'    ******\n");
	printf("****** 向栈里输入数据，enter             'h'    ******\n");
	printf("****** 输出栈里的数据，enter             'i'    ******\n");
	printf("****** 清空栈，enter                     'j'    ******\n");
	printf("****** 从栈底到栈顶输出元素， enter      'k'    ******\n"); 
	SqStack S;
	int back;	//用于空与非空的判断
	int k;	//用于接受返回值
	SElemType E,N; 
	char str;
	do
	{
		printf("\n");
		printf("Please enter a char:    ");
		str=getche();/*从键盘获取一个字符并显示，不按回车直接执行*/ 
		printf("\n");/*	getchar();	/*接收上条语句的回车键，否则回车键也会被认为是字符*/
		switch(str)
		{
			case 'a':{
						back=InitStack(S);
						if(back)
						printf("以为您构建好一个空栈\n");
						else
						printf("ERROR\n");
				break;
			}
			case 'b':{
						DestroyStack(S);
				break;
			}
			case 'c':{
						k=LengthStack(S);
						printf("栈的长度为：   %d\n",k);
				break;
			}
			case 'd':{
						back=EmptyStack(S);
						if(back)
							printf("这是一个空栈。\n");
						else
							printf("这不是一个空栈。\n");
				break;
			}
			case 'e':{
						back=GetTopStack(S,E);
						if(back)
							printf("栈顶元素是：   %d\n",E);
						else
							printf("这是一个空栈\n");
				break;
			}
			case 'f':{
						printf("请输入将要在栈顶插入的元素：   ");
						scanf("%d",&E);
						back=PushStack(S,E);
						if(back)
							printf("插入成功\n");
						else
							printf("插入失败\n");
				break;
			}
			case 'g':{
						back=PopStack(S,E);
						if(back)
						{
							printf("删除成功，删除元素为:    %d\n",E);
						}
						else
							printf("删除失败\n");
				break;
			}
			case 'h':{
						printf("请输入数据的个数：  ");
						scanf("%d",&N);
						CreateStack(S,N);
				break;
			}
			case 'i':{
						PrintfStack(S);
				break;
			}
			case 'j':{
						back = ClearStack(S);
						if(back)
							printf("清空栈成功！！\n");
				break;
			}
			case 'k':{
				rePrintfStack(S);
				break;
			}
			default:printf("wrong!\n");
		 } 

	}while(str!='q');
	return 0;
}
 
