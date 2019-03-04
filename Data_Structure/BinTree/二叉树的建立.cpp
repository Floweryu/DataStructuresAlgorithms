#include "single_stack.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>


//按先序左右子树为空输入二叉树中的值
void PreCreateTree(BinTree &T)
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
		PreCreateTree(T->lchild);						//递归构造左子树 
		PreCreateTree(T->rchild);						//递归构造右子树 
	}
}


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

//分配新的节点 
BinTree newcode(char c)									//把数据插入到节点中 
{
	BinTree t = (BinTree)malloc(sizeof(BinTreeNode));
	t->data = c;
	t->lchild = t->rchild =NULL;
	return t;											//返回带该数据的结点 
}

//用括号表示法建立二叉树
int ParCreateTree(BinTree &T, char *string)
{
	LinkStack S;
	BinTree e, t;							//接受返回结点值 
	int flag;							//标志位，判断左右孩子 
	Init_Stack(S);
	
	int i = 0;
	char ch;
	
	while (ch = string[i++] != '\0');			//如果 i + 1 个不是'\0' 
	{
		if (ch == '(')							//如果后一个值是左括号 
		{
			t = newcode(string[i-1]);			//把前一个值放到结点中 
			Push_Stack(S, t);					//把左括号前的值入栈 
			flag = 1;							//标志位是左孩子 
		}
		else if(ch == ')')						//如果是右括号 
		{
			Pop_Stack(S, e);					//栈顶元素出栈，	
		}
		else if(ch == ',')						//如果是逗号， 
		{							
			flag = 2;							//标志位是右孩子 
		}		
		else									//如果是结点 
		{
			t = newcode(string[i]);				//把值转换为结点 
			GetTop_Stack(S, e);					//返回栈顶元素的节点
			 	
			if (T == NULL)
				T = t;
				
			if (flag == 1)						//如果是 1  
			{
				e->lchild = t;					//赋给左孩子 
			}
			else								//如果是 2 
			{
				e->rchild = t;					//赋给右孩子 
			}
				
		}
		
	}
} 

void ParPrintfTree(BinTree &T)
{
	if (T)
	{
		printf("%c ", T->data);
		
		if (T->lchild != NULL && T->rchild != NULL)
		{
			printf("(");
			ParPrintfTree(T->lchild);
			if (T->rchild != NULL)
			{
				printf(",");
			}
			ParPrintfTree(T->rchild);
			printf(")");
		}
	}
}

int main()
{
	char string[100];
	BinTree root;
	gets(string);
	ParCreateTree(root, string);
	ParPrintfTree(root);
}
