#include<stdio.h>


void PrintfArray(int *array, int n)
{
	int i, j;								//���� i , j ��Ϊ������±�  
	int k;									// k Ϊ�洢��һά�����������±� 
	for(i = 0; i < n; i++)					//��ѭ�� 
	{
		for(j = 0; j < n; j++)				//��ѭ�� 
		{
			if(i >= j)						//������������������ 
			{
				k = i*(i + 1) / 2 + j;		//������������������Ӧ��һά�����е��±� 
			}
			else
			{
				k = j*(j + 1) / 2 + i; 		//������������������Ӧ��һά�����е��±� 
			}
			printf("%2d ", array[k]);		//��� 
		}
		printf("\n");
	}
}

void StoreArray(int n)
{
	int len, i;
	len = n * (n + 1) / 2;					//ȷ��һά����ĳ��� 
	int array[len];							//����һά���� 
				
	printf("������ %d �����ݣ�\n", len);
	for(i = 0; i < len; i++)
	{	
		scanf("%d", &array[i]);				//��һά�������������� 
	}
	
	PrintfArray(array, n);
} 

int main()
{	
	int n;									//n Ϊ����Ľ���
	printf("���������Ľ�����      ");
	scanf("%d", &n);
	StoreArray(n);

}
