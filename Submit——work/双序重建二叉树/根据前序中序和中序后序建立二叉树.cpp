/**
* Author : ZhangFengng
* Date : 2018-11-22-18.52.03
* Function: 根据前序、中序||中序、后序遍历结果重建二叉树
* Description : 递归思想,版本0.0
*/
#include <iostream>
#include <stdlib.h>

using namespace std;
int count = 0;
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
}

//根据中序、后序遍历结果建立二叉树
BinTree MidPostCreateBinTree(TElemType *pos, TElemType *mid, int length)
{
    BinTree T;
    if (length == 0)
    {
        T = NULL;                     //这行代码很重要，去掉你就GG了。
        return T;
    }

    TElemType root;
    root = pos[length - 1];           //后序遍历结果数组的最后一个数据就是下一个子树的跟

    T = newcode(root);                //把根节点创建成树节点

    int i ,rootnum;

    for (i = 0; i < length; i++)      //寻找左子树的长度
    {
        if (mid[i] == root)
        {
            rootnum = i;
            break;
        }
    }

    T->lchild = MidPostCreateBinTree(pos, mid, rootnum);    //后序、中序首地址不变，返回左子树的长度

    T->rchild = MidPostCreateBinTree(pos + rootnum, mid + rootnum + 1, length - rootnum - 1);
                            //   后序首地址加上左子树长度，中序加上左子树长度再加一，因为要跳过根结点，返回右子树长度
}

//先序递归遍历
void PreOrder(BinTree &T)
{
	if (T == NULL)
		return;

	cout<<T->data<<" ";				    //先输出根值
	PreOrder(T->lchild);				//输出左孩子
	PreOrder(T->rchild);				//输出右孩子
}

//中序递归遍历
void InOrder(BinTree &T)
{
	if (T == NULL)
		return;

	InOrder(T->lchild);					//输出左孩子
	cout<<T->data<<" ";
	InOrder(T->rchild);					//输出右孩子
}

//后序递归遍历
void PostOrder(BinTree &T)
{
	if (T == NULL)
		return;

	PostOrder(T->lchild);				//输出左孩子
	PostOrder(T->rchild);				//输出右孩子
	cout<<T->data<<" ";
}

int main()
{
    cout<<"************************************************"<<endl;
    cout<<"*****    前序、中序重建,           'a'   *******"<<endl;
    cout<<"*****    中序、后序重建，          'b'   *******"<<endl;
    cout<<"*****    前序遍历                  'c'   *******"<<endl;
    cout<<"*****    中序遍历                  'd'   *******"<<endl;
    cout<<"*****    后序遍历                  'e'   *******"<<endl;
    cout<<"************************************************"<<endl;

    BinTree T;
    TElemType mid[255], pre[255], pos[255];
    int len, j;
    char str;

    do
    {
        cout<<"Please enter a char:      ";
        cin>>str;
        switch(str)
        {
        case 'a':
            {
                cout<<"请输入字符串长度：";
                cin>>len;
                cout<<"请输入前序遍历字符串:";
                for (j = 0; j < len; j++)
                    cin>>pre[j];
                cout<<"请输入中序遍历字符串:";
                for (j = 0; j < len; j++)
                    cin>>mid[j];
                T = PreMidCreateBinTree(pre, mid, len);
                break;
            }
        case 'b':
            {
                cout<<"请输入字符串长度：";
                cin>>len;
                cout<<"请输入后遍历字符串:";
                for (j = 0; j < len; j++)
                    cin>>pos[j];
                cout<<"请输入中序遍历字符串:";
                for (j = 0; j < len; j++)
                    cin>>mid[j];

                T = MidPostCreateBinTree(pos, mid, len);

                break;
            }
        case 'c':
            {
                cout<<"前序遍历结果：    ";
                PreOrder(T);
                cout<<endl;
                break;
            }
        case 'd':
            {
                cout<<"中序遍历结果：    ";
                InOrder(T);
                cout<<endl;
                break;
            }
        case 'e':
            {
                cout<<"后序遍历结果：    ";
                PostOrder(T);
                cout<<endl;
                break;
            }
        default:    cout<<"Wrong!!!\n";
        }
    }while(str != 'q');

}
