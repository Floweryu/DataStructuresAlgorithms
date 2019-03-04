#include "intsingle_stack.h"
#include "intpriority.h"

SElemType EvaluateExpression()
{
	LinkStack OPTR, OPND;			//设 OPTR 和 OPND 分别为运算符栈和运算数栈
	SElemType a, b, d, x;			// a 和 b 存储运算数，d 用来把输入的字符数变成整形数，x 存储栈顶元素 
	char c;
	
	Init_Stack(OPTR);				//初始化 OPRT 
	Init_Stack(OPND);				//初始化 OPND
	
	Push_Stack(OPTR, '\n');			//把 \n 压入运算符栈的栈底 
	
	c = getchar();	 				//从键盘读入一个字符
	
	GetTop_Stack(OPTR, x);			//将运算符栈的栈顶元素赋给 x

	while(c != '\n' || x != '\n')			// c 和 x 都不是换行符 
	{
		if( In(c) )			// c 是 7 种运算符之一 
		{		
			switch(Precede(x, c))			//判断 x 和 c 的优先级
			{
				case '<':					// c 的优先级高，入栈 c 
				{
					Push_Stack(OPTR, c);
					c = getchar();			//从键盘读取下一个字符
					break; 
				} 
				
				case '=':					//优先级相等
				{
					Pop_Stack(OPTR, x);	
					c = getchar();
					break;
				}
				
				case '>':
				{
					Pop_Stack(OPTR, x);		//栈顶元素优先级高，弹出运算符栈的栈顶元素给 x 
					Pop_Stack(OPND, b);		//依次弹出运算数栈的元素给 b , a 
					Pop_Stack(OPND, a);
					Push_Stack(OPND, Operate(a, x, b));		//将运算结果 a x b 入栈 
					break;
				} 
			} 	//end switch
		}	// end if 
		
		else if(c >= '0' && c <= '9')		// c 是操作数
		{
			d = 0;
			
			while(c >= '0' && c <= '9')
			{
				d = d *10 + c - '0';
				c = getchar();
			}
			
			Push_Stack(OPND, d);
		} 
		
		else		// c 是非法字符
		{
			printf("Invalid character!!!\n");
			exit(OVERFLOW);
		}
		
		GetTop_Stack(OPTR, x);				//将运算符栈的栈顶元素赋给 x 
	} 	//end  while
	
	Pop_Stack(OPND, x);						//弹出运算数栈的栈顶元素给 x

	if( ! Empty_Stack(OPND))				//运算数栈不为空（只剩下 '\n'） 
	{
		printf("Incorrect expression!!!\n");
		exit(OVERFLOW);
	} 
	 
	return x;
} 

int main()
{
	printf("请输入正确的表达式，负数要用（0-正数）表示：\n");
	printf("%d\n",EvaluateExpression());
}
