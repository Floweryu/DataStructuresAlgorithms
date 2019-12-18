/**
* Author : ZhangJunFeng
* Date : 2018-11-28-18.32.05
* Function: 赫夫曼树编码
* Description :
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct
{
	unsigned int weight;		//结点的权值
	unsigned int parent, lchild, rchild;
}HTNode, * HuffmanTree;

typedef char * *HuffmanCode;

//选择parent为 0 且weight最小的两个节点
void Select(HuffmanTree HT, int n, int &s1, int &s2)
{
    int minni = MAX, flag = 0, i;       //MAX的初始值定义为比权值大的数，flag记录最小节点下标

    for (i = 1; i <= n; i++)
    {
        if (HT[i].weight < minni && HT[i].parent == 0)     //当权值小于时 且 父节点为 0 时
        {
            minni = HT[i].weight;
            flag = i;
        }
    }
    HT[flag].parent = 1;                //把已经处理过得节点的双亲置一，避免再次查找
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

    int temp;       //按严蔚敏老师书中进行编码，否则可以有多种哈夫曼编码
    if (s1 > s2)
    {
        temp = s1;
        s1 = s2;
        s2 = temp;
    }

}

//构造赫夫曼树
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

	for (p = HT + 1, i = 1; i <= n; i++, p++, w++)			    //从一号单元开始到 n 号单元，给叶子结点赋值
	{
		(*p).weight = *w;
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}
	for (; i <= m; i++, p++)	             // i 从 n + 1到 m
		(*p).parent = 0;		    //其余结点的双亲域初值为 0

	for (i = n + 1; i <= m; i++)	//建赫夫曼树
	{
	    int s1, s2;
		Select(HT, i - 1, s1, s2);	                    //s1、s2 为被选择节点的位置
		HT[s1].parent = HT[s2].parent = i;	            // i 号单元是 s1 s2 的双亲
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;	// i 号单元的权值是 s1 和 s2 的权值之和
	}

	HC = (HuffmanCode) malloc ((n + 1) * sizeof(char*));

	cd = (char*) malloc (n * sizeof(char));              //分配 n 个字符编码的头指针向量
	cd[n - 1] = '\0';	                                 //编码结束符号

	for (i = 1; i <= n; i++)
	{
		start = n - 1;
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)	//从叶子到根逆向求编码
		{
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		HC[i] = (char*) malloc ((n - start) * sizeof (char));
		strcpy(HC[i], &cd[start]);		//从 cd 赋值编码到 HC
	}
	free(cd);			//释放空间
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

	//printf("请输入权值的个数(>1) ：    ");
	//scanf("%d", &n);
	fscanf(fp, "%d", &n);

	w = (int*) malloc (n * sizeof(int));		//生成存放 n 个权值的空间
	printf("请依次输入 %d 个权值（整形）:\n", n);
	for (i = 0; i < n; i++)
		//scanf("%d", w + i);
		fscanf(fp, "%d", w + i);

	HuffmanCoding(HT, HC, w, n);				//根据w所存的 n 个权值构造赫夫曼树，n 个赫夫曼编码存于HC

	for (i = 1; i <= n; i++)
		puts(HC[i]);							//依次输出赫夫曼编码
}