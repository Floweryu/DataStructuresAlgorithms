/*
	Name: 
	Copyright: 
	Author: 
	Date: 01/11/18 18:48
	Description: 	�˳���ֻʹ����һ�����н��в����� 
*/

#include "circle_queue.h"

int main()
{
	SqQueue q1;				 					//q1 ���д������������ݣ����е����� 
	int n, num, i, j, e1, e2;					//n ��ʾ�����������num ��ʾҪ����q1�����е�������ǵ���ֵ 
						
	InitQueue(q1);								//��ʼ��q1���� 
	while(scanf("%d", &n) != EOF)				//������������� 
	{	
		int len, len0 = 0, count = 3;			//len ��ʾ���г��ȣ�len0 ��ʾÿһ�еĳ��ȣ�
												//count ��ʾ�ӳ�ʼֵ 3 λ�ÿ�ʼ���������� 
		for(i = 0; i <= n; i++)		
		{
			if(i == 0)							//�����ǳ�ʼ��ǰ������ݣ�������� 
			{	
				InsertQueue(q1, 0);				
				InsertQueue(q1, 1);
				InsertQueue(q1, 0);
			
				num = 1;						
			}	//end if
			
			else
			{
				len = LengthQueue(q1);			//������еĳ��� 
				InsertQueue(q1, 0);				//����һ�н�������һ�п�ʼǰ���� 0  
				for(j = len0; j < len-1; j++)	//�Ӹ��еĵ�һ��λ�ÿ�ʼѭ������ 
				{	
					GetQueue(q1, j, e1);		//�õ���������λ�õ�ֵ 
					GetQueue(q1, j+1, e2);
					num = e1 + e2;			 	//��� 
					
					InsertQueue(q1, num);		//���浽q1���к��� 
					
				}	// end while 
				len0 = len;						//len0 ������һ�ζ��еĳ��� 
				InsertQueue(q1, 0);				//ÿ�н�������ĩβ���� 0  
					
			} // end else
			
		}	// end for
	
		for(i = 1; i <= n; i++)					//��� n �� 
		{		
			for(j = 1; j <= n - i + 1; j++)		//ÿ������Ŀո�����ϵ 
				printf("  ");
			for(j = 1; j <= i + 3; j++)			//q1 �����ж�Ӧ��ÿ�еĸ��� 
			{
				GetQueue(q1, count, num);		//�õ�ָ��λ�õ�ֵ 
				if(num)							//������� 0  
				printf("%d   ", num);			//��������� 
				
				count++;						//λ�ú��� 
			}		
			printf("\n");					
		}
		
		ClearQueue(q1);							//��ն���q1 

	}	//end while
	
}
