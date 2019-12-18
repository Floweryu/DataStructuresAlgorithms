/**
* Author : ZhangJunFeng
* Date : 2018-11-28-18.32.05
* Function: �շ���������
* Description :
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct
{
	unsigned int weight;		//����Ȩֵ
	unsigned int parent, lchild, rchild;
}HTNode, * HuffmanTree;

typedef char * *HuffmanCode;

//ѡ��parentΪ 0 ��weight��С�������ڵ�
void Select(HuffmanTree HT, int n, int &s1, int &s2)
{
    int minni = MAX, flag = 0, i;       //MAX�ĳ�ʼֵ����Ϊ��Ȩֵ�������flag��¼��С�ڵ��±�

    for (i = 1; i <= n; i++)
    {
        if (HT[i].weight < minni && HT[i].parent == 0)     //��ȨֵС��ʱ �� ���ڵ�Ϊ 0 ʱ
        {
            minni = HT[i].weight;
            flag = i;
        }
    }
    HT[flag].parent = 1;                //���Ѿ�������ýڵ��˫����һ�������ٴβ���
    s1 = flag;

    minni = MAX;
    flag = 0;
    for (i = 1; i <= n; i++)
    {
        if (HT[i].weight < minni && HT[i].parent == 0 && i != s1)
        {
            minni = HT[i].weight;
            flag = i;
        }
    }
    HT[flag].parent = 1;
    s2 = flag;

    int temp;       //����ε����ʦ���н��б��룬��������ж��ֹ���������
    if (s1 > s2)
    {
        temp = s1;
        s1 = s2;
        s2 = temp;
    }

}

//����շ�����
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{
	int start;
	unsigned f;

	int m, i;
	unsigned c;
	HuffmanTree p;
	char *cd;

	if (n <= 1)
		return;

	m = 2 * n - 1;
	HT = (HuffmanTree) malloc ((m + 1) * sizeof(HTNode));

	for (p = HT + 1, i = 1; i <= n; i++, p++, w++)			    //��һ�ŵ�Ԫ��ʼ�� n �ŵ�Ԫ����Ҷ�ӽ�㸳ֵ
	{
		(*p).weight = *w;
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}
	for (; i <= m; i++, p++)	             // i �� n + 1�� m
		(*p).parent = 0;		    //�������˫�����ֵΪ 0

	for (i = n + 1; i <= m; i++)	//���շ�����
	{
	    int s1, s2;
		Select(HT, i - 1, s1, s2);	                    //s1��s2 Ϊ��ѡ��ڵ��λ��
		HT[s1].parent = HT[s2].parent = i;	            // i �ŵ�Ԫ�� s1 s2 ��˫��
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;	// i �ŵ�Ԫ��Ȩֵ�� s1 �� s2 ��Ȩֵ֮��
	}

	HC = (HuffmanCode) malloc ((n + 1) * sizeof(char*));

	cd = (char*) malloc (n * sizeof(char));              //���� n ���ַ������ͷָ������
	cd[n - 1] = '\0';	                                 //�����������

	for (i = 1; i <= n; i++)
	{
		start = n - 1;
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)	//��Ҷ�ӵ������������
		{
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
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

	FILE *fp;
	fp = fopen("zipdata.txt","r");
	if (fp == NULL)
    {
        printf("cannot open the file!!!\n");
        exit(-1);
    }

	//printf("������Ȩֵ�ĸ���(>1) ��    ");
	//scanf("%d", &n);
	fscanf(fp, "%d", &n);

	w = (int*) malloc (n * sizeof(int));		//���ɴ�� n ��Ȩֵ�Ŀռ�
	printf("���������� %d ��Ȩֵ�����Σ�:\n", n);
	for (i = 0; i < n; i++)
		//scanf("%d", w + i);
		fscanf(fp, "%d", w + i);

	HuffmanCoding(HT, HC, w, n);				//����w����� n ��Ȩֵ����շ�������n ���շ����������HC

	for (i = 1; i <= n; i++)
		puts(HC[i]);							//��������շ�������
}