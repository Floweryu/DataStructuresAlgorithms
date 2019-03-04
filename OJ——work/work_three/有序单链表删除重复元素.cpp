#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int ElemType;

typedef struct LNode{
	ElemType	data;	//数据域 
	struct LNode	*next;	//指针域 
}LNode,*LinkList;

/*函数名： Create_L()
  功能：链表的创建；正向建立	*/	
int Create_L(LinkList &L,int n)
{
	LNode *p,*q;
	L=q=(LinkList)malloc(sizeof(LNode));	//申请头结点，把q指针指向头结点，为以后与p结点接替 
		//建立一个带头结点的单链表 
	int i;
	for(i=0;i<n;i++)	
	{
		p=(LinkList)malloc(sizeof(LNode));	//生成新节点
		scanf("%d",&p->data);		//输入数据 
		//下面三行代码相当于把p结点插入到链表中，且是从头到尾的顺序插入 
		p->next=NULL;		//p结点的下一个地址指向NULL,申请新节点的指针p的下一个地址永远指向NULL 
		q->next=p;			//q的下一个地址指向p，即指针p的前驱要与上一个元素的后驱链接 
		q=p;		//把当前已插入的节点地址赋给q，以便接下来的遍历 
	}
 }
 
 /*函数名：reDelete_L 
 	功能：删除有序单向链表中的重复元素	*/
int reDelete_L(LinkList &L)
{
	LNode *p,*s,*q;
	p=L->next;
	q=p->next;
	while(q!=NULL)
	{
		if(p->data==q->data)
		{
			p->next=q->next;
			s=q;
			q=q->next;
			free(s);
		}
		else
		{
			p=p->next;
			q=q->next;
		}
	}
 } 
 
 int Printf_L(LinkList &L)
{
	LNode *p;
	p=L->next;		//使p指针指向链表的第一个数据
	while(p!=NULL)
	{
		printf("%d ",p->data);
		p=p->next;		//指针后移 
	} 
	printf("\n");
 } 
 
 int main()
 {
 	LinkList La;
 	int N;
 	while(scanf("%d",&N)!=EOF)
 	{
 		if(!N)
 		printf("list is empty\n");
 		else
 		{
 			Create_L(La,N);
 			Printf_L(La);
 			reDelete_L(La);
 			Printf_L(La);
 		}
 	}
 }
