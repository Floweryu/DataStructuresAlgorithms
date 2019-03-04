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

//分配新的节点
BinTree newcode(TElemType c)							//把数据插入到节点中
{
	BinTree t = (BinTree)malloc(sizeof(BinTreeNode));
	t->data = c;
	t->lchild = NULL;
	t->rchild = NULL;
	return t;											//返回带该数据的结点
}

//根据前序、中序遍历结果建立二叉树
BinTree PreMidCreateBinTree(TElemType *pre, TElemType *mid, int length)
{
    BinTree T;
    if (length == 0)
    {
        T = NULL;                   //这行代码很重要，去掉你就GG了。
        return T;
    }

    TElemType root;
    root = pre[0];                  //每次递归回来的前序的第一个数据就是下一个二叉树的根
    T = newcode(root);              //把根元素创建成节点

    int i;                          //求左子树的长度
    for (i = 0; i < length; i++)
    {
        if (mid[i] == root)         //找到根节点在中序遍历中的位置
            break;                  //找到位置后跳出循环
    }


    T->lchild = PreMidCreateBinTree(pre + 1, mid, i);       //递归创建左子树，前序数组首地址向后移一位，length值变成左子树长度

    T->rchild = PreMidCreateBinTree(pre + i + 1, mid + i + 1, length - i - 1);
                                //  前序数组首地址、中序数组的首地址加上左子树的长度，length值变成右子树的长度
    return T;
}

//后序递归遍历
void PostOrder(BinTree &T)
{
	if (T == NULL)
		return;

	PostOrder(T->lchild);				//输出左孩子
	PostOrder(T->rchild);				//输出右孩子
	printf("%c", T->data);
}

//销毁树
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
