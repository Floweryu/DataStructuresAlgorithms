/**
* Author : ZhangJunFeng
* Date : 2018-12-13-16.23.16
* Function: 平衡二叉树
* Description :
* Algorithm description :
* The test data :
*/

#include <iostream>
using namespace std;

#define LH  +1
#define EH   0
#define RH  -1

#define BinTree BSTree

typedef int ElemType;
typedef int KeyType;

typedef struct BSTNode          //二叉平衡树存储结构
{
    ElemType data;
    int bf;
    struct BSTNode *lchild, *rchild;
}BSTNode, *BSTree;


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

//对二叉树进行右旋处理
void R_Rotate(BSTree &p)
{
    BSTree lc;

    lc = p->lchild;
    p->lchild = lc->rchild;
    lc->rchild = p;
    p = lc;
}

//对二叉树进行左旋处理
void L_Rotate(BSTree &p)
{
    BSTree rc;

    rc = p->rchild;
    p->rchild = rc->lchild;
    rc->lchild = p;
    p = rc;
}

//对LR型，直接进行平衡处理，不修改平衡因子
void LR_Rotate(BSTree &p)
{
    BSTree lc;

    lc = p->lchild;
    p->lchild = lc->rchild->rchild;
    lc->rchild->rchild = p;
    p = lc->rchild;
    lc->rchild = p->lchild;
    p->lchild = lc;
}

//对RL型，直接平衡处理，不修改平衡因子
void RL_Rotate(BSTree &p)
{
    BSTree rc;

    rc = p->rchild;
    p->rchild = rc->lchild->lchild;
    rc->lchild->lchild = p;
    p = rc->lchild;
    rc->lchild = p->rchild;
    p->rchild = rc;
}

//左平衡旋转处理
void LeftBalance(BSTree &T)
{
    BSTree lc, rd;

    lc = T->lchild;
    switch(lc->bf)
    {
        case LH:
            {
                T->bf = lc->bf = EH;
                R_Rotate(T);
                break;
            }
        case RH:
            {
                rd = lc->rchild;
                switch(rd->bf)
                {
                    case LH:
                        {
                            T->bf = RH;
                            lc->bf = EH;
                            break;
                        }
                    case EH:
                        {
                            T->bf = lc->bf = EH;
                            break;
                        }
                    case RH:
                        {
                            T->bf = EH;
                            lc->bf = LH;
                            break;
                        }
                }   //switch(rd->bf)
                rd->bf = EH;
                L_Rotate(T->lchild);
                R_Rotate(T);
            }
    }  //switch(lc->bf)
}

//右平衡旋转处理
void RightBalance(BSTree &T)
{
    BSTree rc, ld;
    rc = T->rchild;
    switch(rc->bf)
    {
        case RH:
            {
                T->bf = rc->bf = EH;
                L_Rotate(T);
                break;
            }
        case LH:
            {
                ld = rc->lchild;
                switch(ld->bf)
                {
                    case RH:
                        {
                            T->bf = LH;
                            rc->bf = EH;
                            break;
                        }
                    case EH:
                        {
                            T->bf = rc->bf = EH;
                            break;
                        }
                    case LH:
                        {
                            T->bf = EH;
                            rc->bf = RH;
                            break;
                        }
                }   // switch
                ld->bf = EH;
                R_Rotate(T->rchild);
                L_Rotate(T);
            }   // case(LH)
    }  //  switch(rc->bf)
}

//插入一个平衡树中不存在的节点
bool InsertAVL(BSTree &T, ElemType e, bool &taller)
{
    if (!T)
    {
        T = new BSTNode;
        T->data = e;
        T->lchild = T->rchild = NULL;
        T->bf = EH;
        taller = true;
    }
    else
    {
        if (EQ(e, T->data))
        {
            taller = false;
            return false;
        }
        if (LT(e, T->data))
        {
            if (!InsertAVL(T->lchild, e, taller))
                return false;
            if (taller)
            {
                switch (T->bf)
                {
                case LH:
                    {
                        LeftBalance(T);
                        taller = false;
                        break;
                    }
                case EH:
                    {
                        T->bf = LH;
                        taller = true;
                        break;
                    }
                case RH:
                    {
                        T->bf = EH;
                        taller = false;
                        break;
                    }
                }   // switch
            }
        }  // if
        else
        {
            if (!InsertAVL(T->rchild, e, taller))
                return false;
            if (taller)
            {
                switch(T->bf)
                {
                case LH:
                    {
                        T->bf = EH;
                        taller = false;
                        break;
                    }
                case EH:
                    {
                        T->bf = RH;
                        taller = true;
                        break;
                    }
                case RH:
                    {
                        RightBalance(T);
                        taller = false;
                        break;
                    }
                }   //switch
            }
        }  //else
    }   //else
    return true;
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

//先序递归遍历
void PreOrder(BinTree T)
{
	if (T == NULL)
		return;

	cout<<T->data<<" ";				//先输出根值
	PreOrder(T->lchild);				//输出左孩子
	PreOrder(T->rchild);				//输出右孩子
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
    BSTree root, pback;
    root = NULL;

    int i, j, back;
    int n, k;
    ElemType keys, target;
    bool flag;
    int goals[501];

    cout<<"输入数据个数:    ";
    cin>>n;
    cout<<"输入数据值："<<endl;
    for (i = 0; i < n; i++)
    {
        cin>>keys;
        back = InsertAVL(root, keys, flag);

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

    cout<<endl;
    cout<<"输入关键字：   "<<endl;
    while(cin>>target)
    {
        cout<<endl;
        pback = SearchBST_1(root, target);
        if(pback)
        {
            cout<<"存在关键字!!!"<<endl<<endl;;
            cout<<"平衡因子：  "<<pback->bf<<endl;
            cout<<"关键字：    "<<pback->data<<endl;
        }
        else
            cout<<"不存在关键字！！"<<endl;
        cout<<endl;
    }
}
