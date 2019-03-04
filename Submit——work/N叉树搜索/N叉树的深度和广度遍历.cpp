/*
	Name: N����������Ⱥ͹�����ȵݹ�����㷨 
	Author: �ſ��� 
	Date: 17/11/18 16:25
	Description: 
*/

#include "link_queue_n.h"
#include <string.h> 

//������ 
void CreateTree(CSTree &T)
{
	char c[20];				//��ʱ��ź��ӵĽڵ�
	CSTree p, pl;
	LinkQueue q;
	int i, m;
	
	Init_Queue(q);			//��ʼ������q
	printf("��������ڵ㣨�ַ��ͣ�#Ϊ�գ���");
	scanf("%c%*c",  &c[0]);
	if (c[0] != '#')
	{
		T = (CSTree) malloc (sizeof(CSNode));		//�������ڵ�
		T->data = c[0];								//�����ڵ㸳ֵ
		T->nextsibling = NULL;						//���ڵ�û����һ���ֵ�
		Insert_Queue(q, T);							//��Ӹ��ڵ��ָ��
		
		while ( ! Empty_Queue(q))
		{
			Delete_Queue(q, p);						//���ӵ�һ������ָ��
			printf("�밴����˳������ڵ� %c �����к��ӣ�", p->data);	
			gets(c);								//�����нڵ�����
			m = strlen(c);							//����ڵ����
			if (m > 0)
			{
				pl = p->firstchild = (CSTree) malloc (sizeof(CSNode));		//�������ӽڵ�
				pl->data = c[0];
				Insert_Queue(q, pl);
				
				for (i = 1; i < m; i++)
				{
					pl->nextsibling = (CSTree) malloc (sizeof(CSNode));		//������һ���ֵܽڵ�
					pl = pl->nextsibling;									//pl ָ����һ���ֵܽڵ�
					pl->data = c[i];										//�� pl �ڵ㸳ֵ
					Insert_Queue(q, pl);									//��� pl ��ָ��ָ��
		 
				}
				pl->nextsibling = NULL; 
			}
			else
				p->firstchild = NULL; 
		} 
		
	} 
	else
		T = NULL;		//���� 
}

//������� ����-�ֵ� ��������ṹ����
void PostOrderTraverse(CSTree T)
{
	CSTree p;
	
	if (T == NULL)
		return;
		
	if (T->firstchild)
	{
		PostOrderTraverse(T->firstchild);
		p = T->firstchild->nextsibling;			// p ָ���ӵ���һ���ֵ�
		while (p)
		{
			PostOrderTraverse(p);				//���������һ���ֵ����� 
			p = p->nextsibling;					// p ָ������һ���ֵ� 
		} 
	}
	printf("%c ", T->data);
} 

//�ȸ����� ����-�ֵܶ�������ṹ
void PreOrderTraverse(CSTree T)
{
	if (T == NULL)
	 	return;
		
	printf("%c ", T->data);						//�ȷ��ʸ��ڵ� 
	PreOrderTraverse(T->firstchild);			//���ȸ����������� 
	PreOrderTraverse(T->nextsibling);			//����ȸ�������һ���ֵ����� 
} 

//������� ����-�ֵ�����ṹ����
void LeveOrderTraverse(CSTree T)
{
	CSTree p;
	LinkQueue q;
	Init_Queue(q);
	
	if (T == NULL)
		return;
		
	printf("%c ", T->data);
	Insert_Queue(q, T);
	
	while ( ! Empty_Queue(q))
	{
		Delete_Queue(q, p);
		
		if (p->firstchild)
		{
			p = p->firstchild;				// p ָ���ӽڵ�
			printf("%c ", p->data);			//���ʳ��ӽڵ�
			Insert_Queue(q, p);				//��ӳ��ӽڵ��ָ��
			while(p->nextsibling)
			{
				p = p->nextsibling;			// p ָ����һ���ֵܽڵ�
				printf("%c ", p->data);		//������һ���ֵ�
				Insert_Queue(q, p);			//����ֵܽڵ��ָ�� 
			} 
		}
	}
	printf("\n"); 
} 

int main()
{
	printf("*****************************************************************\n");
	printf("*****   ������                                 enter   'a' ******\n");
	printf("*****   �ȸ����� ����-�ֵ� ��������ṹ��      enter   'b' ******\n");
	printf("*****   ������� ����-�ֵ� ��������ṹ        enter   'c' ******\n");
	printf("*****   ������� ����-�ֵ� ����ṹ������      enter   'd' ******\n");
	printf("*****************************************************************\n");
	
	CSTree T;
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
					CreateTree(T);
					break;
				}
			case 'b':
				{
					printf("�ȸ����� ����-�ֵ� ��������ṹ:\n");
					PreOrderTraverse(T);
					break;
				}
			case 'c':
				{
					printf("������� ����-�ֵ� ��������ṹ��\n");
					PostOrderTraverse(T);
					break;
				}
			case 'd':
				{
					printf("������� ����-�ֵ� ����ṹ������\n");
					LeveOrderTraverse(T);
					break;
				}
			default: printf("Wrong!!!\n");	
		} 
	} while (str != 'q');
}
