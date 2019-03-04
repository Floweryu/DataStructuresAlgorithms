#include "single_stack.h"
#include "priority.h"

SElemType EvaluateExpression()
{
	LinkStack OPTR, OPND;			//�� OPTR �� OPND �ֱ�Ϊ�����ջ��������ջ
	SElemType a, b, c, x;			// a �� b �洢��������d ������������ַ��������������x �洢ջ��Ԫ�� 
	
	Init_Stack(OPTR);				//��ʼ�� OPRT 
	Init_Stack(OPND);				//��ʼ�� OPND
	
	Push_Stack(OPTR, '\n');			//�� \n ѹ�������ջ��ջ�� 
	
	c = getchar();	 				//�Ӽ��̶���һ���ַ�
	
	GetTop_Stack(OPTR, x);			//�������ջ��ջ��Ԫ�ظ��� x

	while(c != '\n' || x != '\n')			// c �� x �����ǻ��з� 
	{
		if( In(c) )			// c �� 7 �������֮һ 
		{		
			switch(Precede(x, c))			//�ж� x �� c �����ȼ�
			{
				case '<':					// c �����ȼ��ߣ���ջ c 
				{
					Push_Stack(OPTR, c);
					c = getchar();			//�Ӽ��̶�ȡ��һ���ַ�
					break; 
				} 
				
				case '=':					//���ȼ����
				{
					Pop_Stack(OPTR, x);	
					c = getchar();
					break;
				}
				
				case '>':
				{
					Pop_Stack(OPTR, x);		//ջ��Ԫ�����ȼ��ߣ����������ջ��ջ��Ԫ�ظ� x 
					Pop_Stack(OPND, b);		//���ε���������ջ��Ԫ�ظ� b , a 
					Pop_Stack(OPND, a);
					Push_Stack(OPND, Operate(a, x, b));		//�������� a x b ��ջ 
					break;
				} 
			} 	//end switch
		}	// end if 
		
		else if(c >= '0' && c <= '9')		// c �ǲ�����
		{
			Push_Stack(OPND, c-48);			//�� d ѹ��������ջ 
			c = getchar();
		} 
		
		else		// c �ǷǷ��ַ�
		{
			printf("Invalid character!!!\n");
			exit(OVERFLOW);
		}
		
		GetTop_Stack(OPTR, x);				//�������ջ��ջ��Ԫ�ظ��� x 
	} 	//end  while
	
	Pop_Stack(OPND, x);						//����������ջ��ջ��Ԫ�ظ� x

	if( ! Empty_Stack(OPND))				//������ջ��Ϊ�գ�ֻʣ�� '\n'�� 
	{
		printf("Incorrect expression!!!\n");
		exit(OVERFLOW);
	} 
	 
	return x;
} 

int main()
{
	printf("��������ȷ�ı��ʽ������ֵ��0~9֮�䣺\n");
	printf("%d\n",EvaluateExpression());
}
