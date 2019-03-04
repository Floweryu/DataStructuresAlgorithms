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
	TElemType data;		//结点的值
	BinTreeNode *lchild, *rchild;		//左右孩子指针
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
	QueuePtr front,rear;		//队头，队尾指针
};

//初始化定义一个空的队列
Status Init_Queue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr) malloc (sizeof(QNode));

	if( ! Q.front)				//判断空间是否申请成功
		exit(OVERFLOW);

	Q.front->next = NULL;		//头结点的 next 域为空

	return OK;
}

//判断链队列是否为空
Status Empty_Queue(LinkQueue &Q)
{
	if(Q.front->next == NULL)	//如果头结点的 next 域为空
		return TRUE;
	else
		return FALSE;
}

//插入元素到队尾
Status Insert_Queue(LinkQueue &Q, QElemType e)
{
	QueuePtr p;								//定义申请新节点的指针

	p = (QueuePtr) malloc (sizeof(QNode));	//申请新的存储空间
	if( ! p)								//判断空间是否申请成功
		exit(OVERFLOW);

	p->data = e;							//将要插入的值赋给 p 指针

	p->next = NULL;							//新节点的后继指向空
	Q.rear->next = p;						//队尾指针的后继指向新节点
	Q.rear = p;								//队尾指针指向新节点

	return OK;
}

//删除队头元素
Status Delete_Queue(LinkQueue &Q, QElemType &e)
{
	QueuePtr p;					//定义指针

	if (Q.front == Q.rear)
		return ERROR;

	p = Q.front->next;			// p 指向第一个结点
	e = p->data;				//将要删除元素赋给 e

	Q.front->next = p->next;	//头指针的后继指向 p 的下一个节点

	if (Q.rear == p)			//若删除的是队尾节点
		Q.rear = Q.front;		//队尾指针指向头结点

	free(p);					//释放 p 节点

	return OK;
}

//销毁链队列
Status Destroy_Queue(LinkQueue &Q)
{
	while(Q.front)				//Q.front不为空
	{
		Q.rear = Q.front->next;	//Q.rear 指向 Q.front 的下一个节点
		free(Q.front);			//释放 Q.front
		Q.front = Q.rear;		// Q.front 指向 Q.rear
	}
	return OK;
}

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
}

//后序递归遍历
void PostOrder(BinTree &T)
{
	if (T == NULL)
		return;

	PostOrder(T->lchild);				//输出左孩子
	PostOrder(T->rchild);				//输出右孩子
	printf("%c", T->data);
}

//层序递归遍历
void LeveOrder(BinTree &T)
{
	LinkQueue Q;
	QElemType a;

	if (T == NULL)
		return;

	Init_Queue(Q);								//初始化队列 q
	Insert_Queue(Q, T);							//根指针入队

	while( ! Empty_Queue(Q))
	{
		Delete_Queue(Q, a);						//出队
		printf("%c", a->data);

		if (a->lchild != NULL)					//若 a 有左孩子
			Insert_Queue(Q, a->lchild);			// a 的左孩子入队

		if (a->rchild != NULL)					//若 a 有右孩子
			Insert_Queue(Q, a->rchild); 		// a 的右孩子入队
	}

	printf("\n");
	Destroy_Queue(Q);							//销毁队列 q
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
