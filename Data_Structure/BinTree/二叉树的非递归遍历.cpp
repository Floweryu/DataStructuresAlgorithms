/*
	Name:�������ķǵݹ����
	Copyright:
	Author: С�۷�������
	Date: 14/11/18 19:14
	Description: ʵ���˶�������ǰ�����򡢺���ķǵݹ����
*/
#include "single_stack.h"

//��������������ķǵݹ��㷨
void Pre_Order(BinTree T)	//������ڵ�ʱ���
{
	LinkStack S;
	Init_Stack(S);
	BinTree p = T;
	while(p || ! Empty_Stack(S))
	{
		if(p)								//�� p������������������ ���ǿյ�ʱ��
		{
			Push_Stack(S, p);				//����ջ��ʱ������ڵ�
			printf("%c ", p->data);
			p = p->lchild;
		}
		else							 	//�����սڵ�ʱ����ջԪ�أ����˻��������ǿսڵ�
		{
			Pop_Stack(S, p);
			p = p->rchild;
		}
	}
	printf("\n");
}
//��������������ķǵݹ��㷨
void In_Order(BinTree T)		//������Ϊ��ʱ���
{
	LinkStack S;
	Init_Stack(S);
	BinTree p = T;
	while (p || ! Empty_Stack(S))
	{
		if (p)							//���������ǿ�ʱ����ջ
		{
			Push_Stack(S, p);
			p = p->lchild;
		}
		else							//�������սڵ�ʱ ��ջԪ�أ������
		{
			Pop_Stack(S, p);
			printf("%c ", p->data);
			p = p->rchild;
		}
	}
	printf("\n");
	Destroy_Stack(S);
}
/*
//��������������ķǵݹ��㷨		�д���
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
//����������������е�ֵ
void CreateBinTree(BinTree &T)
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
		CreateBinTree(T->lchild);						//�ݹ鹹��������
		CreateBinTree(T->rchild);						//�ݹ鹹��������
	}
}


int main()
{
	printf("********************************************************\n");
	printf("*****   ����������������е�ֵ��      enter   'a' ******\n");
	printf("*****   ǰ��ǵݹ���������������    enter   'b' ******\n");
	printf("*****   ����ǵݹ���������������    enter   'c' ******\n");
//	printf("*****   ����ǵݹ���������������    enter   'd' ******\n");
//	printf("*****   ����ݹ���������������      enter   'e' ******\n");
	printf("********************************************************\n");

	BinTree T;
	char str;			//���մӼ�������ķ���
	do
	{
		printf("\n");
		printf("Please enter a char:    ");
		str=getche();		/*�Ӽ��̻�ȡһ���ַ�����ʾ�������س�ֱ��ִ��*/
		printf("\n");
		switch(str)
		{
			case 'a':
				{
					printf("�밴�����������������'#'��ʾ���Ϊ�գ���\n");
					CreateBinTree(T);
					break;
				}
			case 'b':
				{
					printf("ǰ��ǵݹ���������������\n");
					Pre_Order(T);
					printf("\n");
					break;
				}
			case 'c':
				{
					printf("����ǵݹ���������������\n");
					In_Order(T);
					printf("\n");
					break;
				}
		/*	case 'd':
				{
					printf("����ǵݹ���������������\n");
					Post_Order(T);
					printf("\n");
					break;
				}
		/*	case 'e':
				{
					printf("������������������\n");
					LeveOrder(T);
					printf("\n");
					break;
				}*/
			default: printf("Wrong!!!");
		} //end switch
	}while (str != 'q');
}
