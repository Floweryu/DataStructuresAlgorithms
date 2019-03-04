#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char ElemType;

// �����������ṹ��
typedef struct HuffmanTree
{
	ElemType data;
    int  weight;
    int  id;                  // id������Ҫ��������Ȩֵ��ͬ�Ľ�㣬����������±�
    struct HuffmanTree* lchild;
    struct HuffmanTree* rchild;
}HuffmanNode,* Huffman;

// ������������
HuffmanNode* createHuffmanTree(ElemType *str,int *a, int n)
{
    int i;
    int j;
    Huffman *temp;
	Huffman hufmTree;
    //HuffmanNode **temp, *hufmTree;
    temp = (Huffman *) malloc(n * sizeof(HuffmanNode));
    for (i = 0; i < n; ++i)     // ������a�е�Ȩֵ��������е�weight
    {
        temp[i] = (Huffman)malloc(sizeof(HuffmanNode));
        temp[i]->data = str[i];
		temp[i]->weight = a[i];
        temp[i]->id = i;
        temp[i]->lchild = temp[i]->rchild = NULL;
    }

    for (i = 0; i< n-1; ++i)       // ��������������Ҫn-1�ϲ�
    {
        int small1 = -1;          // small1��small2�ֱ���Ϊ��С�ʹ�СȨֵ���±�
        int small2;
		for (j = 0; j < n; ++j)         // �Ƚ���С�������±긳��small1��small2��ע�⣺��ӦȨֵδ����С��
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
        for (j = small2; j < n; ++j)    // �Ƚ�Ȩֵ��Ų��small1��small2ʹ֮�ֱ��Ϊ��С�ʹ�СȨֵ���±�
        {
            if (temp[j] != NULL)
            {
                if (temp[j]->weight < temp[small1]->weight)   //����СȨֵ�Ƚ�
                {
                    small2 = small1;
                    small1 = j;
                }
				else if (temp[j]->weight < temp[small2]->weight)  //���СȨֵ�Ƚ�
                {
                    small2 = j;
                }
            }
        }
        hufmTree = (Huffman)malloc(sizeof(HuffmanNode));
        hufmTree->weight = temp[small1]->weight + temp[small2]->weight;  //�ϲ�
        hufmTree->lchild = temp[small1];
        hufmTree->rchild = temp[small2];

        temp[small1] = hufmTree;
        temp[small2] = NULL;
    }
    free(temp);      //ɾ����ǰ��ָ��
    return hufmTree;
}

// �ݹ���й���������
void HuffmanCode(Huffman hufmTree, int depth)      // depth�ǹ������������
{
    static int code[10];
    int i;
    if (hufmTree)
    {
        if (hufmTree->lchild==NULL && hufmTree->rchild==NULL)    //Ҷ�ڵ�
        {
            printf("idΪ%d������ַ�%c,��ȨֵΪ%d��Ҷ�ӽ��Ĺ���������Ϊ ", hufmTree->id, hufmTree->data,  hufmTree->weight);
            for (i = 0; i < depth; ++i)
            {
                printf("%d", code[i]);   //����
            }
            printf("\n");
        }
		else  //��Ϊ0����Ϊ1
        {
            code[depth] = 0;
            HuffmanCode(hufmTree->lchild, depth+1);
            code[depth] = 1;
            HuffmanCode(hufmTree->rchild, depth+1);
        }
    }
}

// ����������
void HuffmanDecode(char ch[], HuffmanNode* hufmTree, char string[])     // ch��Ҫ�����01����string�ǽ���Ӧ���ַ�
{
    int i;
    int num[100];
    Huffman tempTree = NULL;
    for (i = 0; i < strlen(ch); i++) //����Ҫ����ı������num������
    {
        if (ch[i] == '0')
            num[i] = 0;
        else
            num[i] = 1;
    }
    if(hufmTree)
    {
        i = 0;        // �����ѽ���01���ĳ���
        while(i < strlen(ch))
        {
            tempTree = hufmTree;
            while(tempTree->lchild != NULL && tempTree->rchild != NULL)  //����Ϊ��
            {
                if (num[i] == 0)       //����Ϊ0ʱ������ǰ��������
                {
                    tempTree = tempTree->lchild;
                }
				else					//����Ϊ1ʱ������ǰ�����Һ���
                {
                    tempTree = tempTree->rchild;
                }
                i++;
            }
            printf("%c", string[tempTree->id]);      // ���������Ӧ�����ַ�
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
            printf("�����������������nֵ��");
    }
    for (i = 0 ;i < n; i++)    //�����ַ�
    {
    	fscanf(f,"%c",&str[i]);
	}

    for (i = 0; i < n; i++)		//����ȡȨֵ
    {
		flag = 0;
    	for (j = 0; j < n; j++)
    	{
    		if (str[i] == str[j])
    			flag++;
		}
		arr[i] = flag;
		printf("\n%c��ȨֵΪ%d\n ",str[i],arr[i]);
	}

    hufmTree = createHuffmanTree(str,arr, n);     //����HuffmanTree��

    printf("\n��Ҷ�ӽ��Ĺ���������Ϊ:\n");
    HuffmanCode(hufmTree, 0);

    printf("��������Ҫ����ı���:\n");
    gets(ch);
    printf("������Ϊ��\n");
    HuffmanDecode(ch, hufmTree, str);
    printf("\n");

    free(hufmTree);

    return 0;
}

