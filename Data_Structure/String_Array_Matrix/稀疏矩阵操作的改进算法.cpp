#include<stdio.h>
#include<conio.h>

#define ERROR -1
#define OK 0

#define MAX_SIZE 100		//����Ԫ�����ֵ
#define MAX_RC   20			//�������

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
	int rops[MAX_RC + 1]; 			//���е�һ������Ԫ�ص�λ�ñ�
	int mu, nu, tu;					//���������������������Ԫ����
};

//����ϡ�����
Status CreateMatrix(Matrix &M)
{
	int i, j;
	Triple 	T;
	Status k;

	printf("��������������������������Ԫ������");
	scanf("%d %d %d", &M.mu, &M.nu, &M.tu);

	if(M.tu > MAX_SIZE || M.mu > MAX_RC)			//����Ԫ����̫�� �� ����̫��
		return ERROR;

	M.data[0].i = 0;

	for (i = 1; i <= M.tu; i++)		//һ������ M.tu ������Ԫ��
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

	for (i = 1; i <= M.mu; i++)		//�� rops����ֵ 1 (������ memset ������
	{
		M.rops[i] = 1;
	}

	for (i = 1; i <= M.tu; i++)		//����ÿ������Ԫ�أ�����ͳ�ƣ������� rops
	{
		for (j = M.data[i].i + 1; j <= M.mu; j++)	//�ӷ���Ԫ�����е���һ�п�ʼ
		{
			M.rops[j]++;			//ÿ�е�һ������Ԫλ�ü�һ
		}
	}
	return OK;
}

//��ϡ������ת��
void TransMatrix(Matrix &M, Matrix &T)
{
	int i, j, k, num[MAX_RC + 1];

	T.mu = M.nu;						//���� T ���������� M ������
	T.nu = M.mu;						//���� T ���������� M ������
	T.tu = M.tu;						//���� T �ķ���Ԫ�������� M �ķ���Ԫ����

	if(T.tu == 0)						//�������Ϊ�վ���
		return ERROR;

	for (i = 1; i <= T.mu; i++)
	{
		num[i] = 0;						//���� T ��ÿ�з���Ԫ�ĸ�����ʼֵΪ 0
	}

	for (i = 1; i <= M.tu; i++)
	{
		num[M.data[i].j]++;				//ÿ�еķ���Ԫ�ĸ���
	}

	T.rops[1] = 1;						// T �е�һ�е�һ�еķ���Ԫ�ص����Ϊ 1

	for (i = 2; i <= T.mu; i++)			//�Ӿ���ڶ��е����һ��
	{
		T.rops[i] = T.rops[i - 1] + num[i - 1];		//�� T �е� i �е�һ������Ԫ�����
	}

	for (i = 1; i <= T.mu; i++)
	{
		num[i] = T.rops[i];				//��ǰ����Ԫ���� T �д�ŵ�λ��
	}

	for (i = 1; i <= M.tu; i++)			//��ֵ�Ե�
	{
		j = M.data[i].j;
		k = num[j]++;					//���� T �е���ż�һ
		T.data[k].i = M.data[i].j;
		T.data[k].j = M.data[i].i;
		T.data[k].e = M.data[i].e;
	}
}
