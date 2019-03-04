#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

typedef char SElemType;
typedef int Status;
 
//�ж� t1 �� t2 ���ַ��ŵ����ȼ� 
char Precede(SElemType t1, SElemType t2)
{
	char f;
	switch(t2)
	{
		case '+':			//�� '-' ���ȼ���ͬ����ʾͬһ����� 
			
		case '-':
		{
			if(t1 == '(' || t1 == '\n')	//�Ƚ� t1 �� t2 �����ȼ� 
				f = '<';	// t1 ���ȼ�С�� t2 
			break;
		}
		
		case '*':			//�� '/' ���ȼ���ͬ����ʾͬһ����� 
			
		case '/':
		{
			if(t1 == '*' || t1 == '/' || t1 == ')')	//�Ƚ� t1 �� t2 �����ȼ�
				f = '>';	// t1 ���ȼ����� t2 
			break;
		} 
		
		case '(':
		{
			if(t1 == ')')	//��� t1 �������ţ�t2 �������� 
				{
					printf("���Ų�ƥ�䣡����\n");
					exit(OVERFLOW);
				}
			break;
		}
		
		case ')':				//�Ƚ� t1 �� t2 �����ȼ��� t1 �ж������ 
		{
			switch(t1)
			{
				case '(':		//�� t1 �������� 
				{
					f = '=';	//���Ÿպ�ƥ�� �����ȼ���� 
					break;
				} 
				
				case '\n':		//�� t1 �ǻس����� 
				{
					printf("ȱ�������ţ�����\n");
					exit(OVERFLOW);
					break;
				}
				
				default:f = '>';	// t1 ���ȼ����� t2 
			}	// end switch
 		}
		
		case '\n':					//�Ƚ� t1 �� t2 �����ȼ��� t1 �ж������
		{
			switch(t1)
			{
				case '\n':			//�� t1 �ǻ��� 
				{ 
					f = '=';		// t1 ���ȼ����� t2
					break;
				}
				
				case '(':			//�� t1 �������� 
				{
					printf("ȱ�������ţ�����\n");
					break;
				}
				
				default: f = '>'; 	// t1 ���ȼ����� t2 
			}	// end switch
		}		
	}// end switch
	return f;
} 

//�ж� c �Ƿ�Ϊ�������֮һ
Status In(SElemType c)
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
		default:	return FALSE;
	}
}

//���������㣬����������
SElemType Operate(SElemType a, SElemType theta, SElemType b)
{
	switch(theta)
	{
		case '+':	return a + b;
		case '-':	return a - b;
		case '*':	return a * b;
		case '/':	return a / b;	//û�п��� b Ϊ 0 �����Ĭ�ϳ�����Ϊ 0  
		default:	return FALSE;
	}		
} 
 

