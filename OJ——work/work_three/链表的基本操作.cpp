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
	ElemType	data;	//数据域 
	struct LNode	*next;	//指针域 
}LNode,*LinkList;

void reCreate_L(LinkList &L,int n)
{
	LNode *p;
	L=(LinkList)malloc(sizeof(LNode));	//申请头结点，把q指针指向头结点，为以后与p结点接替 
		//建立一个带头结点的单链表
	L->next=NULL;
	int i;
	for(i=n;i>0;i--)	
	{
		p=(LinkList)malloc(sizeof(LNode));	//生成新节点
		scanf("%d",&p->data);		//输入数据 
		p->next=L->next;
		L->next=p;
	}
 } 
 
 int Empty_L(LNode *L)
{
	/*当只有一个头结点的时候，该链表就为空*/
	if((L->next)==NULL)		//头结点与NULL相连 
	return OK; 
	else
	return ERROR; 
}

int iGetElem_L(LinkList &L,int i,ElemType *e)
{
	LNode *p;
	p=L->next;		//使p指向头结点 
	int j=1;		//j为计数器 
	while(p&&j<i)	//顺指针向后查找，知道p指向第i个元素或p为空 
	{
		p=p->next;   //遍历链表 
		j++;		//记录遍历的位置和次数 
	}
	if(!p||j>i)
		return ERROR;
	*e=p->data;		//退出while()循环时p的指针已经指到下一个元素地址 
	return OK; 
}

int Insert_L(LinkList &L,int i,ElemType *e)
{
	LNode *p,*s;
	p=L;
	int j=0;
	while(p&&j<i-1)		//当链表L不是空表时并且当前位置小于i-1 
	{  //要找到第i-1个节点的位置就要在第i-2个节点处停止循环，因为循环体内是先移动指针后加一，指针比j先到i-1； 
		p=p->next;		//遍历链表 
		j++;
	}			//当跳出循环时p指针指向第i-1个元素 
	if(!p||j>i-1)
	return ERROR;
	s=(LinkList)malloc(sizeof(LNode));
	s->data=*e;		//把要插入的数据赋给 s指针 
	s->next=p->next;	//p->next指向第i个元素，把第i个元素的前驱接到要插入节点的后驱 
	p->next=s;		//第i-1节点的后驱接到要插入元素的前驱 
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
	}		//跳出循环时p指向第i-1个节点 
	if(!p->next||j>i-1)
	return ERROR;
	s=p->next;   //s指针指向第i个节点 
	p->next=s->next;//第i-1个节点的后驱与第i个节点后驱（即第i+1个节点的前驱） 
	*e=s->data;	//把第i个节点的值赋给e传回 
	free(s);	//释放第i个节点的空间 
	return OK;
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
		if(!strcmp(str,"show"))		//输出 
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
		else if(!strcmp(str,"delete"))	//删除 
		{
			scanf("%d",&a);
			back=Delete_L(L,a,&E);
			if(back)
			printf("delete OK\n");
			else
			printf("delete fail\n");
		}
		else if(!strcmp(str,"insert"))	//插入 
		{
			scanf("%d %d",&a,&E);
			back=Insert_L(L,a,&E);
			if(back)
			printf("insert OK\n");
			else
			printf("insert fail\n");
		}
		else if(!strcmp(str,"get"))		//查找 
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
