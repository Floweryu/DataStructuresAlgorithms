#include<stdio.h>
#include<conio.h>

#define ERROR -1
#define OK 0

#define MAX_SIZE 100		//非零元素最大值
#define MAX_RC   20			//最大行数

typedef int ElemType;
typedef int Status;

struct Triple
{
	int i, j;		//行下标，列下标
	ElemType e;		//非零元素值
};

struct Matrix
{
	Triple 	data[MAX_SIZE + 1];		//非零元三元组表，data[0] 未用
	int rops[MAX_RC + 1]; 			//各行第一个非零元素的位置表
	int mu, nu, tu;					//矩阵的行数，列数，非零元个数
};

//创建稀疏矩阵
Status CreateMatrix(Matrix &M)
{
	int i, j;
	Triple 	T;
	Status k;

	printf("请输入矩阵的行数，列数，非零元个数：");
	scanf("%d %d %d", &M.mu, &M.nu, &M.tu);

	if(M.tu > MAX_SIZE || M.mu > MAX_RC)			//非零元个数太多 或 行数太多
		return ERROR;

	M.data[0].i = 0;

	for (i = 1; i <= M.tu; i++)		//一次输入 M.tu 个非零元素
	{
		do
		{
			printf("请按行序顺序输入第 %d 个非零元素所在的行（1~%d），列（1~%d），元素值：", i, M.mu, M.nu);
			scanf("%d %d %d", &T.i, &T.j, &T.e);

			k = 0;			//输入值的范围正确标志

			if(T.i < 1 || T.i > M.mu || T.j < 1 || T.j > M.nu)	//若行和列超出范围
				k = 1;
			if(T.i < M.data[i - 1].i || T.i == M.data[i - 1].i && T.j <= M.data[i - 1].j)	//行或列的顺序有错
				k = 1;
		}while (k);
		M.data[i] = T;				//将输入的正确的值赋给三元组结构体 M 的相应单元
	}

	for (i = 1; i <= M.mu; i++)		//给 rops赋初值 1 (可以用 memset 函数）
	{
		M.rops[i] = 1;
	}

	for (i = 1; i <= M.tu; i++)		//对于每个非零元素，按行统计，并计入 rops
	{
		for (j = M.data[i].i + 1; j <= M.mu; j++)	//从非零元所在行的下一行开始
		{
			M.rops[j]++;			//每行第一个非零元位置加一
		}
	}
	return OK;
}

//求稀疏矩阵的转置
void TransMatrix(Matrix &M, Matrix &T)
{
	int i, j, k, num[MAX_RC + 1];

	T.mu = M.nu;						//矩阵 T 的行数等于 M 的列数
	T.nu = M.mu;						//矩阵 T 的列数等于 M 的行数
	T.tu = M.tu;						//矩阵 T 的非零元个数等于 M 的非零元个数

	if(T.tu == 0)						//如果矩阵为空矩阵
		return ERROR;

	for (i = 1; i <= T.mu; i++)
	{
		num[i] = 0;						//矩阵 T 的每行非零元的个数初始值为 0
	}

	for (i = 1; i <= M.tu; i++)
	{
		num[M.data[i].j]++;				//每列的非零元的个数
	}

	T.rops[1] = 1;						// T 中第一行第一列的非零元素的序号为 1

	for (i = 2; i <= T.mu; i++)			//从矩阵第二行到最后一行
	{
		T.rops[i] = T.rops[i - 1] + num[i - 1];		//求 T 中第 i 行第一个非零元的序号
	}

	for (i = 1; i <= T.mu; i++)
	{
		num[i] = T.rops[i];				//当前非零元素在 T 中存放的位置
	}

	for (i = 1; i <= M.tu; i++)			//将值对调
	{
		j = M.data[i].j;
		k = num[j]++;					//矩阵 T 中的序号加一
		T.data[k].i = M.data[i].j;
		T.data[k].j = M.data[i].i;
		T.data[k].e = M.data[i].e;
	}
}
