#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>

using namespace std;

const int MAXN = 50;

long long  n;
long long  f[MAXN][MAXN], root[MAXN][MAXN];
typedef int TElemType;

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
    return T;                   //这行代码更重要，去掉你就死透GG了。
}

void print(long long l, long long r)
{
    if (l > r)
        return;
    cout<<root[l][r]<<" ";
    if (l == r)
        return;
    print(l, root[l][r] - 1);

    print(root[l][r]+1,r);
}

int main()
{
    cin>>n;
    for (int i = 1; i <= n; i++)
    {
        cin>>f[i][i];
        f[i][i-1]=1;
        root[i][i] = i;
    }
    for (int len = 1; len < n; ++len)
    {
        for (int i = 1; i + len <= n; ++i)
        {
            int j = i + len;
            f[i][j] = f[i + 1][j] + f[i][i];        //默认它的左子树为空，如果有的话，这肯定不是最优解
            root[i][j] = i;                         //默认从起点选根
            for (int k = i + 1; k < j; ++k)
            {
                if (f[i][j] < f[i][k - 1] * f[k + 1][j] + f[k][k])
                {
                    f[i][j] = f[i][k - 1] * f[k + 1][j] + f[k][k];
                    root[i][j] = k;
                }
            }
        }
    }
    cout << f[1][n] << endl;
    print(1, n);
    return 0;
}
