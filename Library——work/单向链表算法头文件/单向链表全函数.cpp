#include "stdio.h"
#include "stdlib.h"
#include "conio.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int ElemType;

typedef struct LNode{
	ElemType	data;	//数据域 
	struct LNode	*next;	//指针域 
}LNode,*LinkList;

//初始化链表 
void InitList(LNode *L)
{
	L=(LinkList)malloc(sizeof(LNode));
	if(!L)
		exit(OVERFLOW);
	L->next=NULL;
 } 
//链表的创建；正向建立	
int Create_L(LNode *L,int n)
{
	LNode *p,*q;
	q=L;
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
 
//逆序创建一个单链表 
int reCreate_L(LNode *L,int n)
{
	LNode *p;
	L=(LinkList)malloc(sizeof(LNode));	//申请头结点，把q指针指向头结点，为以后与p结点接替 
		//建立一个带头结点的单链表
	L->next=NULL;
	int i;
	for(i=0;i<n;i++)	
	{
		p=(LinkList)malloc(sizeof(LNode));	//生成新节点
		scanf("%d",&p->data);		//输入数据 
		p->next=L->next;
		L->next=p;
	}
 } 
 
//打印输出链表中的数据
int Printf_L(LNode *L)
{
	LNode *p;
	p=L->next;		//使p指针指向链表的第一个数据
	while(p!=NULL)
	{
		printf("%d ",p->data);
		p=p->next;		//指针后移 
	} 
 } 
 
//返回链表的长度
int Length_L(LNode *L)
{
	LNode *p;		//定义一个指针变量 
	int len=0;		//定义一个计数器，计算节点的个数 
	p=L->next;		//指针p指向链表的第一个节点 
	while(p!=NULL)
	{	
		len++;		//先加一，再移动指针，这样能在p指针指到空集时及时跳出循环从而不会多加上一 
		p=p->next;	//指针后移 
	}
	return len;		//返回链表长度 	
 } 
 
//判断链表是否为空；空就返回1
int Empty_L(LNode *L)
{
	/*当只有一个头结点的时候，该链表就为空*/
	if((L->next)==NULL)		//头结点与NULL相连 
	return OK; 
	else
	return ERROR; 
}

//当第i个元素存在时，将其值赋给e并返回OK
int iGetElem_L(LNode *L,int i,ElemType *e)
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

//按值查找寻找元素e，返回e的位置
int eGetElem_L(LNode *L,ElemType e)
{
	LNode *p;
	p=L->next;		//p连接头结点 
	int count=0;
	while(p!=NULL)
	{
		count++;	//位置先加一，避免跳出循环后多一 
		if(p->data==e)	//判断 
		return (count);		//返回位置值 
		p=p->next;		//p指向下一个结点 
	}
	return ERROR;
 } 
 

//在链表中指定位置i在之前处插入数据
//其中包含在表头插入、在表尾插入、在表中插入三个位置
int Insert_L(LNode *L,int i,ElemType *e)
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
 
//删除第i个元素，并由e返回其值。
//其中包含删除的节点是表头、在中间
int Delete_L(LNode *L,int i,ElemType *e)
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

//删除有序单向链表中的重复元素	
int reDelete_L(LNode *L)
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

//对单链表进行逆序输出 
/*主要思想：把原链表的数据从头到尾通过逆序建立链表法（从后插入）插入到新链表中，
			(相当于逆序建立链表),然后再输出新链表*/ 
int rePrintf_L(LNode *L,int n)
 {
 	LNode *p,*s,*q;
 	LinkList L0;		/*定义一个新的链表用来存储反转后的数据*/ 
 	L0=(LinkList)malloc(sizeof(LNode));
 	p=L->next;		/*p指向原链表的下一个*/ 
 	L0->next==NULL;	/*新链表进行初始化*/ 
 	while(p!=NULL)	/*指针没到空集时循环*/ 
 	{
 		q=(LinkList)malloc(sizeof(LNode));/*申请一个新节点用来存储反转元素*/ 
 		q->data=p->data;	/*把原来L链表的数据按从头结点到尾的顺序赋给新链表L0节点q。*/ 
 		q->next=L0->next;	/*把新节点用尾插法，从新链表L0的后面开始存储*/ 
 		L0->next=q;		
 		p=p->next;	/*遍历原链表L*/ 
 	}
 	s=L0->next;		/*对新链表L0进行输出*/ 
 	for(int i=0;i<n;i++)	/*若是用while(p!=NULL)来输出会陷入循环(没有限制)输出错误值，目前不知道怎么改*/ 
 	{
 		printf("%d ",s->data);
 		s=s->next;
	 }
	 printf("\n");
 }


