#include "single_stack.h"

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

//十进制转换二进制 
void Dec_BinConversion(LinkStack &S, unsigned n)
{
	Init_Stack(S); 				//初始化一个空的链栈 
	SElemType e;				//定义一个接受返回值的变量 
	
	while(n)					//把余数堆栈 
	{
		Push_Stack(S, n%2);		//把除以 2 的余数进栈 
		n = n / 2;				// n 除以 2 取整 
	}
	
	while(!Empty_Stack(S))		//余数出栈 
	{	
		Pop_Stack(S, e);		//在出栈的同时删除元素 
		printf("%d", e);		//输出出栈的元素 
	}
}

//十进制转换十六进制
void Dec_HexConversion(LinkStack &S, unsigned n)
{
	Init_Stack(S); 				//初始化一个空的链栈 
	SElemType e;				//定义一个接受返回值的变量
	
	while(n)					//余数堆栈 
	{
		Push_Stack(S, n%16);	// n 除以 16 后取余进栈 
		n = n / 16;				// n 除以 16 取整，然后循环 
	}
	
	while( ! Empty_Stack(S))	//余数出栈 
	{
		Pop_Stack(S, e);		//先出栈一个元素 
			
		if(e >= 0 && e <=9)		//判断是否在 0 到 9 之间 
		{
			printf("%d", e);	//是则输出整形 0 ~ 9 
		}
		else					//否则 
		{
			printf("%c", e+55);	//输出字符变量 A ~ F 
		}
		
	}
}

int main()
{
	printf("**********************************************\n");
	printf("*****十进制转换八进制，   enter   'a'    *****\n");
	printf("*****十进制转换二进制，   enter   'b'    *****\n");
	printf("*****十进制转换十六进制， enter   'c'    *****\n");
	printf("**********************************************\n");
	LinkStack s; 			//定义一个栈 
	unsigned n;				//定义一个非负的整形变量 
	char str;				//定义一个供 switch 选择的字符
	
	do
	{
		printf("\n");
		printf("Please enter a char:    ");
		str=getche();       //从键盘获取一个字符并显示，不按回车直接执行
		printf("\n");
		 
		switch(str)
		{
			case 'a':		//十进制转换八进制
			{
				printf("Please enter a num:      ");
				scanf("%d", &n);
				
				Dec_OctConversion(s, n);	//调用函数 
				
				break;
			} 
			case 'b':		//十进制转换二进制
			{
				printf("Please enter a num:      ");
				scanf("%d", &n);
				
				Dec_BinConversion(s, n);	//调用函数 
				
				break;
			} 
			case 'c':		//十进制转换十六进制
			{
				printf("Please enter a num:      ");
				scanf("%d", &n);
				
				Dec_HexConversion(s, n);	//调用函数 
				
				break;
			} 
			default:printf("wrong!\n");
		}
	}while(str != 'q');
	return 0;
}
