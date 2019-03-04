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
	ElemType	data;				//数据域
	struct LNode	*next;			//指针域
}LNode,*LinkList;

//初始化链表
void Init_List(LNode *L)
{
	L = (LinkList) malloc (sizeof (LNode));		//申请头结点空间

	if( ! L)									//判断空间是否申请成功
		exit(OVERFLOW);

	L->next = NULL;								//头结点后继指向空
}


//链表的创建；尾插法
int Create_List(LNode *L, int n)
{
	LNode *p, *q;									//定义 p , q 指针
	int i;											//定义计数器 i

	q = L;											//让 q 指针指向头结点
	for(i = 0; i < n; i++)
	{
		p = (LinkList) malloc (sizeof(LNode));		//生成新节点
		scanf("%d", &p->data);						//输入数据
		//下面三行代码相当于把p结点插入到链表中，且是从头到尾的顺序插入
		p->next = NULL;								//p结点的下一个地址指向NULL,申请新节点的指针p的下一个地址永远指向NULL
		q->next = p;								//q的下一个地址指向p，即指针p的前驱要与上一个元素的后驱链接
		q = p;										//把当前已插入的节点地址赋给q，以便接下来的遍历
	}
 }

//逆序创建一个单链表（头查法）
int reCreate_List(LNode *L,int n)
{
	LNode *p;										//定义 p 指针
	int i;											//定义计数器

	for(i = 0; i < n; i++)
	{
		p = (LinkList) malloc (sizeof(LNode));		//生成新节点
		scanf("%d", &p->data);				 		//输入数据

		p->next = L->next;							//将 p 节点从链表尾部查入
		L->next = p;
	}
}

//打印输出链表中的数据
int Printf_List(LNode *L)
{
	LNode *p;

	p = L->next;				//使p指针指向链表的第一个数据
	while(p != NULL)
	{
		printf("%d ",p->data);	//输出元素
		p = p->next;				//指针后移
	}
 }

//返回链表的长度
int Length_List(LNode *L)
{
	LNode *p;			//定义一个指针变量
	int len = 0;		//定义一个计数器，计算节点的个数

	p = L->next;		//指针p指向链表的第一个节点
	while(p != NULL)
	{
		len++;			//先加一，再移动指针，这样能在p指针指到空集时及时跳出循环从而不会多加上一
		p = p->next;	//指针后移
	}

	return len;			//返回链表长度
 }

//判断链表是否为空；空就返回1
int Empty_List(LNode *L)
{
	/*当只有一个头结点的时候，该链表就为空*/
	if((L->next) == NULL)		//头结点与NULL相连
		return OK;
	else
		return ERROR;
}

//当第i个元素存在时，将其值赋给e并返回OK
int iGetElem_List(LNode *L, int i, ElemType &e)
{
	LNode *p;			// 定义一个 遍历指针
	int j = 1;			// j 为计数器

	p = L->next;		//使p指向第一个结点
	while(p && j < i)	//顺指针向后查找，知道p指向第i个元素或p为空
	{
		p = p->next;   	//遍历链表
		j++;			//记录遍历的位置和次数
	}

	if( ! p || j > i)	//判断此时的 p 是否为空 或 j 是否大于 i
		return ERROR;

	e = p->data;		//将第 i 个位置的元素值赋给 e 返回
	return OK;
}

//按值查找寻找元素e，返回e的位置
int eGetElem_List(LNode *L, ElemType &e)
{
	LNode *p;				//定义一个遍历指针
	int count = 0;			//定义计数器

	p = L->next;			// p 指向第一个结点
	while(p != NULL)
	{
		count++;			//位置加一，

		if(p->data == e)	//如果找到相等值
			return (count);		//返回位置值

		p = p->next;		//p指向下一个结点
	}

	return ERROR;
 }


//在链表中指定位置i在之前处插入数据
//其中包含在表头插入、在表尾插入、在表中插入三个位置
int Insert_List(LNode *L, int i, ElemType e)
{
	LNode *p, *s;			//定义指针，p 用来遍历，s 用来存储插入值
	int j=0;				//定义计数器

	p = L;					// p 指向头结点
	while(p && j < i-1)		//寻找第 i-1 个节点
	{
		p = p->next;			//遍历链表
		j++;
	}						//当跳出循环时p指针指向第i-1个元素

	if( ! p || j > i-1)		//判断 p 是否为空 或 j 是否大于 i
		return ERROR;

	s = (LinkList) malloc (sizeof(LNode));

	s->data = e;			//把要插入的数据赋给 s指针
	s->next = p->next;		//p->next指向第i个元素，把第i个元素的前驱接到要插入节点的后驱
	p->next = s;			//第i-1节点的后驱接到要插入元素的前驱

	return OK;
 }

//删除第i个元素，并由e返回其值。
//其中包含删除的节点是表头、在中间
int Delete_List(LNode *L, int i, ElemType &e)
{
	LNode *p,*s;			//定义 p s 指针
	int j=0;				//定义计数器

	p = L;					// p 指针指向头结点
	while(p && j<i-1)
	{
		p = p->next;
		j++;
	}						//跳出循环时p指向第i-1个节点

	if( !p->next || j > i-1)	//当第 i 个节点为空时
		return ERROR;

	s = p->next;   			//s指针指向第i个节点
	p->next = s->next;		//第i-1个节点的后驱与第i个节点后驱（即第i+1个节点的前驱）

	e = s->data;			//把第i个节点的值赋给e传回
	free(s);				//释放第i个节点的空间

	return OK;
}

//删除有序单向链表中的重复元素
int reDelete_List(LNode *L)
{
	LNode *p,*s,*q;					//定义指针

	p = L->next;					// p 指向第一个节点
	q = p->next;					// q 指向 p 的下一个节点

	while(q != NULL)
	{
		if(p->data == q->data)		//如果相邻两个节点值相等
		{
			p->next = q->next;		// p 的后继指向 q 的后继
			s = q;					//将相等的后一个节赋给 s
			q = q->next;			// q 继续向后遍历
			free(s);				//释放 s 节点
		}
		else
		{
			p = p->next;			// p 向后遍历
			q = q->next;			// q 向后遍历
		}
	}
 }

//对单链表进行逆序输出
/*主要思想：把原链表的数据从头到尾通过逆序建立链表法（头插法）插入到新链表中，
			(相当于逆序建立链表),然后再输出新链表*/
int rePrintf_List(LNode *L)
 {
 	LNode *p, *s, *q;
 	LinkList L0;					//定义一个新的链表用来存储反转后的数据

 	L0 = (LinkList) malloc (sizeof(LNode));
 	L0->next = NULL;				//新链表进行初始化

 	p = L->next;					//p指向原链表的第一个结点
 	while(p != NULL)
 	{
 		q = (LinkList) malloc (sizeof(LNode));		//申请一个新节点用来存储反转元素

 		q->data = p->data;			//把原来L链表的数据按从头结点到尾的顺序赋给新链表L0节点q。

 		q->next = L0->next;			//把新节点用头插法，从新链表L0的后面开始存储
 		L0->next = q;

 		p = p->next;				//遍历原链表L
 	}

 	s = L0->next;					//对新链表L0进行输出
	while(s != NULL)
	{
		printf("%d ",s->data);
		s = s->next;				//指针后移
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
	printf("*****      初始化一个单向链表，   Please enter  'l'          *****\n");
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
			case 'l':/*初始化一个单向链表*/
					{
						Init_List(&L);
						break;
					}
			default:printf("wrong!\n");
		}
	}while(str!='q');
}
