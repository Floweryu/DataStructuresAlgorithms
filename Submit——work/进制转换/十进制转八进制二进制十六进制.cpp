#include "single_stack.h"

//ʮ����ת���˽��� 
void Dec_OctConversion(LinkStack &S, unsigned n)	
{
	Init_Stack(S); 				//��ʼ��һ���յ���ջ 
	SElemType e;				//����һ�����ܷ���ֵ�ı���
	 
	while(n)					//��������ջ 
	{
		Push_Stack(S, n%8);		//�ѳ��� 8 ��������ջ 
		n = n / 8;				// n ���� 8 ȡ�� 
	}
	
	while( ! Empty_Stack(S))	//������ջ 
	{	
		Pop_Stack(S, e);		//�ڳ�ջ��ͬʱɾ��Ԫ�� 
		
		printf("%d", e);		//�����ջ��Ԫ�� 
	}
}

//ʮ����ת�������� 
void Dec_BinConversion(LinkStack &S, unsigned n)
{
	Init_Stack(S); 				//��ʼ��һ���յ���ջ 
	SElemType e;				//����һ�����ܷ���ֵ�ı��� 
	
	while(n)					//��������ջ 
	{
		Push_Stack(S, n%2);		//�ѳ��� 2 ��������ջ 
		n = n / 2;				// n ���� 2 ȡ�� 
	}
	
	while(!Empty_Stack(S))		//������ջ 
	{	
		Pop_Stack(S, e);		//�ڳ�ջ��ͬʱɾ��Ԫ�� 
		printf("%d", e);		//�����ջ��Ԫ�� 
	}
}

//ʮ����ת��ʮ������
void Dec_HexConversion(LinkStack &S, unsigned n)
{
	Init_Stack(S); 				//��ʼ��һ���յ���ջ 
	SElemType e;				//����һ�����ܷ���ֵ�ı���
	
	while(n)					//������ջ 
	{
		Push_Stack(S, n%16);	// n ���� 16 ��ȡ���ջ 
		n = n / 16;				// n ���� 16 ȡ����Ȼ��ѭ�� 
	}
	
	while( ! Empty_Stack(S))	//������ջ 
	{
		Pop_Stack(S, e);		//�ȳ�ջһ��Ԫ�� 
			
		if(e >= 0 && e <=9)		//�ж��Ƿ��� 0 �� 9 ֮�� 
		{
			printf("%d", e);	//����������� 0 ~ 9 
		}
		else					//���� 
		{
			printf("%c", e+55);	//����ַ����� A ~ F 
		}
		
	}
}

int main()
{
	printf("**********************************************\n");
	printf("*****ʮ����ת���˽��ƣ�   enter   'a'    *****\n");
	printf("*****ʮ����ת�������ƣ�   enter   'b'    *****\n");
	printf("*****ʮ����ת��ʮ�����ƣ� enter   'c'    *****\n");
	printf("**********************************************\n");
	LinkStack s; 			//����һ��ջ 
	unsigned n;				//����һ���Ǹ������α��� 
	char str;				//����һ���� switch ѡ����ַ�
	
	do
	{
		printf("\n");
		printf("Please enter a char:    ");
		str=getche();       //�Ӽ��̻�ȡһ���ַ�����ʾ�������س�ֱ��ִ��
		printf("\n");
		 
		switch(str)
		{
			case 'a':		//ʮ����ת���˽���
			{
				printf("Please enter a num:      ");
				scanf("%d", &n);
				
				Dec_OctConversion(s, n);	//���ú��� 
				
				break;
			} 
			case 'b':		//ʮ����ת��������
			{
				printf("Please enter a num:      ");
				scanf("%d", &n);
				
				Dec_BinConversion(s, n);	//���ú��� 
				
				break;
			} 
			case 'c':		//ʮ����ת��ʮ������
			{
				printf("Please enter a num:      ");
				scanf("%d", &n);
				
				Dec_HexConversion(s, n);	//���ú��� 
				
				break;
			} 
			default:printf("wrong!\n");
		}
	}while(str != 'q');
	return 0;
}
