#include<stdio.h>
#include<math.h>
#include<conio.h>

void Diagonal(int n)
{
	int len, i, j, k, tail = 0;					//定义 i , j 作为矩阵的下标 , k 为存储在一维数组中数的下标 
	len = 3 * n - 2;							//确定一维数组的长度
	int array[len];								//申请一维数组 
	
	printf("请输入 %d 个数据：\n", len);	
	for(i = 0; i < len; i++)
	{
		scanf("%d", &array[i]);					//向一维数组中输入数据 
	}
					
	for(i = 0; i < n; i++)						//行循环 
	{
		for(j = 0; j < n; j++)					//列循环 
		{
			k = 2 * i + j;
			if(abs(i - j) <= 1)
				printf("%2d ", array[k]);		//输出 
			else
				printf("%2d ", tail);
		}
		printf("\n");
	}
}

void SymmetricOn(int n)
{
	int len, i, j, k;										//定义 i , j 作为矩阵的下标 , k 为存储在一维数组中数的下标 
	len = n * (n + 1) / 2;									//确定一维数组的长度
	int array[len];											//申请一维数组 
	
	printf("请输入 %d 个数据：\n", len);	
	for(i = 0; i < len; i++)
	{
		scanf("%d", &array[i]);								//向一维数组中输入数据 
	}

	for(i = 0; i < n; i++)									//行循环 
	{
		for(j = 0; j < n; j++)								//列循环 
		{
			if(i <= j)										//上三角区域矩阵坐标对应的一维数组中的下标 
			{
				k = i * (2 * n - i + 1) / 2 + j - i;
			}
		
			else
			{
				k = j * (2 * n - j + 1) / 2 + i - j;		//下三角区域矩阵坐标对应的一维数组中的下标 
			}
			printf("%2d ", array[k]);						//输出 
		}
		printf("\n");
	}
}

void SymmetricIn(int n)
{
	int len, i, j, k;						//定义 i , j 作为矩阵的下标 , k 为存储在一维数组中数的下标 
	len = n * (n + 1) / 2;					//确定一维数组的长度
	int array[len];							//申请一维数组 
	
	printf("请输入 %d 个数据：\n", len);	
	for(i = 0; i < len; i++)
	{
		scanf("%d", &array[i]);				//向一维数组中输入数据 
	}

	for(i = 0; i < n; i++)					//行循环 
	{
		for(j = 0; j < n; j++)				//列循环 
		{
			if(i >= j)						//输出矩阵的下三角区域 
			{
				k = i*(i + 1) / 2 + j;		//下三角区域矩阵坐标对应的一维数组中的下标 
			}
			else
			{
				k = j*(j + 1) / 2 + i; 		//上三角区域矩阵坐标对应的一维数组中的下标 
			}
			printf("%2d ", array[k]);		//输出 
		}
		printf("\n");
	}
}

void InArray(int n)
{
	int i, j, len;							//定义 i , j 作为矩阵的下标  
	int k, tail = 0;						// k 为存储在一维数组中数的下标 
	len = n * (n + 1) / 2;					//确定一维数组的长度 
	int array[len];							//申请一维数组 
				
	printf("请输入 %d 个数据：\n", len);
	for(i = 0; i < len; i++)
	{	
		scanf("%d", &array[i]);				//向一维数组中输入数据 
	}
	
	for(i = 0; i < n; i++)					//行循环 
	{
		for(j = 0; j < n; j++)				//列循环 
		{
			if(i >= j)						//输出矩阵的下三角区域 
			{
				k = i*(i + 1) / 2 + j;		//下三角区域矩阵坐标对应的一维数组中的下标 
				printf("%2d ", array[k]);	//输出 
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
	int i, j, len;							//定义 i , j 作为矩阵的下标  
	int k, tail = 0;						// k 为存储在一维数组中数的下标 
	len = n * (n + 1) / 2;					//确定一维数组的长度 
	int array[len];							//申请一维数组 
				
	printf("请输入 %d 个数据：\n", len);
	for(i = 0; i < len; i++)
	{	
		scanf("%d", &array[i]);				//向一维数组中输入数据 
	}
	
	for(i = 0; i < n; i++)					//行循环 
	{
		for(j = 0; j < n; j++)				//列循环 
		{
			if(i > j)						//输出矩阵的下三角区域 
			{
				printf("%2d ", tail);
			}
			else
			{
				k = j*(j + 1) / 2 + i; 		//上三角区域矩阵坐标对应的一维数组中的下标
				printf("%2d ", array[k]);		//输出 
			}
			 
		}
		printf("\n");
	}
}


int main()
{
	printf("*************************************************************\n");
	printf("***** 对角矩阵（三元组）的压缩存储，    enter      'a'  *****\n");
	printf("***** 对称矩阵上三角的压缩存储，        enter      'b'  *****\n");
	printf("***** 对称矩阵下三角的压缩存储，        enter      'c'  *****\n");
	printf("***** 下三角矩阵的压缩存储，            enter      'd'  *****\n");
	printf("***** 上三角矩阵的压缩存储，            enter      'e'  *****\n");
	printf("*************************************************************\n");
	int n;								//n 为矩阵的阶数
	printf("请输入矩阵的阶数：      ");
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
