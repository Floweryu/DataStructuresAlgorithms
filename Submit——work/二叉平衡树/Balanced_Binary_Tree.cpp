/**
* Author : ZhangJunFeng
* Date : 2018-12-13-16.23.16
* Function: ƽ�������
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

typedef struct BSTNode          //����ƽ�����洢�ṹ
{
    ElemType data;
    int bf;
    struct BSTNode *lchild, *rchild;
}BSTNode, *BSTree;


//�ж��������Ƿ����
bool EQ(KeyType a, KeyType b)
{
    if (a == b)
        return true;
    else
        return false;
}

//�ж�������С�ڹ�ϵ
bool LT(KeyType a, KeyType b)
{
    if (a < b)
        return true;
    else
        return false;
}

//�Զ�����������������
void R_Rotate(BSTree &p)
{
    BSTree lc;

    lc = p->lchild;
    p->lchild = lc->rchild;
    lc->rchild = p;
    p = lc;
}

//�Զ�����������������
void L_Rotate(BSTree &p)
{
    BSTree rc;

    rc = p->rchild;
    p->rchild = rc->lchild;
    rc->lchild = p;
    p = rc;
}

//��LR�ͣ�ֱ�ӽ���ƽ�⴦�����޸�ƽ������
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

//��RL�ͣ�ֱ��ƽ�⴦�����޸�ƽ������
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

//��ƽ����ת����
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

//��ƽ����ת����
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

//����һ��ƽ�����в����ڵĽڵ�
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

//�ڶ����������еݹ����keyԪ��
BinTree SearchBST_1(BinTree T, KeyType key)
{
    if (!T || EQ(key, T->data))             //����Ϊ�ջ���keyΪ�����ڵ�
        return T;
    else if(LT(key, T->data))
        return (SearchBST_1(T->lchild, key));
    else
        return (SearchBST_1(T->rchild, key));
}

//����ݹ����
void PreOrder(BinTree T)
{
	if (T == NULL)
		return;

	cout<<T->data<<" ";				//�������ֵ
	PreOrder(T->lchild);				//�������
	PreOrder(T->rchild);				//����Һ���
}

//����ݹ����
void InOrder(BinTree T)
{
	if (T == NULL)
		return;

	InOrder(T->lchild);					//�������
	cout<<T->data<<" ";
	InOrder(T->rchild);					//����Һ���
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

    cout<<"�������ݸ���:    ";
    cin>>n;
    cout<<"��������ֵ��"<<endl;
    for (i = 0; i < n; i++)
    {
        cin>>keys;
        back = InsertAVL(root, keys, flag);

        if (back)
        {
            cout<<"���������Ϊ��"<<endl;
            InOrder(root);
            cout<<endl;
        }
        else
        {
            cout<<"ERROR!!"<<endl;
        }
    }

    cout<<endl;
    cout<<"����ؼ��֣�   "<<endl;
    while(cin>>target)
    {
        cout<<endl;
        pback = SearchBST_1(root, target);
        if(pback)
        {
            cout<<"���ڹؼ���!!!"<<endl<<endl;;
            cout<<"ƽ�����ӣ�  "<<pback->bf<<endl;
            cout<<"�ؼ��֣�    "<<pback->data<<endl;
        }
        else
            cout<<"�����ڹؼ��֣���"<<endl;
        cout<<endl;
    }
}
