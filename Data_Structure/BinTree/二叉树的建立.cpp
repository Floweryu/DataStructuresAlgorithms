#include "single_stack.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>


//��������������Ϊ������������е�ֵ
void PreCreateTree(BinTree &T)
{
	TElemType ch;
	
	scanf("%c", &ch);									//����ֵ 
	
	if (ch == '#')
		T = NULL;
	else
	{
		T = (BinTree)malloc(sizeof(BinTreeNode));
		if ( ! T)
			exit(OVERFLOW);
	
		T->data = ch;									//��ֵ���� T ��� 
		PreCreateTree(T->lchild);						//�ݹ鹹�������� 
		PreCreateTree(T->rchild);						//�ݹ鹹�������� 
	}
}


void Pre_Order(BinTree T)	//������ڵ�ʱ��� 
{
	LinkStack S;
	Init_Stack(S);
	BinTree p = T;
	while(p || ! Empty_Stack(S))
	{
		if(p)								//�� p������������������ ���ǿյ�ʱ�� 
		{
			Push_Stack(S, p);				//�� p ��ջ 
			printf("%c ", p->data);			//���ջ��Ԫ�� 
			p = p->lchild;					//ָ�������� 
		}
		else							 	//��������Ϊ�� 
		{	
			Pop_Stack(S, p);				//������ǰ�յĽڵ� 
			p = p->rchild;					// p ָ�������� 
		}
	}
	printf("\n");
} 

//�����µĽڵ� 
BinTree newcode(char c)									//�����ݲ��뵽�ڵ��� 
{
	BinTree t = (BinTree)malloc(sizeof(BinTreeNode));
	t->data = c;
	t->lchild = t->rchild =NULL;
	return t;											//���ش������ݵĽ�� 
}

//�����ű�ʾ������������
int ParCreateTree(BinTree &T, char *string)
{
	LinkStack S;
	BinTree e, t;							//���ܷ��ؽ��ֵ 
	int flag;							//��־λ���ж����Һ��� 
	Init_Stack(S);
	
	int i = 0;
	char ch;
	
	while (ch = string[i++] != '\0');			//��� i + 1 ������'\0' 
	{
		if (ch == '(')							//�����һ��ֵ�������� 
		{
			t = newcode(string[i-1]);			//��ǰһ��ֵ�ŵ������ 
			Push_Stack(S, t);					//��������ǰ��ֵ��ջ 
			flag = 1;							//��־λ������ 
		}
		else if(ch == ')')						//����������� 
		{
			Pop_Stack(S, e);					//ջ��Ԫ�س�ջ��	
		}
		else if(ch == ',')						//����Ƕ��ţ� 
		{							
			flag = 2;							//��־λ���Һ��� 
		}		
		else									//����ǽ�� 
		{
			t = newcode(string[i]);				//��ֵת��Ϊ��� 
			GetTop_Stack(S, e);					//����ջ��Ԫ�صĽڵ�
			 	
			if (T == NULL)
				T = t;
				
			if (flag == 1)						//����� 1  
			{
				e->lchild = t;					//�������� 
			}
			else								//����� 2 
			{
				e->rchild = t;					//�����Һ��� 
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
