#include<stdio.h>
#include<conio.h>

#define ERROR 0
#define OK 1

#define MAX_SIZE 100

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

//����ϡ����� 
Status CreateMatrix(Matrix &M)
{
	int i;
	Triple 	T;
	Status k;
	
	printf("��������������������������Ԫ������");
	scanf("%d %d %d", &M.mu, &M.nu, &M.tu);
	
	if(M.tu > MAX_SIZE)			//����Ԫ����̫��
		return ERROR;
		
	M.data[0].i = 0;
	
	for (i = 1; i <= M.tu; i++)
	{
		do
		{
			printf("�밴����˳������� %d ������Ԫ�����ڵ��У�1~%d�����У�1~%d����Ԫ��ֵ��", i, M.mu, M.nu);
			scanf("%d %d %d", &T.i, &T.j, &T.e);
			
			k = 0;			//����ֵ�ķ�Χ��ȷ��־
			
			if(T.i < 1 || T.i > M.mu || T.j < 1 || T.j > M.nu)	//���к��г�����Χ 
				k = 1; 
			if(T.i < M.data[i - 1].i || T.i == M.data[i - 1].i && T.j <= M.data[i - 1].j)	//�л��е�˳���д� 
				k = 1;		
		}while (k);
		M.data[i] = T;				//���������ȷ��ֵ������Ԫ��ṹ�� M ����Ӧ��Ԫ 
	} 
	
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
				printf("%3d", p->e);
				p++;
				k++;
			} 
			else	//p ���ǵ�ǰ�����Ԫ�أ�Ҳ����˵ p ���������ֵ 
			{
				printf("%3d", 0);
			}
		}
		printf("\n");
	} 
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

//ϡ�����Ŀ���ת��
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

//ϡ��������� 
Status MulMatrix(Matrix M, Matrix N, Matrix &Q) 
{
	int col, rol, p;		// col �� rol , p ���������� 
	
	if(M.nu != N.mu)		//�����޷����
		return ERROR;
		
	Q.mu = M.mu;			//Q ���е��� M ������ 
	Q.nu = N.nu;			//Q ���е��� N ������ 
	Q.tu = 0;				//Q �ķ���Ԫ������ֵΪ 0
	
	p = 0;					// p ��ʼֵΪ 0 ����ʾ�˻�����Ŀǰ�� 0 ��Ԫ�� 
	for(col = 1; col <= M.tu; col++)								//���� M ����ķ� 0 Ԫ�� 
	{														
		for(rol = 1; rol <= N.tu; rol++)							//���� N ����ķ� 0 Ԫ�� 
		{
			if(M.data[col].j == N.data[rol].i)						//�� M �з���Ԫ���������������� N �з���Ԫ������������ 
			{														//��������� 
				p++;												// Q �������Ԫ������һ 
				Q.data[p].e = M.data[col].e * N.data[rol].e;		//�˻�������� Q  
				Q.data[p].i = M.data[col].i;						//�˻�������������� M ��Ԫ�ص� �� 
				Q.data[p].j = N.data[rol].j;						//�ɼ�������������� N ��Ԫ�ص� �� 
			}
		}
	} 
	Q.tu = p;						// p ��ʱ���� Q �з���Ԫ�ص��ܺ�  
	
	PrintfMatrix(Q);				//��� Q ���� 
	
	return OK;
}

//����ϡ�����
Status DestroyMatrix(Matrix &M)
{
	M.mu = M.nu = M.tu = 0;
	return OK;
}

 
int main()
{
	printf("***********************************************\n");
	printf("*****  ����ϡ����� enter        'a'    *****\n");
	printf("*****  ���ϡ����� enter        'b'    *****\n");
	printf("*****  ϡ������ת�ã�enter       'c'    *****\n");
	printf("*****  ϡ��������ˣ� enter      'd'    *****\n");
	printf("*****  ϡ�������ٵ�ת�ã�enter   'e'    *****\n");
	printf("*****  ����ϡ����� enter        'f'    *****\n");
	printf("***********************************************\n");
	
	Matrix A, B, C;		//��������ϡ��������
	int back;
	char str;			//ѡ���ַ�
	
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
						printf("��Ϊ�㴴����һ��ϡ����� A ������\n");
					else
						printf("����ʧ�ܣ�����\n");
					break;
				}
			case 'b':
				{
					printf("ϡ����� A Ϊ:\n");
					PrintfMatrix(A);
					break;
				}
			case 'c':
				{
					TransMatrix(A, B);
					printf("ϡ����� A ��ת��Ϊ��\n");
					PrintfMatrix(B);
					break;
				}
			case 'd':
				{
					printf("��������� A :\n");
					CreateMatrix(A);
					printf("��������� B ������������� A ��������ͬ��:\n");
					CreateMatrix(B);
					printf("A B ������˵Ľ��Ϊ:\n");
					MulMatrix(A, B, C);
					break;
				}
			case 'e':
				{
					FastTransMatrix(A, B);
					printf("ϡ����� A ��ת��Ϊ��\n");
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
