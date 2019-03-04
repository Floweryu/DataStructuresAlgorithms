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

//����������������е�ֵ
void PreCreateBinTree(BinTree &T)
{
	TElemType ch;

	scanf("%c", &ch);									//����ֵ

	if (ch == ' ')
		T = NULL;
	else
	{
		T = (BinTree)malloc(sizeof(BinTreeNode));
		if ( ! T)
			exit(0);

		T->data = ch;									//��ֵ���� T ���
		PreCreateBinTree(T->lchild);						//�ݹ鹹��������
		PreCreateBinTree(T->rchild);						//�ݹ鹹��������
	}
}

//����ݹ����
void InOrder(BinTree T)
{
	if (T == NULL)
		return;

	InOrder(T->lchild);					//�������
	printf("%c ", T->data);
	InOrder(T->rchild);					//����Һ���
}

int main()
{
    BinTree T;
    PreCreateBinTree(T);
    InOrder(T);
}
