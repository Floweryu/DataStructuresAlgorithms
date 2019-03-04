#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int ElemType;

typedef struct LNode{
	ElemType	data;				//������
	struct LNode	*next;			//ָ����
}LNode,*LinkList;

//��ʼ������
void Init_List(LNode *L)
{
	L = (LinkList) malloc (sizeof (LNode));		//����ͷ���ռ�

	if( ! L)									//�жϿռ��Ƿ�����ɹ�
		exit(OVERFLOW);

	L->next = NULL;								//ͷ�����ָ���
}


//����Ĵ�����β�巨
int Create_List(LNode *L, int n)
{
	LNode *p, *q;									//���� p , q ָ��
	int i;											//��������� i

	q = L;											//�� q ָ��ָ��ͷ���
	for(i = 0; i < n; i++)
	{
		p = (LinkList) malloc (sizeof(LNode));		//�����½ڵ�
		scanf("%d", &p->data);						//��������
		//�������д����൱�ڰ�p�����뵽�����У����Ǵ�ͷ��β��˳�����
		p->next = NULL;								//p������һ����ַָ��NULL,�����½ڵ��ָ��p����һ����ַ��Զָ��NULL
		q->next = p;								//q����һ����ַָ��p����ָ��p��ǰ��Ҫ����һ��Ԫ�صĺ�������
		q = p;										//�ѵ�ǰ�Ѳ���Ľڵ��ַ����q���Ա�������ı���
	}
 }

//���򴴽�һ��������ͷ�鷨��
int reCreate_List(LNode *L,int n)
{
	LNode *p;										//���� p ָ��
	int i;											//���������

	for(i = 0; i < n; i++)
	{
		p = (LinkList) malloc (sizeof(LNode));		//�����½ڵ�
		scanf("%d", &p->data);				 		//��������

		p->next = L->next;							//�� p �ڵ������β������
		L->next = p;
	}
}

//��ӡ��������е�����
int Printf_List(LNode *L)
{
	LNode *p;

	p = L->next;				//ʹpָ��ָ������ĵ�һ������
	while(p != NULL)
	{
		printf("%d ",p->data);	//���Ԫ��
		p = p->next;				//ָ�����
	}
 }

//��������ĳ���
int Length_List(LNode *L)
{
	LNode *p;			//����һ��ָ�����
	int len = 0;		//����һ��������������ڵ�ĸ���

	p = L->next;		//ָ��pָ������ĵ�һ���ڵ�
	while(p != NULL)
	{
		len++;			//�ȼ�һ�����ƶ�ָ�룬��������pָ��ָ���ռ�ʱ��ʱ����ѭ���Ӷ���������һ
		p = p->next;	//ָ�����
	}

	return len;			//����������
 }

//�ж������Ƿ�Ϊ�գ��վͷ���1
int Empty_List(LNode *L)
{
	/*��ֻ��һ��ͷ����ʱ�򣬸������Ϊ��*/
	if((L->next) == NULL)		//ͷ�����NULL����
		return OK;
	else
		return ERROR;
}

//����i��Ԫ�ش���ʱ������ֵ����e������OK
int iGetElem_List(LNode *L, int i, ElemType &e)
{
	LNode *p;			// ����һ�� ����ָ��
	int j = 1;			// j Ϊ������

	p = L->next;		//ʹpָ���һ�����
	while(p && j < i)	//˳ָ�������ң�֪��pָ���i��Ԫ�ػ�pΪ��
	{
		p = p->next;   	//��������
		j++;			//��¼������λ�úʹ���
	}

	if( ! p || j > i)	//�жϴ�ʱ�� p �Ƿ�Ϊ�� �� j �Ƿ���� i
		return ERROR;

	e = p->data;		//���� i ��λ�õ�Ԫ��ֵ���� e ����
	return OK;
}

//��ֵ����Ѱ��Ԫ��e������e��λ��
int eGetElem_List(LNode *L, ElemType &e)
{
	LNode *p;				//����һ������ָ��
	int count = 0;			//���������

	p = L->next;			// p ָ���һ�����
	while(p != NULL)
	{
		count++;			//λ�ü�һ��

		if(p->data == e)	//����ҵ����ֵ
			return (count);		//����λ��ֵ

		p = p->next;		//pָ����һ�����
	}

	return ERROR;
 }


//��������ָ��λ��i��֮ǰ����������
//���а����ڱ�ͷ���롢�ڱ�β���롢�ڱ��в�������λ��
int Insert_List(LNode *L, int i, ElemType e)
{
	LNode *p, *s;			//����ָ�룬p ����������s �����洢����ֵ
	int j=0;				//���������

	p = L;					// p ָ��ͷ���
	while(p && j < i-1)		//Ѱ�ҵ� i-1 ���ڵ�
	{
		p = p->next;			//��������
		j++;
	}						//������ѭ��ʱpָ��ָ���i-1��Ԫ��

	if( ! p || j > i-1)		//�ж� p �Ƿ�Ϊ�� �� j �Ƿ���� i
		return ERROR;

	s = (LinkList) malloc (sizeof(LNode));

	s->data = e;			//��Ҫ��������ݸ��� sָ��
	s->next = p->next;		//p->nextָ���i��Ԫ�أ��ѵ�i��Ԫ�ص�ǰ���ӵ�Ҫ����ڵ�ĺ���
	p->next = s;			//��i-1�ڵ�ĺ����ӵ�Ҫ����Ԫ�ص�ǰ��

	return OK;
 }

//ɾ����i��Ԫ�أ�����e������ֵ��
//���а���ɾ���Ľڵ��Ǳ�ͷ�����м�
int Delete_List(LNode *L, int i, ElemType &e)
{
	LNode *p,*s;			//���� p s ָ��
	int j=0;				//���������

	p = L;					// p ָ��ָ��ͷ���
	while(p && j<i-1)
	{
		p = p->next;
		j++;
	}						//����ѭ��ʱpָ���i-1���ڵ�

	if( !p->next || j > i-1)	//���� i ���ڵ�Ϊ��ʱ
		return ERROR;

	s = p->next;   			//sָ��ָ���i���ڵ�
	p->next = s->next;		//��i-1���ڵ�ĺ������i���ڵ����������i+1���ڵ��ǰ����

	e = s->data;			//�ѵ�i���ڵ��ֵ����e����
	free(s);				//�ͷŵ�i���ڵ�Ŀռ�

	return OK;
}

//ɾ�������������е��ظ�Ԫ��
int reDelete_List(LNode *L)
{
	LNode *p,*s,*q;					//����ָ��

	p = L->next;					// p ָ���һ���ڵ�
	q = p->next;					// q ָ�� p ����һ���ڵ�

	while(q != NULL)
	{
		if(p->data == q->data)		//������������ڵ�ֵ���
		{
			p->next = q->next;		// p �ĺ��ָ�� q �ĺ��
			s = q;					//����ȵĺ�һ���ڸ��� s
			q = q->next;			// q ����������
			free(s);				//�ͷ� s �ڵ�
		}
		else
		{
			p = p->next;			// p ������
			q = q->next;			// q ������
		}
	}
 }

//�Ե���������������
/*��Ҫ˼�룺��ԭ��������ݴ�ͷ��βͨ��������������ͷ�巨�����뵽�������У�
			(�൱������������),Ȼ�������������*/
int rePrintf_List(LNode *L)
 {
 	LNode *p, *s, *q;
 	LinkList L0;					//����һ���µ����������洢��ת�������

 	L0 = (LinkList) malloc (sizeof(LNode));
 	L0->next = NULL;				//��������г�ʼ��

 	p = L->next;					//pָ��ԭ����ĵ�һ�����
 	while(p != NULL)
 	{
 		q = (LinkList) malloc (sizeof(LNode));		//����һ���½ڵ������洢��תԪ��

 		q->data = p->data;			//��ԭ��L��������ݰ���ͷ��㵽β��˳�򸳸�������L0�ڵ�q��

 		q->next = L0->next;			//���½ڵ���ͷ�巨����������L0�ĺ��濪ʼ�洢
 		L0->next = q;

 		p = p->next;				//����ԭ����L
 	}

 	s = L0->next;					//��������L0�������
	while(s != NULL)
	{
		printf("%d ",s->data);
		s = s->next;				//ָ�����
	}
 }

int main()
{
	printf("******************************************************************\n");
	printf("*****        ���򴴽�һ����������Please enter 'a'          *****\n");
	printf("*****         ���ص�������ĳ��ȣ�Please enter   'b'         *****\n");
	printf("*****         ������������е����ݣ�Please enter 'c'         *****\n");
	printf("*****       �ж������Ƿ�Ϊ�գ�Please enter 'd'               *****\n");
	printf("*****       ���ظ���λ�õĽڵ�Ԫ��ֵ��Please enter 'e'       *****\n");
	printf("*****     ���ظ���Ԫ��ֵ�Ľڵ�λ�ã�Please enter 'f'         *****\n");
	printf("*****   ��������ָ��λ��i��֮ǰ���������ݣ�Please enter 'g'  *****\n");
	printf("*****   ɾ����i��Ԫ�أ�����e������ֵ��Please enter 'h'       *****\n");
	printf("*****        ���򴴽�һ����������Please enter 'i'          *****\n");
	printf("*****       ɾ�������������е��ظ�Ԫ�أ�Please enter 'j'   *****\n");
	printf("*****      �Ե���������������,  Please enter 'k'           *****\n");
	printf("*****      ��ʼ��һ����������   Please enter  'l'          *****\n");
	printf("******************************************************************\n");
	LNode L;
	char str;
	int N,I,k;
	ElemType E;
	do
	{
		printf("\n");
		printf("Please enter a char:    ");
		str=getche();/*�Ӽ��̻�ȡһ���ַ�����ʾ�������س�ֱ��ִ��*/
		printf("\n");/*	getchar();	/*�����������Ļس���������س���Ҳ�ᱻ��Ϊ���ַ�*/
		switch(str)
		{
			case 'a':/* ���򴴽�һ����������*/
					{
						printf("�����봴������ĳ��ȣ�  ");
						scanf("%d",&N);
						Create_List(&L,N);
						break;
					}
			case 'b':/* ���ص�������ĳ���*/
					{
						k=Length_List(&L);
						printf("������ĳ����ǣ�  %d",k);
						break;
					}
			case 'c':/* ������������е�����*/
					{
						printf("�˵��������е�����Ϊ��\n");
						Printf_List(&L);
						break;
					}
			case 'd':/* �ж������Ƿ�Ϊ��*/
					{
						k=Empty_List(&L);
						if(k)
						printf("����һ���յ�����\n");
						else
						printf("�ⲻ��һ���յ�����\n");
						break;
					}
			case 'e':/* ���ظ���λ�õĽڵ�Ԫ��ֵ*/
					{
						printf("����֪���ڼ���Ԫ�أ�   ");
						scanf("%d",&I);
						iGetElem_List(&L,I,E);
						printf("��  %d  ��Ԫ�ص�ֵΪ��  %d\n",I,E);
						break;
					}
			case 'f':/*���ظ���Ԫ��ֵ�Ľڵ�λ��*/
					{
						printf("��������֪���Ƿ��������е���ֵ��  ");
						scanf("%d",&E);
						k=eGetElem_List(&L,E);
						if(k)
							printf("ֵΪ  %d  �Ǳ��еĵ�  %d  ��Ԫ��\n",E,k);
						else
							printf("��������û��ֵΪ%d��Ԫ��\n",E);
						break;
					 }
			case 'g':/*��������ָ��λ��i��֮ǰ����������*/
					{
						printf("���������Ԫ�ص�λ�ã�  ");
						scanf("%d",&I);
						printf("���������Ԫ�ص�ֵ��  ");
						scanf("%d",&E);
						k=Insert_List(&L,I,E);
						if(k)
						{
							printf("����������ֵΪ��\n");
							Printf_List(&L);
							printf("\n");
						 }
						break;
					 }
			case 'h':/*ɾ����i��Ԫ�أ�����e������ֵ*/
					{
						printf("������ɾ��Ԫ�ص�λ�ã�  ");
						scanf("%d",&I);
						k=Delete_List(&L,I,E);
						if(k)
						{
							printf("ɾ����λ�õ�Ԫ��ֵΪ:  %d\n",E);
							printf("ɾ�������Ա�Ϊ:\n");
							Printf_List(&L);
							printf("\n");
						}
							break;
					}
			case 'i':/* ���򴴽�һ����������*/
					{
						printf("�����봴������ĳ��ȣ�  ");
						scanf("%d",&N);
						reCreate_List(&L,N);
						break;
					}
			case 'j':/*ɾ�������������е��ظ�Ԫ��*/
					{
						reDelete_List(&L);
						break;
					}
			case 'k':/*�Ե���������������*/
					{
						rePrintf_List(&L);
						break;
					}
			case 'l':/*��ʼ��һ����������*/
					{
						Init_List(&L);
						break;
					}
			default:printf("wrong!\n");
		}
	}while(str!='q');
}
