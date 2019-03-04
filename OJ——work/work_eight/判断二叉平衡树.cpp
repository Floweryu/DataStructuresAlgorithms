#include <iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

typedef char TElemType;
int m;
typedef struct BinTreeNode
{
	TElemType data;		//结点的值
	BinTreeNode *lchild, *rchild;		//左右孩子指针
}BinTreeNode, *BinTree;


//按先序左右子树为空输入二叉树中的值
void PreCreateTree(BinTree &T, char *str)
{
    char ch;
    ch = str[m];
    m++;
	if (ch == '#')
		T = NULL;
	else
	{
		T = new BinTreeNode;
		if ( ! T)
			exit(0);

		T->data = ch;
		PreCreateTree(T->lchild, str);						//递归构造左子树
		PreCreateTree(T->rchild, str);						//递归构造右子树
	}
}

int Treedepth(BinTree &T)
{
    if (T == NULL)
        return 0;
    int left, right;
    left = Treedepth(T->lchild);
    right = Treedepth(T->rchild);

    if (left > right)
        return left + 1;
    else
        return right + 1;
}

bool isBalance(BinTree &T)
{
	int left, right;
	if (T == NULL)
		return true;

    left = Treedepth(T->lchild);
    right = Treedepth(T->rchild);
    if (abs(left - right) > 1)
        return false;
    else
        return isBalance(T->lchild) && isBalance(T->rchild);

}

int main()
{
    BinTree T;
    char str[2001];
    while(scanf("%s", str) != EOF)
    {
        m = 0;
        if (str[0] == '#')
            cout<<"Yes"<<endl;
        else
        {
            PreCreateTree(T, str);
            if (isBalance(T))
                cout<<"Yes"<<endl;
            else
                cout<<"No"<<endl;
        }
        memset(str, 0, sizeof(str));
    }
}
