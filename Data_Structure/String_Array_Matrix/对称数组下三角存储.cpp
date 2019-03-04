#include<stdio.h>


void PrintfArray(int *array, int n)
{
	int i, j;								//定义 i , j 作为矩阵的下标  
	int k;									// k 为存储在一维数组中数的下标 
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

void StoreArray(int n)
{
	int len, i;
	len = n * (n + 1) / 2;					//确定一维数组的长度 
	int array[len];							//申请一维数组 
				
	printf("请输入 %d 个数据：\n", len);
	for(i = 0; i < len; i++)
	{	
		scanf("%d", &array[i]);				//向一维数组中输入数据 
	}
	
	PrintfArray(array, n);
} 

int main()
{	
	int n;									//n 为矩阵的阶数
	printf("请输入矩阵的阶数：      ");
	scanf("%d", &n);
	StoreArray(n);

}
