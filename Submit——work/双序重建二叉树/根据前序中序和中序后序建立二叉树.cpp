/**
* Author : ZhangFengng
* Date : 2018-11-22-18.52.03
* Function: ����ǰ������||���򡢺����������ؽ�������
* Description : �ݹ�˼��,�汾0.0
*/
#include <iostream>
#include <stdlib.h>

using namespace std;
int count = 0;
typedef char TElemType;

typedef struct BinTreeNode
{
	TElemType data;		                //����ֵ
	BinTreeNode *lchild, *rchild;		//���Һ���ָ��
}BinTreeNode, *BinTree;

//�����µĽڵ�
BinTree newcode(TElemType c)							//�����ݲ��뵽�ڵ���
{
	BinTree t = (BinTree)malloc(sizeof(BinTreeNode));
	t->data = c;
	t->lchild = NULL;
	t->rchild = NULL;
	return t;											//���ش������ݵĽ��
}

//����ǰ����������������������
BinTree PreMidCreateBinTree(TElemType *pre, TElemType *mid, int length)
{
    BinTree T;
    if (length == 0)
    {
        T = NULL;                   //���д������Ҫ��ȥ�����GG�ˡ�
        return T;
    }

    TElemType root;
    root = pre[0];                  //ÿ�εݹ������ǰ��ĵ�һ�����ݾ�����һ���������ĸ�
    T = newcode(root);              //�Ѹ�Ԫ�ش����ɽڵ�

    int i;                          //���������ĳ���
    for (i = 0; i < length; i++)
    {
        if (mid[i] == root)         //�ҵ����ڵ�����������е�λ��
            break;                  //�ҵ�λ�ú�����ѭ��
    }


    T->lchild = PreMidCreateBinTree(pre + 1, mid, i);       //�ݹ鴴����������ǰ�������׵�ַ�����һλ��lengthֵ�������������

    T->rchild = PreMidCreateBinTree(pre + i + 1, mid + i + 1, length - i - 1);
                                //  ǰ�������׵�ַ������������׵�ַ�����������ĳ��ȣ�lengthֵ����������ĳ���
}

//�������򡢺�������������������
BinTree MidPostCreateBinTree(TElemType *pos, TElemType *mid, int length)
{
    BinTree T;
    if (length == 0)
    {
        T = NULL;                     //���д������Ҫ��ȥ�����GG�ˡ�
        return T;
    }

    TElemType root;
    root = pos[length - 1];           //������������������һ�����ݾ�����һ�������ĸ�

    T = newcode(root);                //�Ѹ��ڵ㴴�������ڵ�

    int i ,rootnum;

    for (i = 0; i < length; i++)      //Ѱ���������ĳ���
    {
        if (mid[i] == root)
        {
            rootnum = i;
            break;
        }
    }

    T->lchild = MidPostCreateBinTree(pos, mid, rootnum);    //���������׵�ַ���䣬�����������ĳ���

    T->rchild = MidPostCreateBinTree(pos + rootnum, mid + rootnum + 1, length - rootnum - 1);
                            //   �����׵�ַ�������������ȣ�������������������ټ�һ����ΪҪ��������㣬��������������
}

//����ݹ����
void PreOrder(BinTree &T)
{
	if (T == NULL)
		return;

	cout<<T->data<<" ";				    //�������ֵ
	PreOrder(T->lchild);				//�������
	PreOrder(T->rchild);				//����Һ���
}

//����ݹ����
void InOrder(BinTree &T)
{
	if (T == NULL)
		return;

	InOrder(T->lchild);					//�������
	cout<<T->data<<" ";
	InOrder(T->rchild);					//����Һ���
}

//����ݹ����
void PostOrder(BinTree &T)
{
	if (T == NULL)
		return;

	PostOrder(T->lchild);				//�������
	PostOrder(T->rchild);				//����Һ���
	cout<<T->data<<" ";
}

int main()
{
    cout<<"************************************************"<<endl;
    cout<<"*****    ǰ�������ؽ�,           'a'   *******"<<endl;
    cout<<"*****    ���򡢺����ؽ���          'b'   *******"<<endl;
    cout<<"*****    ǰ�����                  'c'   *******"<<endl;
    cout<<"*****    �������                  'd'   *******"<<endl;
    cout<<"*****    �������                  'e'   *******"<<endl;
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
                cout<<"�������ַ������ȣ�";
                cin>>len;
                cout<<"������ǰ������ַ���:";
                for (j = 0; j < len; j++)
                    cin>>pre[j];
                cout<<"��������������ַ���:";
                for (j = 0; j < len; j++)
                    cin>>mid[j];
                T = PreMidCreateBinTree(pre, mid, len);
                break;
            }
        case 'b':
            {
                cout<<"�������ַ������ȣ�";
                cin>>len;
                cout<<"�����������ַ���:";
                for (j = 0; j < len; j++)
                    cin>>pos[j];
                cout<<"��������������ַ���:";
                for (j = 0; j < len; j++)
                    cin>>mid[j];

                T = MidPostCreateBinTree(pos, mid, len);

                break;
            }
        case 'c':
            {
                cout<<"ǰ����������    ";
                PreOrder(T);
                cout<<endl;
                break;
            }
        case 'd':
            {
                cout<<"������������    ";
                InOrder(T);
                cout<<endl;
                break;
            }
        case 'e':
            {
                cout<<"������������    ";
                PostOrder(T);
                cout<<endl;
                break;
            }
        default:    cout<<"Wrong!!!\n";
        }
    }while(str != 'q');

}
