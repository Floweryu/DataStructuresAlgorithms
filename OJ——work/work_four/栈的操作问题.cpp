#include<stdio.h>
#include<string.h>
int main()
{
	int n;
	int a[1000];
	int i, j, t, k, flag1, flag2;
	while(scanf("%d",&n) != EOF)
	{
	if(n)
	{
		for(i = 0; i < n; i++)		//�������ݴ浽���� a �� 
			scanf("%d",&a[i]);
		
		for(j = 0; j < a[0]; j++)	//�Ե�һ�������д��� 
			printf("P");			
		printf("Q");				//��һ�������ȳ�ջ 
		
		for(i = 0, j = i+1; i < n, j < n; i++, j++)		//��������������֮�����ж� 
		{	
			for(k = 0; k < j; k++)		//Ѱ�� a[j]-1 �Ƿ���ǰ����� 
			{
				if((a[k]+1)== a[j])
				{
					flag1 = 1;			//���� 
					break;
				}
				else
					flag1 = 0; 			//û�г��� 
			}
			
					
			t = a[j] - a[i];
			
			if(t >= 1)					//���������һ 
			{	
				if(flag1 == 1)			//���� a[j]-1 �Ѿ����ֹ� 
				{
					printf("P");		//ֻ��Ҫ��ջһ�� 
					printf("Q");
				}
				else					//���� a[j]-1 û�г��ֹ�
				{
					for(k = 0; k < t; k++)		//��ջ��ε� a[j] 
						printf("P");
					printf("Q");
				}
			}
				
			
			else if(t == -1)				//������������ݼ� 
					printf("Q");			//ֱ�ӳ�ջ 
					
			else if(t < -1)					//��� a[j] ��ǰһ��������� -1 
			{
				int count = 0;
				for(k = 0; k < j; k++)		//�жϱ� a[j] ������Ƿ��Ѿ�ȫ������ 
				{
					if(a[k] > a[j])
						count++;
				}
				if(count == n - a[j])
					flag2 = 1;				//ȫ������ 
				else
					flag2 = 0;				//ûȫ���� 
					
				if(flag2 == 1)				//���ȫ�����֣��Ͳ��������� a[j] ���� 
					printf("Q");
				else						//���û��ȫ�����֣������� a[j] ���� ��a[j] ������ջ 
				{	
					printf(" error");
					break;
				}
			}
		}
	}
		memset(a,0,sizeof(a));
		printf("\n");
	}
} 
