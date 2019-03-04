#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;

typedef struct LNode{
	ElemType	data;			//数据域 
	struct LNode	*next;		//指针域 
}LNode,*LinkList;

//初始化链表 
void Inite_cirList(LNode *L)
{
	L = (LinkList) malloc (sizeof(LNode));		//申请头结点 
	if( ! L)									//判断节点是否分配成功 
		exit(ERROR);
		
	L->next = L;								//头结点指针指向头结点 
}


//链表的创建；正向建立		
int Create_cirList(LNode *L,int n)
{
	LNode *p,*q;					//p指针用来申请新节点，
									//q指针用来遍历，永远跟随新节点，以便链接下一个新节点 
	int i;							//用来计数 
	
	q = L;  						//让遍历指针q指向头结点 
	for(i = 0; i < n; i++)	
	{
		p = (LinkList)malloc(sizeof(LNode));		//生成新节点
		
		if( ! p)
			exit(OVERFLOW);			//判断申请节点是否成功 
			
		scanf("%d", &p->data);		//输入数据 
		
		p->next = NULL;				//新申请的节点的下一个地址指向空 
		q->next = p;				//q的下一个地址指向p，链接新节点到链表中 
		q = p;						//q移动到p这，准备链接下一个节点p 
	}
	
	q->next = L;					//输入数据后，遍历指针q链接表头，构成循环链表 
 }
 
//将L置为空链表
void Clear_cirList(LNode *L)
{
	LinkList p, q;
	
	p = L->next;			//p指向第一个节点 
	
	while(p != L)			//循环链表，当p没有指到表尾 
	{
		q = p->next;		//q指向p的后继节点 
		free(p);			//释放p当前所指的空间 
		p = q;				//p指向q所指的节点，即被释放节点的下一个节点 
	}
	
	L = L->next;			//释放完链表中节点后，使头结点指向自己 
} 

//销毁循环单链表
void Destroy_cirList(LNode *L)
{	//从内容，表头彻底的销毁一个链表 
	Clear_cirList(L);			//先清空L 
	free(L);					//释放头结点 
	L = NULL;					//L不指向任何存储单元 
 } 
 
//判断循环单链表是否为空
Status Empty_cirList(LNode *L)
{	//根据头结点后继是否指向头结点 
	if(L->next == L)		//空返回真 
		return TRUE;
	else					//非空返回假 
		return FALSE;
}

//返回循环单向链表中元素的个数
Status Length_cirList(LNode *L)
{
	LinkList p,q;
	int i = 0;
	
	p = L->next;				//p指向第一个节点 
	while(p != L)				//当p未指向表头时遍历 
	{	
		i++;					//p已经指向第一个节点，所以先加一 
		p=p->next;				//再遍历 
	}
	
	return i;					//返回统计的个数 
 } 
 
//返回指定位置的元素
Status GetElem_cirList(LNode *L,int i,ElemType *e)
{	
	int j = 1;					//计数，算实际位置从1开始 
	LinkList p;
	
	p = L->next;				//p指向第一个节点 
	while(p !=L && j < i)		//关键是j小于i时循环 
	{
		j++;					//j是几就表示第几个节点 ，j=i-1的时候还可以再循环一次 
		p = p->next;			//p此时也指向第i个节点
	}
	
	if(p == L || j > i)
		return ERROR;
		
	*e = p->data;				//把第i个节点的数据传回 
	
	return OK;
} 

//返回单向循环链表中第一个与e满足关系compare()的数据元素的位序
int LocateElem_cirList(LNode *L,ElemType e,Status(*compare)(ElemType,ElemType))
{
	int i = 0;					//计数位序,根据具体情况赋初值为0或1 
	LinkList p;
	p = L->next;				//p指向第一个节点
	while(p != L)
	{
		i++;
		if(compare(p->data,e))	//如果关系符合，就返回真 
			return i;			//如果找到第一个真，返回位序 
			
		p = p->next;
	} 
	
	return 0;
 } 
 
//判断两元素是否相等，相同返回1，不同返回0
Status cmp(ElemType e1,ElemType e2)
{
	if(e1 == e2)
		return 1;
	else
		return 0;
}

//在循环链表前第i个位置前插入元素e
Status Insert_cirList(LNode *L,int i,ElemType e)
{
	LNode *p,*s;
	p = L;
	int j = 0;
	
	if(i <= 0 || i > Length_cirList(L)+1)
		return ERROR;
		
	while(j < i-1)				//当链表L不是空表时并且当前位置小于i-1 
	{  
		p = p->next;			//遍历链表 
		j++;
	}							//当跳出循环时p指针指向第i-1个元素 
	
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;				//把要插入的数据赋给 s指针 
	s->next = p->next;			//p->next指向第i个元素，把第i个元素的前驱接到要插入节点的后驱 
	p->next = s;				//第i-1节点的后驱接到要插入元素的前驱 
	if(p == L)
		L = s;
	return OK;
 } 
 
//删除第i个元素
Status Delete_cirList(LNode *L,int i,ElemType *e)
{
	LinkList p,q;
	p = L->next;			//p指向第一个结点 
	int j = 1;				//所以j从1开始计数 
	
	if(i <= 0 || i > Length_cirList(L))		//删除位置不在链表范围内 
		return ERROR;
		
	while(j < i-1)							//寻找第i-1个节点 
	{
		j++;
		p = p->next;
	}
	
	q = p->next;							//q指向待删除的节点，p的下一个 
	p->next = q->next;						//待删除节点的前驱指向待删除节点的后继 
	
	*e = q->data;							//把待删除节点的存储值赋给e返回 
	
	if(q == L)								//删除的是表尾的元素 
		L = p;								//L指向新的表尾节点 
		
	free(q);								//释放待删除节点 
	return OK;
} 
//打印输出链表中的数据
int Printf_cirList(LNode *L)
{
	int i;
	LNode *p;
	
	p = L->next;			//使p指针指向链表的第一个数据
	while(p != L)
	{
		printf("%d ",p->data);
		p = p->next;		//指针后移 
	} 
 } 
 
 
int main()
{
	printf("******************************************************************\n");
	printf("*****        定义单向循环链表，    Please enter 'a'          *****\n");
	printf("*****         返回单向循环链表的长度，Please enter   'b'     *****\n");
	printf("*****         输出单向循环链表中的数据，Please enter 'c'     *****\n");
	printf("*****       判断单向循环链表是否为空，Please enter 'd'       *****\n");
	printf("*****       返回给定位置的节点元素值，Please enter 'e'       *****\n");
	printf("*****     返回给定元素值的节点位置，Please enter 'f'         *****\n");
	printf("*****   在链表中指定位置i在之前处插入数据，Please enter 'g'  *****\n");
	printf("*****   删除第i个元素，并由e返回其值，Please enter 'h'       *****\n");
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
			case 'a':/* 创建一个单向循环链表*/
					{
						Inite_cirList(&L);
						printf("请输入创建链表的长度：  ");
						scanf("%d",&N);
						Create_cirList(&L,N);
						break;
					} 
			case 'b':/* 返回单向链表的长度*/
					{
						k=Length_cirList(&L);
						printf("该链表的长度是：  %d",k);
						break;
					}
			case 'c':/* 输出单向链表中的数据*/
					{
						printf("此单向链表中的数据为：\n");
						Printf_cirList(&L);
						break;
					} 
			case 'd':/* 判断链表是否为空*/
					{
						k=Empty_cirList(&L);
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
						GetElem_cirList(&L,I,&E);
						printf("第  %d  个元素的值为：  %d\n",I,E);
						break;
					}
			case 'f':/*返回单向循环链表中第一个与e满足关系compare()的数据元素的位序*/
					{
						printf("输入你想知道是否在链表中的数值：  ");
						scanf("%d",&E);
						k=LocateElem_cirList(&L,E,cmp);
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
						k=Insert_cirList(&L,I,E);
						if(k)
						{
							printf("插入后链表的值为：\n");
							Printf_cirList(&L);
							printf("\n");
						 } 
						 else
						 {
						 	printf("ERROR\n");
						 }
						break; 
					 } 
			case 'h':/*删除第i个元素，并由e返回其值*/
					{
						printf("请输入删除元素的位置：  ");
						scanf("%d",&I);
						k=Delete_cirList(&L,I,&E);
						if(k)
						{
							printf("删除该位置的元素值为:  %d\n",E);
							printf("删除后线性表为:\n");
							Printf_cirList(&L);
							printf("\n");
						}
							break;
					}
			default:printf("wrong!\n");
		}
	}while(str!='q');
 } 
