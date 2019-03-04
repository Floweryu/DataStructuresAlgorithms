#include "circle_queue.h"

int main()
{
	SqQueue q1, q2, temp, q3;					// q1 ���ÿ�����ݣ�q2 �����q1�м������һ�����ݣ�
												//tempΪq1��q2�������м����飬q3�������������Ҫ��������� 
	int n, num, e, i, j;						//n ��Ҫ���������ǵ�������num ���ÿ��Ҫ��������ݣ�e���պ�������ֵ��i,jΪ������ 
	
	InitQueue(q1);								//��ʼ������q1,q2,q3,temp; 
	InitQueue(q2);
	InitQueue(temp);
	InitQueue(q3);
	
	while(scanf("%d", &n) != EOF)				//������������ 
	{
		for(i = 0; i <= n; i++)					//���ڵ�һ��������������������ʵ��������� 1 ~ n �С� 
		{
			if(i == 0)							//�� 0 �У� 
			{	
				InsertQueue(q1, 0);				//�� q1 �д������ʼ��Ϊ 0 1 0 
				InsertQueue(q1, 1);
				InsertQueue(q1, 0);
			
				num = 1;						//�� 0 ��Ӧ�����������ʵ��û����� 
			}	//end if
			
			else
			{
				InsertQueue(q2, 0);				//q1���м�����ɺ����� q2 �в��� 0 
				while(LengthQueue(q1) != 1)		//�� q1 ���г��Ȳ�Ϊ 1 ʱ 
				{	
					DeleteQueue(q1, num);		//ɾ��ͷ����ֵ�����ص� num �� ����ֵΪ 0 

					GetHeadQueue(q1, e);		//�õ���һ��ֵ�����ص� e �� 

					num = num + e;				//��������������ֵ��Ӹ��� num����ΪҪ��� 

					InsertQueue(q2, num);		//���õ�����һ�е�ֵ�浽 q2 �����У���Ϊ q1 ���л�Ҫ���㡣�˴������Ż��� 
					
					InsertQueue(q3, num);		//���õ���Ҫ�����ֵ�浽q3�б��� 
				}	// end while 
				InsertQueue(q2, 0);				//�� q2 ���е�β������0 
					
				temp = q1;						//��q2����������q1���н��� 
				q1 = q2;
				q2 = temp;
				
				ClearQueue(q2);					//��� q2 ���У��Ա��´�ʹ�� 
			} // end else
			
		}	// end for
		for(i = 0; i < n; i++)					//���n��������� 
		{		
			for(j = 0; j <= n - i; j++)			//��ÿ��ǰ��� n - i ���ո� 
				printf("  ");
			for(j = 0; j < i + 2; j++)			//ÿ����������ݸ����� i + 2 ������Ϊ i �� 0 ��ʼ���� 
			{
				DeleteQueue(q3, e);				//�����ɾ����ͷԪ�� 
				printf("%d   ", e);
			}	
			printf("\n");						//����û�к��� 
		}
		
		ClearQueue(q1);							//��� q1 , q3 ���� 
		ClearQueue(q3);
	}	//end while
}
