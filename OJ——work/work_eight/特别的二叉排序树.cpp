#include <iostream>
#include <algorithm>

using namespace std;

typedef int KeyType;

typedef struct BinTreeNode
{
	KeyType data;		//结点的值
	BinTreeNode *lchild, *rchild;		//左右孩子指针
}BinTreeNode, *BinTree;



bool EQ(KeyType a, KeyType b)
{
    if (a == b)
        return true;
    else
        return false;
}


bool LT(KeyType a, KeyType b)
{
    if (a > b)
        return true;
    else
        return false;
}


bool SearchBST_2(BinTree T, KeyType key, BinTree f, BinTree &p)
{
    if (!T)
    {
        p = f;
        return false;
    }
    else if (EQ(key, T->data))
    {
        p = T;
        return true;
    }
    else if (LT(key, T->data))
        return SearchBST_2(T->lchild, key, T, p);
    else
        return SearchBST_2(T->rchild, key, T, p);
}

//当排序树中不存在e元素，插入e
bool InsertBSF(BinTree &T, KeyType e)
{
    BinTree p, s;
    if (!SearchBST_2(T, e, NULL, p))
    {
        s = new BinTreeNode;
        s->data = e;
        s->lchild = s->rchild = NULL;

        if (!p)
            T = s;
        else if (LT(e, p->data))
            p->lchild = s;
        else
            p->rchild = s;
        return true;
    }
    else
        return false;
}

int Treedepth(BinTree &T)
{
    if (T == NULL)
        return 0;
    int left, right;
    left = Treedepth(T->lchild);
    right = Treedepth(T->rchild);

    if (left >= right)
        return left + 1;
    else
        return right + 1;
}


//中序递归遍历
void InOrder(BinTree T)
{
	if (T == NULL)
		return;

	InOrder(T->lchild);					//输出左孩子
	cout<<T->data<<" ";
	InOrder(T->rchild);					//输出右孩子
}


int main()
{
    int dat[101];
    int weight[101];
    int m, temp1, temp2;
    cin>>m;
    while(m--)
    {
        int depth;
        BinTree root;
        root = NULL;
        int n;
        cin>>n;
        int i, j;
        for (i = 0; i < n; i++)
            cin>>dat[i];
        for (j = 0; j < n; j++)
            cin>>weight[j];
        for (i = 0; i < n - 1; i++)
        {
            for (j = 0; j < n - i - 1; j++)
            {
                if (weight[j] > weight[j+1])
                {
                    temp1 = weight[j];
                    weight[j] = weight[j+1];
                    weight[j+1] = temp1;
                    temp2 = dat[j];
                    dat[j] = dat[j+1];
                    dat[j+1] = temp2;
                }
            }
        }
        for (i = 0; i < n; i++)
        {
            InsertBSF(root, dat[i]);
           // InOrder(root);
            //cout<<endl;
        }
        depth = Treedepth(root);
        cout<<depth<<endl;
    }
}

