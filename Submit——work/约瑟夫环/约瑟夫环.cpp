#include<stdio.h>
#include<stdlib.h>

typedef struct list
{
	int num;
	struct list *next;
}LinkList;

int main()
{
	LinkList *head=NULL,*p,*q;
	int i,j,k,m,r;
	while(scanf("%d %d",&m,&r)!=EOF&&r>0)	//������������ 
	{
	
		p=(LinkList*)malloc(sizeof(LinkList));	//����һ����� 
		p->num=1;	//Լɪ�򻷵Ķ��һ��ֵ��1 
		p->next=NULL;	//���뵽������ 
		head=p;		//
		q=p;	//�������ù��Ľڵ㣬�½ڵ����һ�� 
		
		for(i=2;i<=m;i++)	//��2��ʼ�������� 
		{
			p=(LinkList*)malloc(sizeof(LinkList)); 
			p->num=i;
			p->next=NULL;	//������һ���ڵ�ĺ��� 
			q->next=p;
			q=p;
		}
	
		q->next=head;	//�������һ���ڵ��ָ��ָ��ͷ��� ���γ�ѭ������ 
		p=head;			//	pָ��ͷ��� 
		while(q->next!=q)	//��û�з��ص���ʼʱѭ�� 
		{
			for(i=1;i<r;i++)
			{
				q=p;	//p�ڵ㸳��q 
				p=p->next;	//����Ѱ�ҵ�r���ڵ� 
			}
			q->next=p->next;	//�ѵ�r+1���ڵ�ǰ�����ӵ���i-1���ڵ�ĺ�̣�����ɾ��dir��Ԫ�� 
			p=q->next;	//pָ���ɾ���ڵ����һ�� 
		}
		printf("%d\n",p->num);	//������һ��Ԫ��ֵ 
	}
}
