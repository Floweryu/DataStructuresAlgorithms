#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int ElemType;

typedef struct LNode{
	ElemType	data;	//������ 
	struct LNode	*next;	//ָ���� 
}LNode,*LinkList;

void reCreate_L(LinkList &L,int n)
{
	LNode *p;
	L=(LinkList)malloc(sizeof(LNode));	//����ͷ��㣬��qָ��ָ��ͷ��㣬Ϊ�Ժ���p������ 
		//����һ����ͷ���ĵ�����
	L->next=NULL;
	int i;
	for(i=n;i>0;i--)	
	{
		p=(LinkList)malloc(sizeof(LNode));	//�����½ڵ�
		scanf("%d",&p->data);		//�������� 
		p->next=L->next;
		L->next=p;
	}
 } 
 
 int Empty_L(LNode *L)
{
	/*��ֻ��һ��ͷ����ʱ�򣬸������Ϊ��*/
	if((L->next)==NULL)		//ͷ�����NULL���� 
	return OK; 
	else
	return ERROR; 
}

int iGetElem_L(LinkList &L,int i,ElemType *e)
{
	LNode *p;
	p=L->next;		//ʹpָ��ͷ��� 
	int j=1;		//jΪ������ 
	while(p&&j<i)	//˳ָ�������ң�֪��pָ���i��Ԫ�ػ�pΪ�� 
	{
		p=p->next;   //�������� 
		j++;		//��¼������λ�úʹ��� 
	}
	if(!p||j>i)
		return ERROR;
	*e=p->data;		//�˳�while()ѭ��ʱp��ָ���Ѿ�ָ����һ��Ԫ�ص�ַ 
	return OK; 
}

int Insert_L(LinkList &L,int i,ElemType *e)
{
	LNode *p,*s;
	p=L;
	int j=0;
	while(p&&j<i-1)		//������L���ǿձ�ʱ���ҵ�ǰλ��С��i-1 
	{  //Ҫ�ҵ���i-1���ڵ��λ�þ�Ҫ�ڵ�i-2���ڵ㴦ֹͣѭ������Ϊѭ�����������ƶ�ָ����һ��ָ���j�ȵ�i-1�� 
		p=p->next;		//�������� 
		j++;
	}			//������ѭ��ʱpָ��ָ���i-1��Ԫ�� 
	if(!p||j>i-1)
	return ERROR;
	s=(LinkList)malloc(sizeof(LNode));
	s->data=*e;		//��Ҫ��������ݸ��� sָ�� 
	s->next=p->next;	//p->nextָ���i��Ԫ�أ��ѵ�i��Ԫ�ص�ǰ���ӵ�Ҫ����ڵ�ĺ��� 
	p->next=s;		//��i-1�ڵ�ĺ����ӵ�Ҫ����Ԫ�ص�ǰ�� 
	return OK;
 } 
 int Delete_L(LinkList L,int i,ElemType *e)
{
	LNode *p,*s;
	int j=0;
	p=L;
	while(p->next&&j<i-1)
	{
		p=p->next;
		j++;
	}		//����ѭ��ʱpָ���i-1���ڵ� 
	if(!p->next||j>i-1)
	return ERROR;
	s=p->next;   //sָ��ָ���i���ڵ� 
	p->next=s->next;//��i-1���ڵ�ĺ������i���ڵ����������i+1���ڵ��ǰ���� 
	*e=s->data;	//�ѵ�i���ڵ��ֵ����e���� 
	free(s);	//�ͷŵ�i���ڵ�Ŀռ� 
	return OK;
}

 
 int Printf_L(LinkList &L)
{
	LNode *p;
	p=L->next;		//ʹpָ��ָ������ĵ�һ������
	while(p!=NULL)
	{
		printf("%d ",p->data);
		p=p->next;		//ָ����� 
	} 
 } 
 
int main()
{
	int N,M,i,a,back;
	ElemType E;
	char str[30];
	LinkList L;
	scanf("%d",&N);
	reCreate_L(L,N);
	scanf("%d",&M);
	while(M--)
	{
		scanf("%s",str); 
		if(!strcmp(str,"show"))		//��� 
		{
			back=Empty_L(L);
			if(back)
			printf("Link list is empty\n");
			else
			{	
				Printf_L(L);
				printf("\n");
			}	
		}
		else if(!strcmp(str,"delete"))	//ɾ�� 
		{
			scanf("%d",&a);
			back=Delete_L(L,a,&E);
			if(back)
			printf("delete OK\n");
			else
			printf("delete fail\n");
		}
		else if(!strcmp(str,"insert"))	//���� 
		{
			scanf("%d %d",&a,&E);
			back=Insert_L(L,a,&E);
			if(back)
			printf("insert OK\n");
			else
			printf("insert fail\n");
		}
		else if(!strcmp(str,"get"))		//���� 
		{
			scanf("%d",&a);
			back=iGetElem_L(L,a,&E);
			if(back)
			printf("%d\n",E);
			else
			printf("get fail\n");
		}
	}
 } 
