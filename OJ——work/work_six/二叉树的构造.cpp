#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef char TElemType;

typedef struct BinTreeNode
{
	TElemType data;		//����ֵ
	BinTreeNode *lchild, *rchild;		//���Һ���ָ��
}BinTreeNode, *BinTree;

typedef int Status;
typedef BinTree QElemType;

typedef struct QNode
{
	QElemType	data;
	QNode 		*next;
}*QueuePtr;

struct LinkQueue
{
	QueuePtr front,rear;		//��ͷ����βָ��
};

//��ʼ������һ���յĶ���
Status Init_Queue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr) malloc (sizeof(QNode));

	if( ! Q.front)				//�жϿռ��Ƿ�����ɹ�
		exit(OVERFLOW);

	Q.front->next = NULL;		//ͷ���� next ��Ϊ��

	return OK;
}

//�ж��������Ƿ�Ϊ��
Status Empty_Queue(LinkQueue &Q)
{
	if(Q.front->next == NULL)	//���ͷ���� next ��Ϊ��
		return TRUE;
	else
		return FALSE;
}

//����Ԫ�ص���β
Status Insert_Queue(LinkQueue &Q, QElemType e)
{
	QueuePtr p;								//���������½ڵ��ָ��

	p = (QueuePtr) malloc (sizeof(QNode));	//�����µĴ洢�ռ�
	if( ! p)								//�жϿռ��Ƿ�����ɹ�
		exit(OVERFLOW);

	p->data = e;							//��Ҫ�����ֵ���� p ָ��

	p->next = NULL;							//�½ڵ�ĺ��ָ���
	Q.rear->next = p;						//��βָ��ĺ��ָ���½ڵ�
	Q.rear = p;								//��βָ��ָ���½ڵ�

	return OK;
}

//ɾ����ͷԪ��
Status Delete_Queue(LinkQueue &Q, QElemType &e)
{
	QueuePtr p;					//����ָ��

	if (Q.front == Q.rear)
		return ERROR;

	p = Q.front->next;			// p ָ���һ�����
	e = p->data;				//��Ҫɾ��Ԫ�ظ��� e

	Q.front->next = p->next;	//ͷָ��ĺ��ָ�� p ����һ���ڵ�

	if (Q.rear == p)			//��ɾ�����Ƕ�β�ڵ�
		Q.rear = Q.front;		//��βָ��ָ��ͷ���

	free(p);					//�ͷ� p �ڵ�

	return OK;
}

//����������
Status Destroy_Queue(LinkQueue &Q)
{
	while(Q.front)				//Q.front��Ϊ��
	{
		Q.rear = Q.front->next;	//Q.rear ָ�� Q.front ����һ���ڵ�
		free(Q.front);			//�ͷ� Q.front
		Q.front = Q.rear;		// Q.front ָ�� Q.rear
	}
	return OK;
}

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

//����ݹ����
void PostOrder(BinTree &T)
{
	if (T == NULL)
		return;

	PostOrder(T->lchild);				//�������
	PostOrder(T->rchild);				//����Һ���
	printf("%c", T->data);
}

//����ݹ����
void LeveOrder(BinTree &T)
{
	LinkQueue Q;
	QElemType a;

	if (T == NULL)
		return;

	Init_Queue(Q);								//��ʼ������ q
	Insert_Queue(Q, T);							//��ָ�����

	while( ! Empty_Queue(Q))
	{
		Delete_Queue(Q, a);						//����
		printf("%c", a->data);

		if (a->lchild != NULL)					//�� a ������
			Insert_Queue(Q, a->lchild);			// a ���������

		if (a->rchild != NULL)					//�� a ���Һ���
			Insert_Queue(Q, a->rchild); 		// a ���Һ������
	}

	printf("\n");
	Destroy_Queue(Q);							//���ٶ��� q
}

int main()
{

    TElemType mid[2000], pre[2000];
    int len;
    while(scanf("%s %s", pre, mid) != EOF)
    {
        BinTree T;
        len = strlen(mid);
        T = PreMidCreateBinTree(pre, mid, len);
        PostOrder(T);
        printf(" ");
        LeveOrder(T);
    }
}
