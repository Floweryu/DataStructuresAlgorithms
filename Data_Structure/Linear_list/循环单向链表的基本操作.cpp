#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;

typedef struct LNode{
	ElemType	data;			//������ 
	struct LNode	*next;		//ָ���� 
}LNode,*LinkList;

//��ʼ������ 
void Inite_cirList(LNode *L)
{
	L = (LinkList) malloc (sizeof(LNode));		//����ͷ��� 
	if( ! L)									//�жϽڵ��Ƿ����ɹ� 
		exit(ERROR);
		
	L->next = L;								//ͷ���ָ��ָ��ͷ��� 
}


//����Ĵ�����������		
int Create_cirList(LNode *L,int n)
{
	LNode *p,*q;					//pָ�����������½ڵ㣬
									//qָ��������������Զ�����½ڵ㣬�Ա�������һ���½ڵ� 
	int i;							//�������� 
	
	q = L;  						//�ñ���ָ��qָ��ͷ��� 
	for(i = 0; i < n; i++)	
	{
		p = (LinkList)malloc(sizeof(LNode));		//�����½ڵ�
		
		if( ! p)
			exit(OVERFLOW);			//�ж�����ڵ��Ƿ�ɹ� 
			
		scanf("%d", &p->data);		//�������� 
		
		p->next = NULL;				//������Ľڵ����һ����ַָ��� 
		q->next = p;				//q����һ����ַָ��p�������½ڵ㵽������ 
		q = p;						//q�ƶ���p�⣬׼��������һ���ڵ�p 
	}
	
	q->next = L;					//�������ݺ󣬱���ָ��q���ӱ�ͷ������ѭ������ 
 }
 
//��L��Ϊ������
void Clear_cirList(LNode *L)
{
	LinkList p, q;
	
	p = L->next;			//pָ���һ���ڵ� 
	
	while(p != L)			//ѭ��������pû��ָ����β 
	{
		q = p->next;		//qָ��p�ĺ�̽ڵ� 
		free(p);			//�ͷ�p��ǰ��ָ�Ŀռ� 
		p = q;				//pָ��q��ָ�Ľڵ㣬�����ͷŽڵ����һ���ڵ� 
	}
	
	L = L->next;			//�ͷ��������нڵ��ʹͷ���ָ���Լ� 
} 

//����ѭ��������
void Destroy_cirList(LNode *L)
{	//�����ݣ���ͷ���׵�����һ������ 
	Clear_cirList(L);			//�����L 
	free(L);					//�ͷ�ͷ��� 
	L = NULL;					//L��ָ���κδ洢��Ԫ 
 } 
 
//�ж�ѭ���������Ƿ�Ϊ��
Status Empty_cirList(LNode *L)
{	//����ͷ������Ƿ�ָ��ͷ��� 
	if(L->next == L)		//�շ����� 
		return TRUE;
	else					//�ǿշ��ؼ� 
		return FALSE;
}

//����ѭ������������Ԫ�صĸ���
Status Length_cirList(LNode *L)
{
	LinkList p,q;
	int i = 0;
	
	p = L->next;				//pָ���һ���ڵ� 
	while(p != L)				//��pδָ���ͷʱ���� 
	{	
		i++;					//p�Ѿ�ָ���һ���ڵ㣬�����ȼ�һ 
		p=p->next;				//�ٱ��� 
	}
	
	return i;					//����ͳ�Ƶĸ��� 
 } 
 
//����ָ��λ�õ�Ԫ��
Status GetElem_cirList(LNode *L,int i,ElemType *e)
{	
	int j = 1;					//��������ʵ��λ�ô�1��ʼ 
	LinkList p;
	
	p = L->next;				//pָ���һ���ڵ� 
	while(p !=L && j < i)		//�ؼ���jС��iʱѭ�� 
	{
		j++;					//j�Ǽ��ͱ�ʾ�ڼ����ڵ� ��j=i-1��ʱ�򻹿�����ѭ��һ�� 
		p = p->next;			//p��ʱҲָ���i���ڵ�
	}
	
	if(p == L || j > i)
		return ERROR;
		
	*e = p->data;				//�ѵ�i���ڵ�����ݴ��� 
	
	return OK;
} 

//���ص���ѭ�������е�һ����e�����ϵcompare()������Ԫ�ص�λ��
int LocateElem_cirList(LNode *L,ElemType e,Status(*compare)(ElemType,ElemType))
{
	int i = 0;					//����λ��,���ݾ����������ֵΪ0��1 
	LinkList p;
	p = L->next;				//pָ���һ���ڵ�
	while(p != L)
	{
		i++;
		if(compare(p->data,e))	//�����ϵ���ϣ��ͷ����� 
			return i;			//����ҵ���һ���棬����λ�� 
			
		p = p->next;
	} 
	
	return 0;
 } 
 
//�ж���Ԫ���Ƿ���ȣ���ͬ����1����ͬ����0
Status cmp(ElemType e1,ElemType e2)
{
	if(e1 == e2)
		return 1;
	else
		return 0;
}

//��ѭ������ǰ��i��λ��ǰ����Ԫ��e
Status Insert_cirList(LNode *L,int i,ElemType e)
{
	LNode *p,*s;
	p = L;
	int j = 0;
	
	if(i <= 0 || i > Length_cirList(L)+1)
		return ERROR;
		
	while(j < i-1)				//������L���ǿձ�ʱ���ҵ�ǰλ��С��i-1 
	{  
		p = p->next;			//�������� 
		j++;
	}							//������ѭ��ʱpָ��ָ���i-1��Ԫ�� 
	
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;				//��Ҫ��������ݸ��� sָ�� 
	s->next = p->next;			//p->nextָ���i��Ԫ�أ��ѵ�i��Ԫ�ص�ǰ���ӵ�Ҫ����ڵ�ĺ��� 
	p->next = s;				//��i-1�ڵ�ĺ����ӵ�Ҫ����Ԫ�ص�ǰ�� 
	if(p == L)
		L = s;
	return OK;
 } 
 
//ɾ����i��Ԫ��
Status Delete_cirList(LNode *L,int i,ElemType *e)
{
	LinkList p,q;
	p = L->next;			//pָ���һ����� 
	int j = 1;				//����j��1��ʼ���� 
	
	if(i <= 0 || i > Length_cirList(L))		//ɾ��λ�ò�������Χ�� 
		return ERROR;
		
	while(j < i-1)							//Ѱ�ҵ�i-1���ڵ� 
	{
		j++;
		p = p->next;
	}
	
	q = p->next;							//qָ���ɾ���Ľڵ㣬p����һ�� 
	p->next = q->next;						//��ɾ���ڵ��ǰ��ָ���ɾ���ڵ�ĺ�� 
	
	*e = q->data;							//�Ѵ�ɾ���ڵ�Ĵ洢ֵ����e���� 
	
	if(q == L)								//ɾ�����Ǳ�β��Ԫ�� 
		L = p;								//Lָ���µı�β�ڵ� 
		
	free(q);								//�ͷŴ�ɾ���ڵ� 
	return OK;
} 
//��ӡ��������е�����
int Printf_cirList(LNode *L)
{
	int i;
	LNode *p;
	
	p = L->next;			//ʹpָ��ָ������ĵ�һ������
	while(p != L)
	{
		printf("%d ",p->data);
		p = p->next;		//ָ����� 
	} 
 } 
 
 
int main()
{
	printf("******************************************************************\n");
	printf("*****        ���嵥��ѭ������    Please enter 'a'          *****\n");
	printf("*****         ���ص���ѭ������ĳ��ȣ�Please enter   'b'     *****\n");
	printf("*****         �������ѭ�������е����ݣ�Please enter 'c'     *****\n");
	printf("*****       �жϵ���ѭ�������Ƿ�Ϊ�գ�Please enter 'd'       *****\n");
	printf("*****       ���ظ���λ�õĽڵ�Ԫ��ֵ��Please enter 'e'       *****\n");
	printf("*****     ���ظ���Ԫ��ֵ�Ľڵ�λ�ã�Please enter 'f'         *****\n");
	printf("*****   ��������ָ��λ��i��֮ǰ���������ݣ�Please enter 'g'  *****\n");
	printf("*****   ɾ����i��Ԫ�أ�����e������ֵ��Please enter 'h'       *****\n");
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
			case 'a':/* ����һ������ѭ������*/
					{
						Inite_cirList(&L);
						printf("�����봴������ĳ��ȣ�  ");
						scanf("%d",&N);
						Create_cirList(&L,N);
						break;
					} 
			case 'b':/* ���ص�������ĳ���*/
					{
						k=Length_cirList(&L);
						printf("������ĳ����ǣ�  %d",k);
						break;
					}
			case 'c':/* ������������е�����*/
					{
						printf("�˵��������е�����Ϊ��\n");
						Printf_cirList(&L);
						break;
					} 
			case 'd':/* �ж������Ƿ�Ϊ��*/
					{
						k=Empty_cirList(&L);
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
						GetElem_cirList(&L,I,&E);
						printf("��  %d  ��Ԫ�ص�ֵΪ��  %d\n",I,E);
						break;
					}
			case 'f':/*���ص���ѭ�������е�һ����e�����ϵcompare()������Ԫ�ص�λ��*/
					{
						printf("��������֪���Ƿ��������е���ֵ��  ");
						scanf("%d",&E);
						k=LocateElem_cirList(&L,E,cmp);
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
						k=Insert_cirList(&L,I,E);
						if(k)
						{
							printf("����������ֵΪ��\n");
							Printf_cirList(&L);
							printf("\n");
						 } 
						 else
						 {
						 	printf("ERROR\n");
						 }
						break; 
					 } 
			case 'h':/*ɾ����i��Ԫ�أ�����e������ֵ*/
					{
						printf("������ɾ��Ԫ�ص�λ�ã�  ");
						scanf("%d",&I);
						k=Delete_cirList(&L,I,&E);
						if(k)
						{
							printf("ɾ����λ�õ�Ԫ��ֵΪ:  %d\n",E);
							printf("ɾ�������Ա�Ϊ:\n");
							Printf_cirList(&L);
							printf("\n");
						}
							break;
					}
			default:printf("wrong!\n");
		}
	}while(str!='q');
 } 
