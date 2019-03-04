#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;

typedef char TElemType;

typedef struct BinTreeNode
{
	TElemType data;		                //����ֵ
	BinTreeNode *lchild, *rchild;		//���Һ���ָ��
}BinTreeNode, *BinTree;

//�����µĽڵ�
BinTree newcode(TElemType c)							//�����ݲ��뵽�ڵ���
{
	BinTree t = (BinTree)malloc(sizeof(BinTreeNode));
	t->data = c;
	t->lchild = NULL;
	t->rchild = NULL;
	return t;											//���ش������ݵĽ��
}

//����ǰ����������������������
BinTree PreMidCreateBinTree(TElemType *pre, TElemType *mid, int length)
{
    BinTree T;
    if (length == 0)
    {
        T = NULL;                   //���д������Ҫ��ȥ�����GG�ˡ�
        return T;
    }

    TElemType root;
    root = pre[0];                  //ÿ�εݹ������ǰ��ĵ�һ�����ݾ�����һ���������ĸ�
    T = newcode(root);              //�Ѹ�Ԫ�ش����ɽڵ�

    int i;                          //���������ĳ���
    for (i = 0; i < length; i++)
    {
        if (mid[i] == root)         //�ҵ����ڵ�����������е�λ��
            break;                  //�ҵ�λ�ú�����ѭ��
    }


    T->lchild = PreMidCreateBinTree(pre + 1, mid, i);       //�ݹ鴴����������ǰ�������׵�ַ�����һλ��lengthֵ�������������

    T->rchild = PreMidCreateBinTree(pre + i + 1, mid + i + 1, length - i - 1);
                                //  ǰ�������׵�ַ������������׵�ַ�����������ĳ��ȣ�lengthֵ����������ĳ���
    return T;
}

//����ݹ����
void PostOrder(BinTree &T)
{
	if (T == NULL)
		return;

	PostOrder(T->lchild);				//�������
	PostOrder(T->rchild);				//����Һ���
	printf("%c", T->data);
}

//������
void DestroyBinTree(BinTree &T)
{
    if (T)
    {
        DestroyBinTree(T->lchild);
        DestroyBinTree(T->rchild);
        free(T);
        T = NULL;
    }
}

int main()
{
    int n, len;
    cin>>n;
    while(n--)
    {
        char mid[2000], pre[2000];
        BinTree T;

        cin>>pre;
        cin>>mid;
        len = strlen(pre);
        T = PreMidCreateBinTree(pre, mid, len);
        PostOrder(T);
        cout<<endl;
        DestroyBinTree(T);
    }
    return 0;
}
