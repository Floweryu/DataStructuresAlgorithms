#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char ElemType;

// 哈夫曼树结点结构体
typedef struct HuffmanTree
{
	ElemType data;
    int  weight;
    int  id;                  // id用来主要用以区分权值相同的结点，这里代表了下标
    struct HuffmanTree* lchild;
    struct HuffmanTree* rchild;
}HuffmanNode,* Huffman;

// 构建哈夫曼树
HuffmanNode* createHuffmanTree(ElemType *str,int *a, int n)
{
    int i;
    int j;
    Huffman *temp;
	Huffman hufmTree;
    //HuffmanNode **temp, *hufmTree;
    temp = (Huffman *) malloc(n * sizeof(HuffmanNode));
    for (i = 0; i < n; ++i)     // 将数组a中的权值赋给结点中的weight
    {
        temp[i] = (Huffman)malloc(sizeof(HuffmanNode));
        temp[i]->data = str[i];
		temp[i]->weight = a[i];
        temp[i]->id = i;
        temp[i]->lchild = temp[i]->rchild = NULL;
    }

    for (i = 0; i< n-1; ++i)       // 构建哈夫曼树需要n-1合并
    {
        int small1 = -1;          // small1、small2分别作为最小和次小权值的下标
        int small2;
		for (j = 0; j < n; ++j)         // 先将最小的两个下标赋给small1、small2（注意：对应权值未必最小）
        {
            if (temp[j] != NULL && small1== -1)
            {
                small1 = j;
                continue;
            }
			else if(temp[j] != NULL)
            {
                small2 = j;
                break;
            }
        }
        for (j = small2; j < n; ++j)    // 比较权值，挪动small1和small2使之分别成为最小和次小权值的下标
        {
            if (temp[j] != NULL)
            {
                if (temp[j]->weight < temp[small1]->weight)   //与最小权值比较
                {
                    small2 = small1;
                    small1 = j;
                }
				else if (temp[j]->weight < temp[small2]->weight)  //与次小权值比较
                {
                    small2 = j;
                }
            }
        }
        hufmTree = (Huffman)malloc(sizeof(HuffmanNode));
        hufmTree->weight = temp[small1]->weight + temp[small2]->weight;  //合并
        hufmTree->lchild = temp[small1];
        hufmTree->rchild = temp[small2];

        temp[small1] = hufmTree;
        temp[small2] = NULL;
    }
    free(temp);      //删除当前树指针
    return hufmTree;
}

// 递归进行哈夫曼编码
void HuffmanCode(Huffman hufmTree, int depth)      // depth是哈夫曼树的深度
{
    static int code[10];
    int i;
    if (hufmTree)
    {
        if (hufmTree->lchild==NULL && hufmTree->rchild==NULL)    //叶节点
        {
            printf("id为%d代表的字符%c,其权值为%d的叶子结点的哈夫曼编码为 ", hufmTree->id, hufmTree->data,  hufmTree->weight);
            for (i = 0; i < depth; ++i)
            {
                printf("%d", code[i]);   //编码
            }
            printf("\n");
        }
		else  //左为0，右为1
        {
            code[depth] = 0;
            HuffmanCode(hufmTree->lchild, depth+1);
            code[depth] = 1;
            HuffmanCode(hufmTree->rchild, depth+1);
        }
    }
}

// 哈夫曼解码
void HuffmanDecode(char ch[], HuffmanNode* hufmTree, char string[])     // ch是要解码的01串，string是结点对应的字符
{
    int i;
    int num[100];
    Huffman tempTree = NULL;
    for (i = 0; i < strlen(ch); i++) //把需要解码的编码放在num数组里
    {
        if (ch[i] == '0')
            num[i] = 0;
        else
            num[i] = 1;
    }
    if(hufmTree)
    {
        i = 0;        // 计数已解码01串的长度
        while(i < strlen(ch))
        {
            tempTree = hufmTree;
            while(tempTree->lchild != NULL && tempTree->rchild != NULL)  //数不为空
            {
                if (num[i] == 0)       //编码为0时，代表当前结点的左孩子
                {
                    tempTree = tempTree->lchild;
                }
				else					//编码为1时，代表当前结点的右孩子
                {
                    tempTree = tempTree->rchild;
                }
                i++;
            }
            printf("%c", string[tempTree->id]);      // 输出解码后对应结点的字符
        }
    }
}

int main()
{
	Huffman hufmTree = NULL;
    int i;
    int j;
    int n;
    int flag;
    int arr[100];
    char str[100];
    char ch[100];
	char string[100];
	FILE *f;

	f = fopen("zipdata.txt","r");

    while(1)
    {
        fscanf(f,"%d",&n);
        if (n > 1)
            break;
        else
            printf("输入错误，请重新输入n值！");
    }
    for (i = 0 ;i < n; i++)    //读入字符
    {
    	fscanf(f,"%c",&str[i]);
	}

    for (i = 0; i < n; i++)		//遍历取权值
    {
		flag = 0;
    	for (j = 0; j < n; j++)
    	{
    		if (str[i] == str[j])
    			flag++;
		}
		arr[i] = flag;
		printf("\n%c的权值为%d\n ",str[i],arr[i]);
	}

    hufmTree = createHuffmanTree(str,arr, n);     //创建HuffmanTree树

    printf("\n各叶子结点的哈夫曼编码为:\n");
    HuffmanCode(hufmTree, 0);

    printf("请输入需要解码的编码:\n");
    gets(ch);
    printf("解码结果为：\n");
    HuffmanDecode(ch, hufmTree, str);
    printf("\n");

    free(hufmTree);

    return 0;
}

