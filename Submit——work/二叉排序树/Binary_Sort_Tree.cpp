/**
* Author : ZhangJunFeng
* Date : 2018-12-11-20.58.01
* Function: ����������
* Description :     ע���ڶ�������ʱҪ��ʼ�����ҵ��ؼ��ַ��� 1�� ���򷵻�0
* Algorithm description :   1������
                            2�������������нڵ��С�����ĸ��ڵ��ֵ��
                               �����������нڵ���������ĸ��ڵ��ֵ��
                               ��������Ҳ�����Ϲ��ɡ�
* The test data :
*/
#include <iostream>
using namespace std;

typedef int KeyType;

typedef struct BinTreeNode
{
	KeyType data;		//����ֵ
	BinTreeNode *lchild, *rchild;		//���Һ���ָ��
}BinTreeNode, *BinTree;

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

//���������в�����eԪ�أ�����e
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

//ɾ���ڵ�p����������������������
bool Delete(BinTree &p)
{
    BinTree q, s;

    if (!p->rchild)         //��������Ϊ��
    {
        q = p;
        p = p->lchild;
        delete q;
    }
    else if (!p->lchild)    //��������Ϊ��
    {
        q = p;
        p = p->rchild;
        delete q;
    }
    else                    //������������Ϊ��
    {
        q = p;
        s = p->lchild;
        while (s->rchild)
        {
            q = s;
            s = s->rchild;
        }

        p->data = s->data;      //ɾ���ڵ㣬ʵ�����ǰ�Ҫɾ���ڵ��ֵ�滻���ʵ���ֵ

        if (q != p)
            q->rchild = s->lchild;
        else
            q->lchild = s->lchild;
        delete s;
    }
    return true;
}

//ɾ��������key��ͬ��Ԫ��
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
    BinTree root;
    root = NULL;
    int n, keys;
    cout<<"�������ݸ���:    ";
    cin>>n;
    int i, j, flag;
    int back;

    cout<<"��������������: "<<endl;
    for (i = 0; i < n; i++)
    {
        cin>>keys;
        back = InsertBSF(root, keys);
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

    cout<<"����ؼ���:   ";
    while (cin>>keys)
    {
        if (SearchBST_1(root, keys))
            cout<<"����!!!"<<endl;
        else
            cout<<"������!!!"<<endl;

    }

}
