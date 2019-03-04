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
    return T;                   //���д������Ҫ��ȥ�������͸GG�ˡ�
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
            f[i][j] = f[i + 1][j] + f[i][i];        //Ĭ������������Ϊ�գ�����еĻ�����϶��������Ž�
            root[i][j] = i;                         //Ĭ�ϴ����ѡ��
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
