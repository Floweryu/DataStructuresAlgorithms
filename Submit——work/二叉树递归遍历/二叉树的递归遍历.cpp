/*
	Name: �����������ֵݹ���� 
	Author: �ſ��� 
	Date: 14/11/18 13:54
	Description: �����˶�������ǰ�����򡢺���ĵݹ�����Ͳ�����������ݲ˵��������룬��'q'�˳����� 
*/

#include "link_queue.h"

//����յĶ�����
void InitBinTree(BinTree &T)
{
	T = NULL;
}

//���ٶ�����
void DestroyBinTree(BinTree &T)
{
	if (T)
	{
		DestroyBinTree(T->lchild);		//�ݹ���������������û������������ִ�в���
		DestroyBinTree(T->rchild);		//�ݹ���������������û������������ִ�в���
		free(T);						//�ͷŸ��ڵ�
		T = NULL;						//ָ��ָ��� 
	}
}

//����ݹ����
void PreOrder(BinTree T)
{
	if (T == NULL)
		return;
	
	printf("%c ", T->data);				//�������ֵ 
	PreOrder(T->lchild);				//������� 
	PreOrder(T->rchild);				//����Һ��� 
} 

//����ݹ����
void InOrder(BinTree T)
{
	if (T == NULL)
		return;
	
	InOrder(T->lchild);					//�������
	printf("%c ", T->data);
	InOrder(T->rchild);					//����Һ���				 
} 

//����ݹ����
void PostOrder(BinTree T)
{
	if (T == NULL)
		return;
		
	PostOrder(T->lchild);				//������� 
	PostOrder(T->rchild);				//����Һ��� 
	printf("%c ", T->data);
}
 
//����ݹ����
void LeveOrder(BinTree T)
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
		printf("%c ", a->data);
		
		if (a->lchild != NULL)					//�� a ������ 
			Insert_Queue(Q, a->lchild);			// a ��������� 

		if (a->rchild != NULL)					//�� a ���Һ��� 
			Insert_Queue(Q, a->rchild); 		// a ���Һ������ 
	}
	
	printf("\n");
	Destroy_Queue(Q);							//���ٶ��� q 
}

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
	printf("*****   ǰ��ݹ���������������      enter   'b' ******\n");
	printf("*****   ����ݹ���������������      enter   'c' ******\n");
	printf("*****   ����ݹ���������������      enter   'd' ******\n");
	printf("*****   ����ݹ���������������      enter   'e' ******\n"); 
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
					printf("ǰ��ݹ���������������\n");
					PreOrder(T);
					printf("\n");
					break;
				}
			case 'c':
				{
					printf("����ݹ���������������\n");
					InOrder(T);
					printf("\n");
					break;
				}
			case 'd':
				{
					printf("����ݹ���������������\n");
					PostOrder(T);
					printf("\n");
					break;
				}
			case 'e':
				{
					printf("������������������\n");
					LeveOrder(T);
					printf("\n");
					break;
				}
			default: printf("Wrong!!!");
		} //end switch
	}while (str != 'q');
}
			
