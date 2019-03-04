/*
	Name:二叉树的非递归遍历 
	Copyright: 
	Author: 小蜜蜂嗡嗡嗡 
	Date: 14/11/18 19:14
	Description: 实现了二叉树的前序、中序、后序的非递归遍历 
*/
#include "single_stack.h"

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
/*
//后序遍历二叉树的非递归算法		有错误 
void Post_Order(BinTree T)
{
	LinkStack S;
	Init_Stack(S);
	BinTree p = T, cur = NULL;
	Push_Stack(S, p);
	
	while(! Empty_Stack(S))
	{
		GetTop_Stack(S, p);
		
		if ((p->lchild == NULL && p->rchild == NULL) || (cur == p->lchild || cur == p->rchild))
		{
			printf("%c ", p->data);
			Pop_Stack(S, p);
			cur = p;
		}
		else 
		{
			if (p->rchild != NULL)
			{
				printf("%c...", p->rchild->data);
				Push_Stack(S, p->rchild);
			}
		
			if (p->lchild != NULL)
			{
				printf("%c...", p->lchild->data);
				Push_Stack(S, p->lchild);
			}
		}
	}
}
*/
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
	printf("*****   前序非递归遍历输出二叉树，    enter   'b' ******\n");
	printf("*****   中序非递归遍历输出二叉树，    enter   'c' ******\n");
//	printf("*****   后序非递归遍历输出二叉树，    enter   'd' ******\n");
//	printf("*****   层序递归遍历输出二叉树，      enter   'e' ******\n"); 
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
					printf("前序非递归遍历输出二叉树：\n");
					Pre_Order(T);
					printf("\n");
					break;
				}
			case 'c':
				{
					printf("中序非递归遍历输出二叉树：\n");
					In_Order(T);
					printf("\n");
					break;
				}
		/*	case 'd':
				{
					printf("后序非递归遍历输出二叉树：\n");
					Post_Order(T);
					printf("\n");
					break;
				}
		/*	case 'e':
				{
					printf("层序遍历输出二叉树：\n");
					LeveOrder(T);
					printf("\n");
					break;
				}*/
			default: printf("Wrong!!!");
		} //end switch
	}while (str != 'q');
}
