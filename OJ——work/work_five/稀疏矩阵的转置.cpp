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

//��ϡ������ת��
void TransMatrix(Matrix &M, Matrix &T)
{
	int p, col, q = 1;							//p �� col Ϊ��������q Ϊת�þ��� T ��ǰԪ�صĳ�ʼֵ 
	T.mu = M.nu;								//���� T ���������� M ������ 
	T.nu = M.mu;								//���� T ���������� M ������ 
	T.tu = M.tu;								//���� T �ķ���Ԫ�������� M �ķ���Ԫ���� 
	
	if(T.tu)									//���	T ����ǿ� 
	{
		for(col = 1; col <= T.mu; col++)		//�Ӿ��� T �ĵ�һ�е����һ�� 
		{
			for(p = 1; p <= M.tu; p++)			//���� M �е�����Ԫ�� 
			if(M.data[p].j == col)				//�����Ԫ�ص��������ڵ�ǰ������ 
			{
				T.data[q].i = M.data[p].j;		//�� M ��������жԵ����� T ���� 
				T.data[q].j = M.data[p].i;
				T.data[q].e = M.data[p].e;
				q++;							//T ����ǰԪ��ָ���һ 
			}
		}
	}
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
	TransMatrix(A, B);
	PrintfMatrix(B);
}
