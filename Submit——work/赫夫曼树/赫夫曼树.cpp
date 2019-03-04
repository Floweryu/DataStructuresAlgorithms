/*
	Name: 赫夫曼编码 
	Author: 张俊峰 
	Date: 17/11/18 19:10
	Description: 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	unsigned int weight;		//结点的权值 
	unsigned int parent, lchild, rchild;	
}HTNode, * HuffmanTree;

typedef char * *HuffmanCode;

#define Order
//返回赫夫曼树的前 i 个结点中权值最小的树的根结序号
int min(HuffmanTree t, int i)
{
	int j, m;
	unsigned int k = UINT_MAX;
	for (j = 1; j <= i; j++)			//对于前 i 个节点 
	{
		if (t[j].weight < k && t[j].parent == 0)		//t[j]的权值小于 k,又是树 的根节点 
		{
			k = t[j].weight;		//t[j] 的权值赋给 k  
			m = j;					//序号赋给 m 
		}
	} 
	t[m].parent = 1;			//给选中的根结点的双亲赋非零值，避免第二次查找
	return m; 
}

//在赫夫曼树的前 i 个节点中选择两个权值最小的树的根节点序号
void select(HuffmanTree t, int i, int &s1, int &s2)
{
	#ifdef Order			//如果在主程中定义了Order ，则以下语句起作用
		int j;
	#endif
		s1 = min(t, i);
		s2 = min(t, i);
	#ifdef Order
		if (s1 > s2)
		{
			j = s1;
			s1 = s2;		//s1 是权值最小的两个中序号较小的 
			s2 = j;			//s2 是权值最小的两个中序号较大的 
		}
	#endif 
} 

//构造赫夫曼树
void HuffmanCoding(HuffmanTree &HT, HuffmanTree &HC, int *w, int n)
{
	int start;
	unsigned f;
	
	int m, i, s1, s2;
	unsigned c;
	HuffmanTree p;
	char *cd;
	
	if (n <= 1)			//叶子节点数不大于 1  
		return;
	
	m = 2 * n - 1;		//n 个叶子结点的赫夫曼树共有 m 个结点 
	HT = (HuffmanTree) malloc ((m + 1) * sizeof(HTNode));		// 0 号单元没有用 
	for (p = HT + 1, i = 1; i <= n; i++, p++, w++)			//从一号单元开始到 n 号单元，给叶子结点赋值 
	{	// p 的初值指向一号单元 
		(*p).weight = *w;		//赋权值		
		(*p).parent = 0;		//双亲域为空 
		(*p).lchild = 0;		//左右孩子为空 
		(*p).rchild = 0;
	}
	for (; i <= m; i++, p++)	// i 从 n + 1到 m 
		(*p).parent = 0;		//其余结点的双亲域初值为 0 
		
	for (i = n + 1; i <= m; i++)	//建赫夫曼树 
	{			
		select(HT, i - 1, s1, s2);	//选择最小的两个节点 
		HT[s1].parent = HT[s2].parent = i;	// i 号单元是 s1 s2 的双亲 
		HT[i].lchild = s1;					// i 号单元的左右孩子分别是 s1 和 s2 
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;	// i 号单元的权值是 s1 和 s2 的权值之和 
	}
	
	HC = (HuffmanTree) malloc ((n + 1) * sizeof(char*));
	//分配 n 个字符编码的头指针向量
	cd = (char*) malloc (n * sizeof(char));	
	cd[n - 1] = '\0';	//编码结束符号
	
	for (i = 1; i <= n; i++)		//逐个字符求赫夫曼编码 
	{
		start = n - 1;				//编码借宿位置 
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)	//从叶子到根逆向求编码 
		{
			if (HT[f].lchild == c)		//c 是其双亲的左孩子 
				cd[--start] = '0';		//由叶子向根赋值 ' 0 ' 
			else 						// c 是其双亲的右孩子 
				cd[--start] = '1';		//由叶子向根赋值‘1’ 
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
	printf("请输入权值的个数(>1) ：    ");
	scanf("%d", &n);
	w = (int*) malloc (n * sizeof(int));		//生成存放 n 个权值的空间
	printf("请依次输入 %d 个权值（整形）:\n", n);
	for (i = 0; i < n; i++)
		scanf("%d", w + i);
		
	HuffmanCoding(HT, HC, w, n);				//根据w所存的 n 个权值构造赫夫曼树，n 个赫夫曼编码存于HC 
		
	for (i = 1; i <= n; i++)
		puts(HC[i]);							//依次输出赫夫曼编码 
} 

