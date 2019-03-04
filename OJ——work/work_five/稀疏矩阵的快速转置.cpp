#include<stdio.h>

#define ERROR -1
#define OK 0

#define MAX_SIZE 12500

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
	int mu, nu, tu;					//矩阵的行数，列数，非零元个数 
}; 

void CreateMatrix(Matrix &M)
{
	int r, c, col, rol, dat, p = 0;		// r 是行数，c 是列数，col, rol 计数器，dat 临时存储输入矩阵数，p 实际矩阵个数计数器 
	Triple T;
	scanf("%d %d", &r, &c);				// 输入矩阵的行数和列数 
	
	M.mu = r;							//把行数列数赋值给三元组存储法的矩阵 
	M.nu = c;
	
	for (col = 1; col <= r; col++)
	{
		for (rol = 1; rol <= c; rol++)
		{
			scanf("%d", &dat);			//输入矩阵的元素 
			if( dat != 0 )				//判断该输入值是否为 0 ，不为 0 则进行三元组存储 
			{				
				p++;					//非零元个数加一 
				T.e = dat;				//赋值 
				T.i = col;				//赋该值的行坐标 
				T.j = rol;				//赋该值的列坐标 
				M.data[p] = T;			//将 T 赋给 M 存储 
			}	
		}
	}
	M.tu = p;							//非零元总个数赋给 M.tu 
}

//稀疏矩阵的快速转置
Status FastTransMatrix(Matrix M, Matrix &T)
{
	int col, t, p, q;
	int num[12500], copt[12500];
	
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	
	if (T.tu)
	{
		for (col = 1; col <= M.nu; ++col)
		{
			num[col] = 0;
		}
		
		for (t = 1; t <= M.tu; ++t)
		{
			++num[M.data[t].j];
		}
		
		copt[1] = 1;
		//求 M 中每一列的第一个非零元在 b.data 中的序号
		for (col = 2; col <= M.nu; ++col)
		{
			copt[col] = copt[col - 1] + num[col - 1];
		}
		
		for (p = 1; p <= M.tu; ++p)
		{
			col = M.data[p].j;
			q = copt[col];
			T.data[q].i = M.data[p].j;
			T.data[q].j = M.data[p].i;
			T.data[q].e = M.data[p].e;
			++copt[col];
		} // end  for
	}// end if
	
	return OK;
} 

//输出稀疏矩阵 
void PrintfMatrix(Matrix &M)
{
	int i, j, k = 1;
	Triple *p = M.data + 1;			// p 指向第一个非零元素.

	for (i = 1; i <= M.mu; i++)
	{
		for (j = 1; j <= M.nu; j++)
		{
			if(k <= M.tu && p->i == i && p->j == j)		// p 指向非零元，且 p 所指元素为当前循环的元素，即 p 是输入的值 
			{
				printf("%d ", p->e);
				p++;
				k++;
			} 
			else	//p 不是当前处理的元素，也就是说 p 不是输入的值 
			{
				printf("%d ", 0);
			}
		}
		printf("\n");
	} 
}

int main()
{
	Matrix A, B;
	CreateMatrix(A);
	FastTransMatrix(A, B);
	PrintfMatrix(B);
}
