#include<stdio.h>
#include<conio.h>

#define ERROR 0
#define OK 1

#define MAX_SIZE 100

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

//创建稀疏矩阵 
Status CreateMatrix(Matrix &M)
{
	int i;
	Triple 	T;
	Status k;
	
	printf("请输入矩阵的行数，列数，非零元个数：");
	scanf("%d %d %d", &M.mu, &M.nu, &M.tu);
	
	if(M.tu > MAX_SIZE)			//非零元个数太多
		return ERROR;
		
	M.data[0].i = 0;
	
	for (i = 1; i <= M.tu; i++)
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
				printf("%3d", p->e);
				p++;
				k++;
			} 
			else	//p 不是当前处理的元素，也就是说 p 不是输入的值 
			{
				printf("%3d", 0);
			}
		}
		printf("\n");
	} 
}

//求稀疏矩阵的转置
void TransMatrix(Matrix &M, Matrix &T)
{
	int p, col, q = 1;							//p ， col 为计数器，q 为转置矩阵 T 当前元素的初始值 
	T.mu = M.nu;								//矩阵 T 的行数等于 M 的列数 
	T.nu = M.mu;								//矩阵 T 的列数等于 M 的行数 
	T.tu = M.tu;								//矩阵 T 的非零元个数等于 M 的非零元个数 
	
	if(T.tu)									//如果	T 矩阵非空 
	{
		for(col = 1; col <= T.mu; col++)		//从矩阵 T 的第一行到最后一行 
		{
			for(p = 1; p <= M.tu; p++)			//对于 M 中的所有元素 
			if(M.data[p].j == col)				//如果该元素的列数等于当前的行数 
			{
				T.data[q].i = M.data[p].j;		//把 M 矩阵的行列对调赋给 T 矩阵 
				T.data[q].j = M.data[p].i;
				T.data[q].e = M.data[p].e;
				q++;							//T 矩阵当前元素指针加一 
			}
		}
	}
} 

//稀疏矩阵的快速转置
Status FastTransMatrix(Matrix M, Matrix &T)
{
	int col, t, p, q;
	int num[200], copt[200];
	
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

//稀疏矩阵的相乘 
Status MulMatrix(Matrix M, Matrix N, Matrix &Q) 
{
	int col, rol, p;		// col 和 rol , p 都用来计数 
	
	if(M.nu != N.mu)		//矩阵无法相乘
		return ERROR;
		
	Q.mu = M.mu;			//Q 的行等于 M 的行数 
	Q.nu = N.nu;			//Q 的列等于 N 的列数 
	Q.tu = 0;				//Q 的非零元个数初值为 0
	
	p = 0;					// p 初始值为 0 ，表示乘积矩阵目前有 0 个元素 
	for(col = 1; col <= M.tu; col++)								//遍历 M 矩阵的非 0 元素 
	{														
		for(rol = 1; rol <= N.tu; rol++)							//遍历 N 矩阵的非 0 元素 
		{
			if(M.data[col].j == N.data[rol].i)						//若 M 中非零元素所处的列数等于 N 中非零元素所处的行数 
			{														//即可以相乘 
				p++;												// Q 矩阵非零元个数加一 
				Q.data[p].e = M.data[col].e * N.data[rol].e;		//乘积结果放在 Q  
				Q.data[p].i = M.data[col].i;						//乘积结果的行数等于 M 中元素的 行 
				Q.data[p].j = N.data[rol].j;						//成绩结果的列数等于 N 中元素的 列 
			}
		}
	} 
	Q.tu = p;						// p 此时等于 Q 中非零元素的总和  
	
	PrintfMatrix(Q);				//输出 Q 矩阵 
	
	return OK;
}

//销毁稀疏矩阵
Status DestroyMatrix(Matrix &M)
{
	M.mu = M.nu = M.tu = 0;
	return OK;
}

 
int main()
{
	printf("***********************************************\n");
	printf("*****  创建稀疏矩阵， enter        'a'    *****\n");
	printf("*****  输出稀疏矩阵， enter        'b'    *****\n");
	printf("*****  稀疏矩阵的转置，enter       'c'    *****\n");
	printf("*****  稀疏矩阵的相乘， enter      'd'    *****\n");
	printf("*****  稀疏矩阵快速的转置，enter   'e'    *****\n");
	printf("*****  销毁稀疏矩阵， enter        'f'    *****\n");
	printf("***********************************************\n");
	
	Matrix A, B, C;		//定义三个稀疏矩阵待用
	int back;
	char str;			//选择字符
	
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
					back = CreateMatrix(A);
					if( back )
						printf("以为你创建好一个稀疏矩阵 A ！！！\n");
					else
						printf("创建失败！！！\n");
					break;
				}
			case 'b':
				{
					printf("稀疏矩阵 A 为:\n");
					PrintfMatrix(A);
					break;
				}
			case 'c':
				{
					TransMatrix(A, B);
					printf("稀疏矩阵 A 的转置为：\n");
					PrintfMatrix(B);
					break;
				}
			case 'd':
				{
					printf("请输入矩阵 A :\n");
					CreateMatrix(A);
					printf("请输入矩阵 B ，（行数与矩阵 A 的列数相同）:\n");
					CreateMatrix(B);
					printf("A B 矩阵相乘的结果为:\n");
					MulMatrix(A, B, C);
					break;
				}
			case 'e':
				{
					FastTransMatrix(A, B);
					printf("稀疏矩阵 A 的转置为：\n");
					PrintfMatrix(B);
					break;
				}
			case 'f':
				{
					DestroyMatrix(A);
					break;
				}
			default: printf("Error!!!\n");
		}
		
	}while( str != 'q' ); 
	
}
