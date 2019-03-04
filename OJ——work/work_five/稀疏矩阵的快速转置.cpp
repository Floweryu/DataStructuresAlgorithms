#include<stdio.h>

#define ERROR -1
#define OK 0

#define MAX_SIZE 12500

typedef int ElemType;
typedef int Status;

struct Triple
{
	int i, j;		//���±꣬���±�
	ElemType e;		//����Ԫ��ֵ 
};

struct Matrix
{
	Triple 	data[MAX_SIZE + 1];		//����Ԫ��Ԫ���data[0] δ��
	int mu, nu, tu;					//���������������������Ԫ���� 
}; 

void CreateMatrix(Matrix &M)
{
	int r, c, col, rol, dat, p = 0;		// r ��������c ��������col, rol ��������dat ��ʱ�洢�����������p ʵ�ʾ������������ 
	Triple T;
	scanf("%d %d", &r, &c);				// ������������������ 
	
	M.mu = r;							//������������ֵ����Ԫ��洢���ľ��� 
	M.nu = c;
	
	for (col = 1; col <= r; col++)
	{
		for (rol = 1; rol <= c; rol++)
		{
			scanf("%d", &dat);			//��������Ԫ�� 
			if( dat != 0 )				//�жϸ�����ֵ�Ƿ�Ϊ 0 ����Ϊ 0 �������Ԫ��洢 
			{				
				p++;					//����Ԫ������һ 
				T.e = dat;				//��ֵ 
				T.i = col;				//����ֵ�������� 
				T.j = rol;				//����ֵ�������� 
				M.data[p] = T;			//�� T ���� M �洢 
			}	
		}
	}
	M.tu = p;							//����Ԫ�ܸ������� M.tu 
}

//ϡ�����Ŀ���ת��
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
		//�� M ��ÿһ�еĵ�һ������Ԫ�� b.data �е����
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

//���ϡ����� 
void PrintfMatrix(Matrix &M)
{
	int i, j, k = 1;
	Triple *p = M.data + 1;			// p ָ���һ������Ԫ��.

	for (i = 1; i <= M.mu; i++)
	{
		for (j = 1; j <= M.nu; j++)
		{
			if(k <= M.tu && p->i == i && p->j == j)		// p ָ�����Ԫ���� p ��ָԪ��Ϊ��ǰѭ����Ԫ�أ��� p �������ֵ 
			{
				printf("%d ", p->e);
				p++;
				k++;
			} 
			else	//p ���ǵ�ǰ�����Ԫ�أ�Ҳ����˵ p ���������ֵ 
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
