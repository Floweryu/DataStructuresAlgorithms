#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

typedef int Status;
 
//判断 t1 和 t2 两种符号的优先级 
char Precede(char t1, char t2)
{
	char f;
	switch(t2)
	{
		case '+':			//与 '-' 优先级相同，表示同一种情况 
			
		case '-':
		{
			if(t1 == '(' || t1 == '\n')	//比较 t1 和 t2 的优先级 
				f = '<';	// t1 优先级小于 t2 
			else
				f = '>';
			break;
		}
		
		case '*':			//与 '/' 优先级相同，表示同一种情况 
			
		case '/':
		{
			if(t1 == '*' || t1 == '/' || t1 == ')')	//比较 t1 和 t2 的优先级
				f = '>';	// t1 优先级大于 t2 
			else
				f = '<';
			break;
		} 
		
		case '(':
		{
			if(t1 == ')')	//如果 t1 是右括号，t2 是左括号 
				{
					printf("括号不匹配！！！\n");
					exit(OVERFLOW);
				}
			else
				f = '<';
			break;
		}
		
		case ')':				//比较 t1 和 t2 的优先级， t1 有多种情况 
		{
			switch(t1)
			{
				case '(':		//若 t1 是左括号 
				{
					f = '=';	//括号刚好匹配 ，优先级相等 
					break;
				} 
				
				case '\n':		//若 t1 是回车换行 
				{
					printf("缺乏左括号！！！\n");
					exit(OVERFLOW);
					break;
				}
				
				default:f = '>';	// t1 优先级大于 t2 
			}	// end switch
 		}
		
		case '\n':					//比较 t1 和 t2 的优先级， t1 有多种情况
		{
			switch(t1)
			{
				case '\n':			//若 t1 是换行 
				{ 
					f = '=';		// t1 优先级等于 t2
					break;
				}
				
				case '(':			//若 t1 是左括号 
				{
					break;
				}
				
				default: f = '>'; 	// t1 优先级大于 t2 
			}	// end switch
		}		
	}// end switch
	return f;
} 

//判断 c 是否为运算符号之一
Status In(char c)
{
	switch(c)
	{
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
		case ')':
		case '\n':	return TRUE;
					break; 
		default:	return FALSE;
	}
}

//做四则运算，返回运算结果
char Operate(int a, char theta, int b)
{
	char c;
	switch(theta)
	{
		case '+': c = a+b;
				break;
		case '-': c = a-b;
				break;
		case '*': c = a*b;
				break;
		case '/': c = a/b;	//没有考虑 b 为 0 情况，默认除数不为 0  
				break;
		default:	return FALSE;
	}	
	return c;	
} 
 

