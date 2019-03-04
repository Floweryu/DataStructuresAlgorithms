#include<stdio.h>
#include<math.h> 

void PrintfArray(int *array, int n)
{
	int i, j;												//���� i , j ��Ϊ������±�  
	int k, tail = 0;													// k Ϊ�洢��һά�����������±� 
	for(i = 0; i < n; i++)									//��ѭ�� 
	{
		for(j = 0; j < n; j++)								//��ѭ�� 
		{
			k = 2 * i + j;
			if(abs(i - j) <= 1)
				printf("%2d ", array[k]);						//��� 
			else
				printf("%2d ", tail);
		}
		printf("\n");
	}
}

void StoreArray(int n)
{
	int len, i;
	len = 3 * n - 2;					//ȷ��һά����ĳ���
	int array[len];						//����һά���� 
	
	printf("������ %d �����ݣ�\n", len);	
	for(i = 0; i < len; i++)
	{
		scanf("%d", &array[i]);			//��һά�������������� 
	}
	
	PrintfArray(array, n);
} 

int main()
{
	int n;								//n Ϊ����Ľ���
	
	printf("���������Ľ�����      ");
	scanf("%d", &n);					
	StoreArray(n);

}
