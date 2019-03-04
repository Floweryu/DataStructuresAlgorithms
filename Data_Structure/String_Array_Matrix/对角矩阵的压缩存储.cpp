#include<stdio.h>
#include<math.h> 

void PrintfArray(int *array, int n)
{
	int i, j;												//定义 i , j 作为矩阵的下标  
	int k, tail = 0;													// k 为存储在一维数组中数的下标 
	for(i = 0; i < n; i++)									//行循环 
	{
		for(j = 0; j < n; j++)								//列循环 
		{
			k = 2 * i + j;
			if(abs(i - j) <= 1)
				printf("%2d ", array[k]);						//输出 
			else
				printf("%2d ", tail);
		}
		printf("\n");
	}
}

void StoreArray(int n)
{
	int len, i;
	len = 3 * n - 2;					//确定一维数组的长度
	int array[len];						//申请一维数组 
	
	printf("请输入 %d 个数据：\n", len);	
	for(i = 0; i < len; i++)
	{
		scanf("%d", &array[i]);			//向一维数组中输入数据 
	}
	
	PrintfArray(array, n);
} 

int main()
{
	int n;								//n 为矩阵的阶数
	
	printf("请输入矩阵的阶数：      ");
	scanf("%d", &n);					
	StoreArray(n);

}
