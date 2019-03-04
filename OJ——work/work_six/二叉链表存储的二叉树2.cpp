#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>


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
typedef BinTree SElemType;			//定义栈中的数据类型

typedef struct SqStack
{
	SElemType data;				//数据域
	struct SqStack *next;		//指针域
}SqStack,*LinkStack;

//初始化链栈
/* 建立一个空栈，创建链栈的头结点，将其NULL置空	*/
Status Init_Stack(LinkStack &S)
{
	S = (LinkStack)malloc(sizeof(SqStack));		//申请头结点空间

	if(S == NULL)								//判断新空间是否分配成功
		exit(OVERFLOW);

	S->next = NULL;								//头结点后继指向空

	return OK;
}

//向栈里输入数据
Status Create_Stack(LinkStack &S, int n)
{
	LinkStack q;									// q 指针用来申请新的节点
	int i;											//计数器

	for(i = 0; i < n; i++)							//在栈顶位置依次插入元素
	{
		q = (LinkStack) malloc (sizeof (SqStack));	//申请空间
		if(q == NULL)								//判断空间是否申请成功
			exit(OVERFLOW);

		scanf("%d", &q->data);						//向新空间里输入数据

		q->next = S->next;							// q 的后继指向头结点 S 的后继
		S->next = q;								//头结点 S 的后继指向 q
	}
	return OK;
}

//判断链栈是否为空
Status Empty_Stack(LinkStack &S)
{
	if(S->next == NULL)	//如果头结点的后继指向NULL，即为空 返回真
		return OK;
	else
		return FALSE; 	//否则，不为空
}

//清空链栈
Status Clear_Stack(LinkStack &S)
{

	LinkStack p,q;				//定义 p q 指针

	p = S->next;				// p 指向第一个节点
	while(p != NULL)			//当 p 不指向空的时候循环
	{
		q = p->next;			// q 指向 p 的下一个节点
		free(p);				//释放 p 节点
		p = q;					// p 重新指向 q 节点
	}

	S->next = NULL;				//节点释放完后，是栈头结点指向NULL，回到初始化状态

	return OK;
}

//销毁链栈
Status Destroy_Stack(LinkStack &S)
{
	LinkStack p,q;		//定义 p q 指针

	p = S->next;		// p 指向第一个节点
	while(p != NULL)	//当 p 不指向空的时候循环
	{
		q = p->next;	// q 指向 p 的下一个节点
		free(p);		//释放 p 节点
		p = q;			// p 重新指向 q 节点
	}

	free(S);			//再把头结点释放

	return OK;
}

//返回链栈元素的个数
Status Length_Stack(LinkStack &S)
{
	LinkStack p;		//定义一个指针用来遍历
	int len =  0;		//定义一个整形变量，计数器，用来统计栈的长度 ,初始值为 0 .

	p = S->next;		// p 指针指向第一个结点
	while(p != NULL)	//当 p 还未到 NULL 的时候遍历
	{
		len++; 			//计数器加一
		p = p->next; 	// p 指向下一个节点
	}

	return len;			//返回计数器的值，即链栈的长度
}

//若链栈不为空，就返回栈顶元素,并不删除
Status GetTop_Stack(LinkStack &S, SElemType &e)
{
	if(S->next == NULL)			//判断链栈是否为空
		return ERROR;
	else
		e = S->next->data;	//不为空，就返回第一个结点的元素
	return OK;
}

//在栈顶插入元素
Status Push_Stack(LinkStack &S,SElemType e)
{
	LinkStack p;			//定义一个指针，用来指向要插入元素

	p = (LinkStack) malloc (sizeof(SqStack));	//为指针 p 申请存储空间
	if(p ==  NULL)			//判断空间是否申请成功
		exit(OVERFLOW);

	p->data = e;			// 把要插入的值赋给p的数据域
	p->next = S->next;		// p 的后继指向头结点的后继
	S->next = p;			// p 的前驱指向头结点的后继

	return OK;				//插入成功，返回真
}

//删除栈顶元素，并用 e 返回其值
Status  Pop_Stack(LinkStack &S, SElemType &e)
{
	if(S->next == NULL)		//判断链栈是否为空栈
		return ERROR;

	LinkStack p;

	p = S->next;			// p 指向栈顶元素
	S->next = p->next;		//头结点 S 的后继指向栈顶元素的下一个元素

	e = p->data;			//把栈顶存储的值赋给 e 返回

	free(p);				//释放栈顶节点

	return OK;
}

//输出链栈里的全部元素
Status Printf_Stack(LinkStack &S)
{
	if(S->next == NULL)			//判断链栈是否为空
		return ERROR;

	LinkStack p;
	p = S->next;				// p 指向栈顶节点

	while(p != NULL)			//当 p 没有指向空的时候循环
	{
		printf("%c ",p->data);	//输出 p 所指的元素
		p = p->next;			//移动 p 指针
	}
}

//先序遍历二叉树的非递归算法
void Pre_Order(BinTree T)	//在入根节点时输出
{
	LinkStack S;
	Init_Stack(S);
	BinTree p = T;
	while(p || ! Empty_Stack(S))
	{
		if(p)								//当 p（左子树或右子树） 不是空的时候
		{
			Push_Stack(S, p);				//把 p 入栈
			printf("%c ", p->data);			//输出栈顶元素
			p = p->lchild;					//指向左子树
		}
		else							 	//若左子树为空
		{
			Pop_Stack(S, p);				//弹出当前空的节点
			p = p->rchild;					// p 指向右子树
		}
	}
	printf("\n");
}
//中序遍历二叉树的非递归算法
void In_Order(BinTree T)		//左子树为空时输出
{
	LinkStack S;
	Init_Stack(S);
	BinTree p = T;
	while (p || ! Empty_Stack(S))		//当二叉树不空或者栈不空
	{
		if (p)							//若二叉树不空
		{
			Push_Stack(S, p);			//入栈根指针
			p = p->lchild;				// T 指向其左孩子
		}
		else							//当左子树为空时
		{
			Pop_Stack(S, p);			//出栈指针
			printf("%c ", p->data);		//输出节点值
			p = p->rchild;				// T 指向其右孩子
		}
	}
	printf("\n");
	Destroy_Stack(S);					//销毁栈
}

//按先序输入二叉树中的值
void CreateBinTree(BinTree &T)
{
	TElemType ch;

	scanf("%c", &ch);									//输入值

	if (ch == ' ')
		T = NULL;
	else
	{
		T = (BinTree)malloc(sizeof(BinTreeNode));
		if ( ! T)
			exit(OVERFLOW);

		T->data = ch;									//将值赋给 T 结点
		CreateBinTree(T->lchild);						//递归构造左子树
		CreateBinTree(T->rchild);						//递归构造右子树
	}
}

int main()
{
    BinTree T;
    CreateBinTree(T);
    Pre_Order(T);
    In_Order(T);
    In_Order(T);
}
