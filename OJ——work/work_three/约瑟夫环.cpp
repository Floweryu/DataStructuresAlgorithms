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
	while(scanf("%d %d",&m,&r)!=EOF&&r>0)
	{
	
		p=(LinkList*)malloc(sizeof(LinkList));
		p->num=1;
		p->next=NULL;
		head=p;
		q=p;
		
		for(i=2;i<=m;i++)
		{
			p=(LinkList*)malloc(sizeof(LinkList)); 
			p->num=i;
			p->next=NULL;
			q->next=p;
			q=p;
		}
	
		q->next=head;
		p=head;
		while(q->next!=q)
		{
			for(i=1;i<r;i++)
			{
				q=p;
				p=p->next;
			}
			q->next=p->next;
			p=q->next;
		}
		printf("%d\n",p->num);
	}
}
