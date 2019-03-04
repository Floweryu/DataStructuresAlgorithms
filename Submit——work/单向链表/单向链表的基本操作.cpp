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
	ElemType	data;	//数据域 
	struct LNode	*next;	//指针域 
}LNode,*LinkList;

//初始化链表 
void Init_List(LNode *L)
{
	L=(LinkList)malloc(sizeof(LNode));
	if(!L)
		exit(OVERFLOW);
	L->next=NULL;
 } 
//链表的创建；正向建立	
int Create_List(LNode *L,int n)
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
int reCreate_List(LNode *L,int n)
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
int Printf_List(LNode *L)
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
int Length_List(LNode *L)
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
int Empty_List(LNode *L)
{
	/*当只有一个头结点的时候，该链表就为空*/
	if((L->next)==NULL)		//头结点与NULL相连 
	return OK; 
	else
	return ERROR; 
}

//当第i个元素存在时，将其值赋给e并返回OK
int iGetElem_List(LNode *L,int i,ElemType &e)
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
	e=p->data;		//退出while()循环时p的指针已经指到下一个元素地址 
	return OK; 
}

//按值查找寻找元素e，返回e的位置
int eGetElem_List(LNode *L,ElemType &e)
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
int Insert_List(LNode *L,int i,ElemType e)
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
	s->data=e;		//把要插入的数据赋给 s指针 
	s->next=p->next;	//p->next指向第i个元素，把第i个元素的前驱接到要插入节点的后驱 
	p->next=s;		//第i-1节点的后驱接到要插入元素的前驱 
	return OK;
 } 
 
//删除第i个元素，并由e返回其值。
//其中包含删除的节点是表头、在中间
int Delete_List(LNode *L,int i,ElemType &e)
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
	e=s->data;	//把第i个节点的值赋给e传回 
	free(s);	//释放第i个节点的空间 
	return OK;
}

//删除有序单向链表中的重复元素	
int reDelete_List(LNode *L)
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
int rePrintf_List(LNode *L)
 {
 	LNode *p,*s,*q;
 	LinkList L0;		/*定义一个新的链表用来存储反转后的数据*/ 
 	L0=(LinkList)malloc(sizeof(LNode));
 	p=L->next;		/*p指向原链表的下一个*/ 
 	L0->next=NULL;	/*新链表进行初始化*/ 
 	while(p!=NULL)	/*指针没到空集时循环*/ 
 	{
 		q=(LinkList)malloc(sizeof(LNode));/*申请一个新节点用来存储反转元素*/ 
 		q->data=p->data;	/*把原来L链表的数据按从头结点到尾的顺序赋给新链表L0节点q。*/ 
 		q->next=L0->next;	/*把新节点用尾插法，从新链表L0的后面开始存储*/ 
 		L0->next=q;		
 		p=p->next;	/*遍历原链表L*/ 
 	}
 	s=L0->next;		/*对新链表L0进行输出*/ 
	while(s!=NULL)
	{
		printf("%d ",s->data);
		s=s->next;		//指针后移 
	} 
 }

int main()
{
	printf("******************************************************************\n");
	printf("*****        正向创建一个单向链表，Please enter 'a'          *****\n");
	printf("*****         返回单向链表的长度，Please enter   'b'         *****\n");
	printf("*****         输出单向链表中的数据，Please enter 'c'         *****\n");
	printf("*****       判断链表是否为空，Please enter 'd'               *****\n");
	printf("*****       返回给定位置的节点元素值，Please enter 'e'       *****\n");
	printf("*****     返回给定元素值的节点位置，Please enter 'f'         *****\n");
	printf("*****   在链表中指定位置i在之前处插入数据，Please enter 'g'  *****\n");
	printf("*****   删除第i个元素，并由e返回其值，Please enter 'h'       *****\n");
	printf("*****        逆向创建一个单向链表，Please enter 'i'          *****\n");
	printf("*****       删除有序单向链表中的重复元素，Please enter 'j'   *****\n");
	printf("*****      对单链表进行逆序输出,  Please enter 'k'           *****\n");
	printf("******************************************************************\n");
	LNode L;
	char str;
	int N,I,k;
	ElemType E; 
	do
	{
		printf("\n");
		printf("Please enter a char:    ");
		str=getche();/*从键盘获取一个字符并显示，不按回车直接执行*/ 
		printf("\n");/*	getchar();	/*接收上条语句的回车键，否则回车键也会被认为是字符*/ 
		switch(str)
		{
			case 'a':/* 正向创建一个单向链表*/
					{
						Init_List(&L);
						printf("请输入创建链表的长度：  ");
						scanf("%d",&N);
						Create_List(&L,N);
						break;
					} 
			case 'b':/* 返回单向链表的长度*/
					{
						k=Length_List(&L);
						printf("该链表的长度是：  %d",k);
						break;
					}
			case 'c':/* 输出单向链表中的数据*/
					{
						printf("此单向链表中的数据为：\n");
						Printf_List(&L);
						break;
					} 
			case 'd':/* 判断链表是否为空*/
					{
						k=Empty_List(&L);
						if(k)
						printf("这是一个空的链表。\n");
						else
						printf("这不是一个空的链表。\n");
						break;
					}
			case 'e':/* 返回给定位置的节点元素值*/
					{
						printf("你想知道第几个元素：   ");
						scanf("%d",&I);
						iGetElem_List(&L,I,E);
						printf("第  %d  个元素的值为：  %d\n",I,E);
						break;
					}
			case 'f':/*返回给定元素值的节点位置*/
					{
						printf("输入你想知道是否在链表中的数值：  ");
						scanf("%d",&E);
						k=eGetElem_List(&L,E);
						if(k)
							printf("值为  %d  是表中的第  %d  个元素\n",E,k);
						else
							printf("此链表中没有值为%d的元素\n",E);
						break;
					 } 
			case 'g':/*在链表中指定位置i在之前处插入数据*/
					{
						printf("请输入插入元素的位置：  ");
						scanf("%d",&I);
						printf("请输入插入元素的值：  ");
						scanf("%d",&E);
						k=Insert_List(&L,I,E);
						if(k)
						{
							printf("插入后链表的值为：\n");
							Printf_List(&L);
							printf("\n");
						 } 
						break; 
					 } 
			case 'h':/*删除第i个元素，并由e返回其值*/
					{
						printf("请输入删除元素的位置：  ");
						scanf("%d",&I);
						k=Delete_List(&L,I,E);
						if(k)
						{
							printf("删除该位置的元素值为:  %d\n",E);
							printf("删除后线性表为:\n");
							Printf_List(&L);
							printf("\n");
						}
							break;
					}
			case 'i':/* 逆向创建一个单向链表*/
					{
						printf("请输入创建链表的长度：  ");
						scanf("%d",&N);
						reCreate_List(&L,N);
						break;
					} 
			case 'j':/*删除有序单向链表中的重复元素*/
					{
						reDelete_List(&L);
						break;
					}
			case 'k':/*对单链表进行逆序输出*/
					{
						rePrintf_List(&L);
						break;
					}
			default:printf("wrong!\n");
		}
	}while(str!='q');
}
