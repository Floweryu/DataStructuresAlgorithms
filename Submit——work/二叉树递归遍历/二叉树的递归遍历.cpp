/*
	Name: 二叉树的四种递归遍历 
	Author: 张俊峰 
	Date: 14/11/18 13:54
	Description: 包含了二叉树的前序、中序、后序的递归遍历和层序遍历。根据菜单进行输入，按'q'退出程序。 
*/

#include "link_queue.h"

//构造空的二叉树
void InitBinTree(BinTree &T)
{
	T = NULL;
}

//销毁二叉树
void DestroyBinTree(BinTree &T)
{
	if (T)
	{
		DestroyBinTree(T->lchild);		//递归销毁左子树，若没有左子树，则不执行操作
		DestroyBinTree(T->rchild);		//递归消除右子树，若没有右子树，则不执行操作
		free(T);						//释放根节点
		T = NULL;						//指针指向空 
	}
}

//先序递归遍历
void PreOrder(BinTree T)
{
	if (T == NULL)
		return;
	
	printf("%c ", T->data);				//先输出根值 
	PreOrder(T->lchild);				//输出左孩子 
	PreOrder(T->rchild);				//输出右孩子 
} 

//中序递归遍历
void InOrder(BinTree T)
{
	if (T == NULL)
		return;
	
	InOrder(T->lchild);					//输出左孩子
	printf("%c ", T->data);
	InOrder(T->rchild);					//输出右孩子				 
} 

//后序递归遍历
void PostOrder(BinTree T)
{
	if (T == NULL)
		return;
		
	PostOrder(T->lchild);				//输出左孩子 
	PostOrder(T->rchild);				//输出右孩子 
	printf("%c ", T->data);
}
 
//层序递归遍历
void LeveOrder(BinTree T)
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
		printf("%c ", a->data);
		
		if (a->lchild != NULL)					//若 a 有左孩子 
			Insert_Queue(Q, a->lchild);			// a 的左孩子入队 

		if (a->rchild != NULL)					//若 a 有右孩子 
			Insert_Queue(Q, a->rchild); 		// a 的右孩子入队 
	}
	
	printf("\n");
	Destroy_Queue(Q);							//销毁队列 q 
}

//按先序输入二叉树中的值
void CreateBinTree(BinTree &T)
{
	TElemType ch;
	
	scanf("%c", &ch);									//输入值 
	
	if (ch == '#')
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
	printf("********************************************************\n");
	printf("*****   按先序输入二叉树中的值，      enter   'a' ******\n");
	printf("*****   前序递归遍历输出二叉树，      enter   'b' ******\n");
	printf("*****   中序递归遍历输出二叉树，      enter   'c' ******\n");
	printf("*****   后序递归遍历输出二叉树，      enter   'd' ******\n");
	printf("*****   层序递归遍历输出二叉树，      enter   'e' ******\n"); 
	printf("********************************************************\n");
	
	BinTree T;
	char str;			//接收从键盘输入的符号 
	do
	{
		printf("\n");
		printf("Please enter a char:    ");
		str=getche();		/*从键盘获取一个字符并显示，不按回车直接执行*/ 
		printf("\n");
		switch(str)
		{
			case 'a':
				{
					printf("请按先序输入二叉树（以'#'表示结点为空）：\n");
					CreateBinTree(T);
					break;
				}
			case 'b':
				{
					printf("前序递归遍历输出二叉树：\n");
					PreOrder(T);
					printf("\n");
					break;
				}
			case 'c':
				{
					printf("中序递归遍历输出二叉树：\n");
					InOrder(T);
					printf("\n");
					break;
				}
			case 'd':
				{
					printf("后序递归遍历输出二叉树：\n");
					PostOrder(T);
					printf("\n");
					break;
				}
			case 'e':
				{
					printf("层序遍历输出二叉树：\n");
					LeveOrder(T);
					printf("\n");
					break;
				}
			default: printf("Wrong!!!");
		} //end switch
	}while (str != 'q');
}
			
