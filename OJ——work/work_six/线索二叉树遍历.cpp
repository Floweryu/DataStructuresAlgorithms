#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;

typedef char TElemType;

typedef struct BinTreeNode
{
	TElemType data;		                //结点的值
	BinTreeNode *lchild, *rchild;		//左右孩子指针
}BinTreeNode, *BinTree;

//按先序输入二叉树中的值
void PreCreateBinTree(BinTree &T)
{
	TElemType ch;

	scanf("%c", &ch);									//输入值

	if (ch == ' ')
		T = NULL;
	else
	{
		T = (BinTree)malloc(sizeof(BinTreeNode));
		if ( ! T)
			exit(0);

		T->data = ch;									//将值赋给 T 结点
		PreCreateBinTree(T->lchild);						//递归构造左子树
		PreCreateBinTree(T->rchild);						//递归构造右子树
	}
}

//中序递归遍历
void InOrder(BinTree T)
{
	if (T == NULL)
		return;

	InOrder(T->lchild);					//输出左孩子
	printf("%c ", T->data);
	InOrder(T->rchild);					//输出右孩子
}

int main()
{
    BinTree T;
    PreCreateBinTree(T);
    InOrder(T);
}
