#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;

typedef struct DuLNode
{
	ElemType data;				//�洢Ԫ��ֵ 
	DuLNode *prior,*next;		// prior Ϊ�ڵ��ǰ����next Ϊ�ڵ�ĺ�� 
}DuLNode,*DuLinkList;			// DuLNode ����ṹ�壬DuLinkList ����ṹ��ָ�� 

//��ʼ������һ���յ�˫��ѭ������
Status DuInit_List(DuLNode *L)
{
	L = (DuLinkList) malloc (sizeof(DuLNode));	//����L�ڵ�ռ� 
	if(L)	
	{	
		L->next = L->prior=L;					//L�ĺ�̺�ǰ�����Ӳ�������L 
		return OK;
	}
	else
		exit(OVERFLOW);						//L�ڵ�ռ�û������ɹ� 
}

//��˫��ѭ����������������
Status DuCreate_List(DuLNode *L, int *n)
{
	DuLinkList p, q;			//q��������p 
	int i;
	
	q = L;						//qָ��L�ڵ� 
	for(i = 0; i < *n; i++)
	{
		p = (DuLinkList) malloc (sizeof(DuLNode));	//����洢�ռ� 
		if(!p)		   			//�ж��Ƿ�����ɹ� 
			exit(ERROR);
			
		scanf("%d", &p->data);	//�������� 
		
		p->next = NULL;			//p�ĺ��ָ��NULL 
		p->prior = q;			//p��ǰ��ָ��q 
		q->next = p;			//q�ĺ��ָ��p 
		L->prior = p;			//L��ǰ��ָ��p��ÿ�β���һ����㣬����ָ��L��ǰ������L������ 
		q = p; 					//����pָ�� 
	}							//������ɺ�Ҫ�γ�˫��ѭ������ 
	
	q->next = L;				//���һ�����ĺ��ָ��L 
	L->prior = q;				//L��ǰ��ָ�������� 
 } 
//��L����Ϊ�ձ�
Status DuClear_List(DuLNode *L)
{
	DuLinkList p=L->next;			//pָ���һ�����
	
	while(p != L)
	{
		p = p->next;				//pָ����һ�����
		free(p->prior); 			//�ͷ�p��ǰ����� 
	} 
	
	L->next = L->prior = L;		 	//ͷ��������ָ�����ָ������ 
	
	return OK;
}

//����˫������L 
Status DuDestroy_List(DuLNode *L)
{
	DuClear_List(L);	//��L��Ϊ�ձ�
	free(L); 			//�ͷ�ͷ���
	L = NULL; 
	
	return OK;
}

//�ж�L�Ƿ�Ϊ�ձ�
Status DuEmpty_List(DuLNode *L)
{
	if(L->next == L && L->prior == L)	//��˫��ѭ��������һ��������ľ���һ���ձ� 
		return TRUE;
	else
		return FALSE;
}

//����L������Ԫ�صĸ���
int DuLength_List(DuLNode *L)
{
	int i = 0;
	DuLinkList p = L->next;		//ָ���һ����� 
	
	while(p != L)				//pδָ��ͷ��� 
	{
		i++;					//p�Ѿ�ָ��һ����㣬�����ȼ�һ 
		p = p->next;
	}
	
	return i;
 } 

//���ص�i��Ԫ�ص�ֵ
Status DuGetElem_List(DuLNode *L, int i, ElemType *e) 
{
	int j=1;
	DuLinkList p = L->next;		//pָ���һ�����
	
	while(p != L&&j<i)			//ʹpָ���i����� 
	{
		j++;					//��������һ 
		p = p->next;	
	}
	
	if(p == L||j>i)
		return ERROR;
		
	*e = p->data;					//����i���ڵ��ֵ����e���� 
	
	return OK; 
}

//���ص�һ����eԪ�������ϵ��Ԫ�ص�λ��
int DuLocateElem_List(DuLNode *L,ElemType e,Status(*compare)(ElemType,ElemType)) 
{
	int i = 0;					//��������ֵΪ0 
	DuLinkList p = L->next;		//pָ���һ����� 
	
	while(p != L)				//��p��ָ��ͷ���ʱѭ�� 
	{
		i++;					//��������һ 
		if(compare(p->data,e))	//�ҵ�����Ҫ���Ԫ�أ������ǡ���� 
			return i;			//��������λ�� 
			
		p = p->next;				//pָ����һ���ڵ� 
	}
	
	return 0;
}

//�ж���Ԫ���Ƿ���ȣ���ͬ����1����ͬ����0
Status cmp(ElemType e1,ElemType e2)
{
	if(e1 == e2)			//������	 
		return 1;
	else
		return 0;
}

//���ص�i��Ԫ�صĵ�ַ
DuLinkList DuGetElem_P(DuLNode *L,int i)
{
	int j;
	DuLinkList p = L;					//pָ��ͷ��� 
	
	if(i < 0 || i > DuLength_List(L))	//�ж�i�Ƿ����Ҫ�� 
		return ERROR;
		
	for(j = 1; j <= i; j++)				//ʹpָ���i���ڵ� 
		p = p->next;					//pָ����һ�� 
		
	return p;							//�ҵ�Ŀ��ڵ㣬�������ĵ�ַ 
 } 
//�ڵ�i��Ԫ��ǰ����Ԫ��e
Status DuInsert_List(DuLNode *L,int i,ElemType *e)
{
	DuLinkList p,s;						//pָ������������sָ���������½ڵ� 
	
	if(i < 1 || i > DuLength_List(L)+1)	//�жϲ���λ���Ƿ���� 
		return ERROR;
		
	p = DuGetElem_P(L, i-1);			//�õ���i-1�����ĵ�ַ 
	
	if(!p)								//�жϵ�i-1������Ƿ�Ϊ�� 
		return ERROR;
		
	s = (DuLinkList)malloc(sizeof(DuLNode));	//����һ���½ڵ� 
	
	if(!s)	//�ж��½ڵ��Ƿ�ɹ� 
		exit(OVERFLOW);
		
	s->data = *e;							//�� e�����½ڵ� 
	
	s->prior = p;							//s��ǰ��ָ���i-1���ڵ� 
	s->next = p->next;						//s�ĺ��ָ���i���ڵ� 
	p->next->prior = s;						//��i���ڵ��ǰ��ָ���½ڵ� 
	p->next = s;								//��i-1���ڵ���ָ���½ڵ� 
	
	return OK; 
 } 
 
 //ɾ����i��λ�õ�Ԫ��
 Status DuDelete_List(DuLNode *L,int i,ElemType *e)
 {
 	DuLinkList p;
 			
 	if(i < 1)					//�ж�λ���Ƿ�Ϸ� 
 		return ERROR;
 		
 	p=DuGetElem_P(L, i);		//�õ���i��Ԫ�ص�λ��
 	
	if(!p)						//�жϵõ��Ľ���Ƿ�Ϊ�� 
		return ERROR;
		
	*e = p->data;				//��ɾ����ԭ��ֵ���� 
	p->prior->next = p->next;		//��i-1���ڵ�ĺ�����ӵ���i+1���ڵ� 
	p->next->prior = p->prior;	//��i+1���ڵ��ǰ�����ӵ���i-1���ڵ�ĺ�� 
	free(p);					//�ͷŵ�i���ڵ� 
	
	return OK; 
} 

//�������
void DuPrintf_List(DuLNode *L)
{
	DuLinkList p;
	
	p = L->next;				//pָ���һ����� 
	while(p != L)				//pδ����ͷʱѭ�� 
	{
		printf("%d ",p->data);
		p = p->next;			//pָ����һ���ڵ� ��p��ǰ�������� 
	}
	printf("\n");
} 

//�������
void DurePrintf_List(DuLNode *L)
{
	DuLinkList p;	
	
	p = L->prior;				//pָ�����һ����� 
	while(p !=	L)				//pΪ����ͷʱѭ�� 
	{
		printf("%d ",p->data);
		p = p->prior;			//pָ����һ���ڵ� ��p�Ӻ���ǰ������ 
	}
	printf("\n");
 } 
 
 int main()
 {
 	printf("***** ��ʼ������һ���յ�˫��ѭ������,   enter   'a'  *****\n");
 	printf("*****           ��L����Ϊ�ձ�,          enter   'b'  *****\n");
 	printf("*****         ����˫������L             enter   'c'  *****\n");
 	printf("*****          �ж�L�Ƿ�Ϊ�ձ�          enter   'd'  *****\n");
 	printf("*****          ����L������Ԫ�صĸ���    enter   'e'  *****\n");
 	printf("*****         ���ص�i��Ԫ�ص�ֵ         enter   'f'  *****\n");
 	printf("*****���ص�һ����eԪ�������ϵ��Ԫ�ص�λ��,enter  'g'  *****\n");
 	printf("*****        �ڵ�i��Ԫ��ǰ����Ԫ��e     enter   'h'  *****\n");
 	printf("*****      ɾ����i��λ�õ�Ԫ��          enter   'i'  *****\n");
 	printf("*****            �������               enter   'j'  *****\n");
 	printf("*****            �������               enter   'k'  *****\n");
 	printf("*****     ��˫��ѭ����������������      enter   'l'  *****\n");
 	DuLNode L;
 	char str;
 	int back;
 	ElemType E,I,N;
 	do
 	{
 		printf("\n");
		printf("Please enter a char:    ");
		str=getche();/*�Ӽ��̻�ȡһ���ַ�����ʾ�������س�ֱ��ִ��*/ 
		printf("\n");/*	getchar();	/*�����������Ļس���������س���Ҳ�ᱻ��Ϊ���ַ�*/ 
		switch(str)
		{ 
			case 'a'://��ʼ������һ���յ�˫��ѭ������
			{
				back=DuInit_List(&L);
				if(back)
					printf("˫��ѭ�������ʼ���ɹ���\n");
				else
					printf("˫��ѭ�������ʼ��ʧ�ܡ�\n");
				break;
			}
			case 'b'://��L����Ϊ�ձ�
			{
				back=DuClear_List(&L);
				if(back)
					printf("���˫��ѭ������ɹ���\n");
				else
					printf("�������ʧ�ܡ�\n");
				break;
			}
			case 'c'://����˫������L 
			{
				back=DuDestroy_List(&L);
				if(back)
					printf("��������ɹ���\n");
				else
					printf("��������ʧ�ܡ�\n");
				break;
			}
			case 'd'://�ж�L�Ƿ�Ϊ�ձ�
			{
				back=DuEmpty_List(&L);
				if(back)
					printf("����һ���յ�����\n");
				else
					printf("�ⲻ��һ��������\n");
				break;
			}
			case 'e'://����L������Ԫ�صĸ���
			{
				back=DuLength_List(&L);
				printf("����ĳ����ǣ�   %d\n",back);
				break;
			}
			case 'f'://���ص�i��Ԫ�ص�ֵ  
			{
				printf("����������֪��Ԫ�ص�λ�ã�   ");
				scanf("%d",&I);
				DuGetElem_List(&L,I,&E);
				printf("�� %d ��λ�õ�Ԫ����:   %d\n",I,E);
				break;
			}
			case 'g'://���ص�һ����eԪ�������ϵ��Ԫ�ص�λ��
			{
				printf("������Ԫ�أ�    ");
				scanf("%d",&E);
				back=DuLocateElem_List(&L,E,cmp);
				printf("��Ԫ���������е�λ���ǣ�   %d\n",back);
				break;
			}
			case 'h'://�ڵ�i��Ԫ��ǰ����Ԫ��e
			{
				printf("���������Ԫ�ص�λ�ã�  ");
				scanf("%d",&I);
				printf("���������Ԫ�ص�ֵ��  ");
				scanf("%d",&E);
				back=DuInsert_List(&L,I,&E);
				if(back)
				{
					printf("����������ֵΪ��\n");
					DuPrintf_List(&L);
					printf("\n");
				} 
				break; 	
			}
			case 'i'://ɾ����i��λ�õ�Ԫ�� 
			{
				printf("������ɾ��Ԫ�ص�λ�ã�  ");
				scanf("%d",&I);
				back=DuDelete_List(&L,I,&E);
				if(back)
				{
					printf("ɾ����λ�õ�Ԫ��ֵΪ:  %d\n",E);
					printf("ɾ�������Ա�Ϊ:\n");
					DuPrintf_List(&L);
					printf("\n");
				}
				break;
			}
			case 'j'://�������
			{
				DuPrintf_List(&L);
				break;
			}
			case 'k'://�������
			{
				DurePrintf_List(&L);
				break;
			}
			case 'l'://��˫��ѭ����������������
			{
				printf("�����봴������ĳ��ȣ�  ");
				scanf("%d",&N);
				DuCreate_List(&L,&N);
				break;
			}
			default:printf("wrong!\n");
		}
	 }while(str!='q');
	 return 0;
  } 
