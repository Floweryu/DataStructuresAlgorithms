#include<stdio.h>
#include<math.h>
#include<conio.h>

void Diagonal(int n)
{
	int len, i, j, k, tail = 0;					//���� i , j ��Ϊ������±� , k Ϊ�洢��һά�����������±� 
	len = 3 * n - 2;							//ȷ��һά����ĳ���
	int array[len];								//����һά���� 
	
	printf("������ %d �����ݣ�\n", len);	
	for(i = 0; i < len; i++)
	{
		scanf("%d", &array[i]);					//��һά�������������� 
	}
					
	for(i = 0; i < n; i++)						//��ѭ�� 
	{
		for(j = 0; j < n; j++)					//��ѭ�� 
		{
			k = 2 * i + j;
			if(abs(i - j) <= 1)
				printf("%2d ", array[k]);		//��� 
			else
				printf("%2d ", tail);
		}
		printf("\n");
	}
}

void SymmetricOn(int n)
{
	int len, i, j, k;										//���� i , j ��Ϊ������±� , k Ϊ�洢��һά�����������±� 
	len = n * (n + 1) / 2;									//ȷ��һά����ĳ���
	int array[len];											//����һά���� 
	
	printf("������ %d �����ݣ�\n", len);	
	for(i = 0; i < len; i++)
	{
		scanf("%d", &array[i]);								//��һά�������������� 
	}

	for(i = 0; i < n; i++)									//��ѭ�� 
	{
		for(j = 0; j < n; j++)								//��ѭ�� 
		{
			if(i <= j)										//������������������Ӧ��һά�����е��±� 
			{
				k = i * (2 * n - i + 1) / 2 + j - i;
			}
		
			else
			{
				k = j * (2 * n - j + 1) / 2 + i - j;		//������������������Ӧ��һά�����е��±� 
			}
			printf("%2d ", array[k]);						//��� 
		}
		printf("\n");
	}
}

void SymmetricIn(int n)
{
	int len, i, j, k;						//���� i , j ��Ϊ������±� , k Ϊ�洢��һά�����������±� 
	len = n * (n + 1) / 2;					//ȷ��һά����ĳ���
	int array[len];							//����һά���� 
	
	printf("������ %d �����ݣ�\n", len);	
	for(i = 0; i < len; i++)
	{
		scanf("%d", &array[i]);				//��һά�������������� 
	}

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

void InArray(int n)
{
	int i, j, len;							//���� i , j ��Ϊ������±�  
	int k, tail = 0;						// k Ϊ�洢��һά�����������±� 
	len = n * (n + 1) / 2;					//ȷ��һά����ĳ��� 
	int array[len];							//����һά���� 
				
	printf("������ %d �����ݣ�\n", len);
	for(i = 0; i < len; i++)
	{	
		scanf("%d", &array[i]);				//��һά�������������� 
	}
	
	for(i = 0; i < n; i++)					//��ѭ�� 
	{
		for(j = 0; j < n; j++)				//��ѭ�� 
		{
			if(i >= j)						//������������������ 
			{
				k = i*(i + 1) / 2 + j;		//������������������Ӧ��һά�����е��±� 
				printf("%2d ", array[k]);	//��� 
			}
			else
			{
				printf("%2d ", tail);
			}
		
		}
		printf("\n");
	}
}

void OnArray(int n)
{
	int i, j, len;							//���� i , j ��Ϊ������±�  
	int k, tail = 0;						// k Ϊ�洢��һά�����������±� 
	len = n * (n + 1) / 2;					//ȷ��һά����ĳ��� 
	int array[len];							//����һά���� 
				
	printf("������ %d �����ݣ�\n", len);
	for(i = 0; i < len; i++)
	{	
		scanf("%d", &array[i]);				//��һά�������������� 
	}
	
	for(i = 0; i < n; i++)					//��ѭ�� 
	{
		for(j = 0; j < n; j++)				//��ѭ�� 
		{
			if(i > j)						//������������������ 
			{
				printf("%2d ", tail);
			}
			else
			{
				k = j*(j + 1) / 2 + i; 		//������������������Ӧ��һά�����е��±�
				printf("%2d ", array[k]);		//��� 
			}
			 
		}
		printf("\n");
	}
}


int main()
{
	printf("*************************************************************\n");
	printf("***** �ԽǾ�����Ԫ�飩��ѹ���洢��    enter      'a'  *****\n");
	printf("***** �Գƾ��������ǵ�ѹ���洢��        enter      'b'  *****\n");
	printf("***** �Գƾ��������ǵ�ѹ���洢��        enter      'c'  *****\n");
	printf("***** �����Ǿ����ѹ���洢��            enter      'd'  *****\n");
	printf("***** �����Ǿ����ѹ���洢��            enter      'e'  *****\n");
	printf("*************************************************************\n");
	int n;								//n Ϊ����Ľ���
	printf("���������Ľ�����      ");
	scanf("%d", &n);					
	
	char str;
	
	do
	{
		printf("\n");
		printf("Please enter a char:    ");
		str = getche();
		printf("\n");
		switch(str)
		{
			case 'a':
				{
					Diagonal(n);
					break;
				}
			
			case 'b':
				{
					SymmetricOn(n);
					break;
				}
				
			case 'c':
				{
					SymmetricIn(n);
					break;
				}
				
			case 'd':
				{
					InArray(n);
					break;
				}
				
			case 'e':
				{
					OnArray(n);
					break;
				}
				
			default:printf("Wrong!!!\n");
		}
	}while(str != 'q');
	
	return 0;
}
