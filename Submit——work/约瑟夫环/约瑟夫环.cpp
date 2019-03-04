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
	while(scanf("%d %d",&m,&r)!=EOF&&r>0)	//多组输入数据 
	{
	
		p=(LinkList*)malloc(sizeof(LinkList));	//申请一个结点 
		p->num=1;	//约瑟夫环的额第一个值是1 
		p->next=NULL;	//插入到链表中 
		head=p;		//
		q=p;	//跟随已用过的节点，新节点的上一个 
		
		for(i=2;i<=m;i++)	//从2开始输入数据 
		{
			p=(LinkList*)malloc(sizeof(LinkList)); 
			p->num=i;
			p->next=NULL;	//插在上一个节点的后面 
			q->next=p;
			q=p;
		}
	
		q->next=head;	//最后把最后一个节点的指针指向头结点 ，形成循环链表 
		p=head;			//	p指向头结点 
		while(q->next!=q)	//当没有返回到初始时循环 
		{
			for(i=1;i<r;i++)
			{
				q=p;	//p节点赋给q 
				p=p->next;	//遍历寻找第r个节点 
			}
			q->next=p->next;	//把第r+1个节点前驱连接到第i-1个节点的后继，就是删除dir个元素 
			p=q->next;	//p指向待删除节点的下一个 
		}
		printf("%d\n",p->num);	//输出最后一个元素值 
	}
}
