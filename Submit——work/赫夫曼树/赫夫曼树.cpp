/*
	Name: �շ������� 
	Author: �ſ��� 
	Date: 17/11/18 19:10
	Description: 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	unsigned int weight;		//����Ȩֵ 
	unsigned int parent, lchild, rchild;	
}HTNode, * HuffmanTree;

typedef char * *HuffmanCode;

#define Order
//���غշ�������ǰ i �������Ȩֵ��С�����ĸ������
int min(HuffmanTree t, int i)
{
	int j, m;
	unsigned int k = UINT_MAX;
	for (j = 1; j <= i; j++)			//����ǰ i ���ڵ� 
	{
		if (t[j].weight < k && t[j].parent == 0)		//t[j]��ȨֵС�� k,������ �ĸ��ڵ� 
		{
			k = t[j].weight;		//t[j] ��Ȩֵ���� k  
			m = j;					//��Ÿ��� m 
		}
	} 
	t[m].parent = 1;			//��ѡ�еĸ�����˫�׸�����ֵ������ڶ��β���
	return m; 
}

//�ںշ�������ǰ i ���ڵ���ѡ������Ȩֵ��С�����ĸ��ڵ����
void select(HuffmanTree t, int i, int &s1, int &s2)
{
	#ifdef Order			//����������ж�����Order �����������������
		int j;
	#endif
		s1 = min(t, i);
		s2 = min(t, i);
	#ifdef Order
		if (s1 > s2)
		{
			j = s1;
			s1 = s2;		//s1 ��Ȩֵ��С����������Ž�С�� 
			s2 = j;			//s2 ��Ȩֵ��С����������Žϴ�� 
		}
	#endif 
} 

//����շ�����
void HuffmanCoding(HuffmanTree &HT, HuffmanTree &HC, int *w, int n)
{
	int start;
	unsigned f;
	
	int m, i, s1, s2;
	unsigned c;
	HuffmanTree p;
	char *cd;
	
	if (n <= 1)			//Ҷ�ӽڵ��������� 1  
		return;
	
	m = 2 * n - 1;		//n ��Ҷ�ӽ��ĺշ��������� m ����� 
	HT = (HuffmanTree) malloc ((m + 1) * sizeof(HTNode));		// 0 �ŵ�Ԫû���� 
	for (p = HT + 1, i = 1; i <= n; i++, p++, w++)			//��һ�ŵ�Ԫ��ʼ�� n �ŵ�Ԫ����Ҷ�ӽ�㸳ֵ 
	{	// p �ĳ�ֵָ��һ�ŵ�Ԫ 
		(*p).weight = *w;		//��Ȩֵ		
		(*p).parent = 0;		//˫����Ϊ�� 
		(*p).lchild = 0;		//���Һ���Ϊ�� 
		(*p).rchild = 0;
	}
	for (; i <= m; i++, p++)	// i �� n + 1�� m 
		(*p).parent = 0;		//�������˫�����ֵΪ 0 
		
	for (i = n + 1; i <= m; i++)	//���շ����� 
	{			
		select(HT, i - 1, s1, s2);	//ѡ����С�������ڵ� 
		HT[s1].parent = HT[s2].parent = i;	// i �ŵ�Ԫ�� s1 s2 ��˫�� 
		HT[i].lchild = s1;					// i �ŵ�Ԫ�����Һ��ӷֱ��� s1 �� s2 
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;	// i �ŵ�Ԫ��Ȩֵ�� s1 �� s2 ��Ȩֵ֮�� 
	}
	
	HC = (HuffmanTree) malloc ((n + 1) * sizeof(char*));
	//���� n ���ַ������ͷָ������
	cd = (char*) malloc (n * sizeof(char));	
	cd[n - 1] = '\0';	//�����������
	
	for (i = 1; i <= n; i++)		//����ַ���շ������� 
	{
		start = n - 1;				//�������λ�� 
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)	//��Ҷ�ӵ������������ 
		{
			if (HT[f].lchild == c)		//c ����˫�׵����� 
				cd[--start] = '0';		//��Ҷ�������ֵ ' 0 ' 
			else 						// c ����˫�׵��Һ��� 
				cd[--start] = '1';		//��Ҷ�������ֵ��1�� 
		} 
		HC[i] = (char*) malloc ((n - start) * sizeof (char));
		strcpy(HC[i], &cd[start]);		//�� cd ��ֵ���뵽 HC 
	} 
	free(cd);			//�ͷſռ� 
} 

int main()
{
	HuffmanTree HT;
	HuffmanCode HC;
	int *w, n, i;
	printf("������Ȩֵ�ĸ���(>1) ��    ");
	scanf("%d", &n);
	w = (int*) malloc (n * sizeof(int));		//���ɴ�� n ��Ȩֵ�Ŀռ�
	printf("���������� %d ��Ȩֵ�����Σ�:\n", n);
	for (i = 0; i < n; i++)
		scanf("%d", w + i);
		
	HuffmanCoding(HT, HC, w, n);				//����w����� n ��Ȩֵ����շ�������n ���շ����������HC 
		
	for (i = 1; i <= n; i++)
		puts(HC[i]);							//��������շ������� 
} 

