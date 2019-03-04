/**
* Author : ZhangJunFeng
* Date : 2018-12-11-20.58.01
* Function: 二叉排序树
* Description :     注意在定义树根时要初始化，找到关键字返回 1， 否则返回0
* Algorithm description :   1，空树
                            2，左子树上所有节点均小于它的根节点的值。
                               右子树上所有节点均大于它的根节点的值。
                               左右子树也按以上规律。
* The test data :
*/
#include <iostream>
using namespace std;

typedef int KeyType;

typedef struct BinTreeNode
{
	KeyType data;		//结点的值
	BinTreeNode *lchild, *rchild;		//左右孩子指针
}BinTreeNode, *BinTree;

//判断两个数是否相等
bool EQ(KeyType a, KeyType b)
{
    if (a == b)
        return true;
    else
        return false;
}

//判断两个数小于关系
bool LT(KeyType a, KeyType b)
{
    if (a < b)
        return true;
    else
        return false;
}

//在二叉排序树中递归查找key元素
BinTree SearchBST_1(BinTree T, KeyType key)
{
    if (!T || EQ(key, T->data))             //树根为空或者key为树根节点
        return T;
    else if(LT(key, T->data))
        return (SearchBST_1(T->lchild, key));
    else
        return (SearchBST_1(T->rchild, key));
}

//
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

//删除节点p，并重新连接其左右子树
bool Delete(BinTree &p)
{
    BinTree q, s;

    if (!p->rchild)         //若右子树为空
    {
        q = p;
        p = p->lchild;
        delete q;
    }
    else if (!p->lchild)    //若左子树为空
    {
        q = p;
        p = p->rchild;
        delete q;
    }
    else                    //左右子树都不为空
    {
        q = p;
        s = p->lchild;
        while (s->rchild)
        {
            q = s;
            s = s->rchild;
        }

        p->data = s->data;      //删除节点，实际上是把要删除节点的值替换成适当的值

        if (q != p)
            q->rchild = s->lchild;
        else
            q->lchild = s->lchild;
        delete s;
    }
    return true;
}

//删除树中与key相同的元素
bool DeleteBST(BinTree &T, KeyType key)
{
    if (!T)
        return false;
    else
    {
        if (EQ(key, T->data))
            return Delete(T);
        else if (LT(key, T->data))
            return DeleteBST(T->lchild, key);
        else
            return DeleteBST(T->rchild, key);
    }
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
    BinTree root;
    root = NULL;
    int n, keys;
    cout<<"输入数据个数:    ";
    cin>>n;
    int i, j, flag;
    int back;

    cout<<"建立二叉排序树: "<<endl;
    for (i = 0; i < n; i++)
    {
        cin>>keys;
        back = InsertBSF(root, keys);
        if (back)
        {
            cout<<"中序遍历树为："<<endl;
            InOrder(root);
            cout<<endl;
        }
        else
        {
            cout<<"ERROR!!"<<endl;
        }
    }

    cout<<"输入关键字:   ";
    while (cin>>keys)
    {
        if (SearchBST_1(root, keys))
            cout<<"存在!!!"<<endl;
        else
            cout<<"不存在!!!"<<endl;

    }

}
