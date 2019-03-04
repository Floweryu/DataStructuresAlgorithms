#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;

typedef struct DuLNode
{
	ElemType data;				//存储元素值 
	DuLNode *prior,*next;		// prior 为节点的前驱，next 为节点的后继 
}DuLNode,*DuLinkList;			// DuLNode 定义结构体，DuLinkList 定义结构体指针 

//初始化产生一个空的双向循环链表
Status DuInit_List(DuLNode *L)
{
	L = (DuLinkList) malloc (sizeof(DuLNode));	//申请L节点空间 
	if(L)	
	{	
		L->next = L->prior=L;					//L的后继和前驱链接并都链接L 
		return OK;
	}
	else
		exit(OVERFLOW);						//L节点空间没有申请成功 
}

//向双向循环链表中输入数据
Status DuCreate_List(DuLNode *L, int *n)
{
	DuLinkList p, q;			//q用来跟随p 
	int i;
	
	q = L;						//q指向L节点 
	for(i = 0; i < *n; i++)
	{
		p = (DuLinkList) malloc (sizeof(DuLNode));	//申请存储空间 
		if(!p)		   			//判断是否申请成功 
			exit(ERROR);
			
		scanf("%d", &p->data);	//输入数据 
		
		p->next = NULL;			//p的后继指向NULL 
		p->prior = q;			//p的前驱指向q 
		q->next = p;			//q的后继指向p 
		L->prior = p;			//L的前驱指向p，每次插入一个结点，它都指向L的前驱，与L相连接 
		q = p; 					//跟随p指针 
	}							//输入完成后，要形成双向循环链表 
	
	q->next = L;				//最后一个结点的后继指向L 
	L->prior = q;				//L的前驱指向这个结点 
 } 
//将L表置为空表
Status DuClear_List(DuLNode *L)
{
	DuLinkList p=L->next;			//p指向第一个结点
	
	while(p != L)
	{
		p = p->next;				//p指向下一个结点
		free(p->prior); 			//释放p的前驱结点 
	} 
	
	L->next = L->prior = L;		 	//头结点的两个指针域均指向自身 
	
	return OK;
}

//销毁双向链表L 
Status DuDestroy_List(DuLNode *L)
{
	DuClear_List(L);	//将L置为空表
	free(L); 			//释放头结点
	L = NULL; 
	
	return OK;
}

//判断L是否为空表
Status DuEmpty_List(DuLNode *L)
{
	if(L->next == L && L->prior == L)	//与双向循环链表定义一样（定义的就是一个空表） 
		return TRUE;
	else
		return FALSE;
}

//返回L中数据元素的个数
int DuLength_List(DuLNode *L)
{
	int i = 0;
	DuLinkList p = L->next;		//指向第一个结点 
	
	while(p != L)				//p未指向头结点 
	{
		i++;					//p已经指向一个结点，所以先加一 
		p = p->next;
	}
	
	return i;
 } 

//返回第i个元素的值
Status DuGetElem_List(DuLNode *L, int i, ElemType *e) 
{
	int j=1;
	DuLinkList p = L->next;		//p指向第一个结点
	
	while(p != L&&j<i)			//使p指向第i个结点 
	{
		j++;					//计数器加一 
		p = p->next;	
	}
	
	if(p == L||j>i)
		return ERROR;
		
	*e = p->data;					//将第i个节点的值赋给e返回 
	
	return OK; 
}

//返回第一个与e元素满足关系的元素的位序
int DuLocateElem_List(DuLNode *L,ElemType e,Status(*compare)(ElemType,ElemType)) 
{
	int i = 0;					//计数器初值为0 
	DuLinkList p = L->next;		//p指向第一个结点 
	
	while(p != L)				//当p不指向头结点时循环 
	{
		i++;					//计数器加一 
		if(compare(p->data,e))	//找到满足要求的元素，这里是“相等 
			return i;			//返回它的位序 
			
		p = p->next;				//p指向下一个节点 
	}
	
	return 0;
}

//判断两元素是否相等，相同返回1，不同返回0
Status cmp(ElemType e1,ElemType e2)
{
	if(e1 == e2)			//如果相等	 
		return 1;
	else
		return 0;
}

//返回第i个元素的地址
DuLinkList DuGetElem_P(DuLNode *L,int i)
{
	int j;
	DuLinkList p = L;					//p指向头结点 
	
	if(i < 0 || i > DuLength_List(L))	//判断i是否符合要求 
		return ERROR;
		
	for(j = 1; j <= i; j++)				//使p指向第i个节点 
		p = p->next;					//p指向下一个 
		
	return p;							//找到目标节点，返回它的地址 
 } 
//在第i个元素前插入元素e
Status DuInsert_List(DuLNode *L,int i,ElemType *e)
{
	DuLinkList p,s;						//p指针用来遍历，s指针用来做新节点 
	
	if(i < 1 || i > DuLength_List(L)+1)	//判断插入位置是否合理 
		return ERROR;
		
	p = DuGetElem_P(L, i-1);			//得到第i-1个结点的地址 
	
	if(!p)								//判断第i-1个结点是否为空 
		return ERROR;
		
	s = (DuLinkList)malloc(sizeof(DuLNode));	//申请一个新节点 
	
	if(!s)	//判断新节点是否成功 
		exit(OVERFLOW);
		
	s->data = *e;							//将 e赋给新节点 
	
	s->prior = p;							//s的前驱指向第i-1个节点 
	s->next = p->next;						//s的后继指向第i个节点 
	p->next->prior = s;						//第i个节点的前驱指向新节点 
	p->next = s;								//第i-1个节点后继指向新节点 
	
	return OK; 
 } 
 
 //删除第i个位置的元素
 Status DuDelete_List(DuLNode *L,int i,ElemType *e)
 {
 	DuLinkList p;
 			
 	if(i < 1)					//判断位置是否合法 
 		return ERROR;
 		
 	p=DuGetElem_P(L, i);		//得到第i个元素的位置
 	
	if(!p)						//判断得到的结点是否为空 
		return ERROR;
		
	*e = p->data;				//将删除的原素值传回 
	p->prior->next = p->next;		//第i-1个节点的后继链接到第i+1个节点 
	p->next->prior = p->prior;	//第i+1个节点的前驱连接到第i-1个节点的后继 
	free(p);					//释放第i个节点 
	
	return OK; 
} 

//正序输出
void DuPrintf_List(DuLNode *L)
{
	DuLinkList p;
	
	p = L->next;				//p指向第一个结点 
	while(p != L)				//p未到表头时循环 
	{
		printf("%d ",p->data);
		p = p->next;			//p指向下一个节点 （p从前向后遍历） 
	}
	printf("\n");
} 

//逆序输出
void DurePrintf_List(DuLNode *L)
{
	DuLinkList p;	
	
	p = L->prior;				//p指向最后一个结点 
	while(p !=	L)				//p为到表头时循环 
	{
		printf("%d ",p->data);
		p = p->prior;			//p指向上一个节点 （p从后向前遍历） 
	}
	printf("\n");
 } 
 
 int main()
 {
 	printf("***** 初始化产生一个空的双向循环链表,   enter   'a'  *****\n");
 	printf("*****           将L表置为空表,          enter   'b'  *****\n");
 	printf("*****         销毁双向链表L             enter   'c'  *****\n");
 	printf("*****          判断L是否为空表          enter   'd'  *****\n");
 	printf("*****          返回L中数据元素的个数    enter   'e'  *****\n");
 	printf("*****         返回第i个元素的值         enter   'f'  *****\n");
 	printf("*****返回第一个与e元素满足关系的元素的位序,enter  'g'  *****\n");
 	printf("*****        在第i个元素前插入元素e     enter   'h'  *****\n");
 	printf("*****      删除第i个位置的元素          enter   'i'  *****\n");
 	printf("*****            正序输出               enter   'j'  *****\n");
 	printf("*****            逆序输出               enter   'k'  *****\n");
 	printf("*****     向双向循环链表中输入数据      enter   'l'  *****\n");
 	DuLNode L;
 	char str;
 	int back;
 	ElemType E,I,N;
 	do
 	{
 		printf("\n");
		printf("Please enter a char:    ");
		str=getche();/*从键盘获取一个字符并显示，不按回车直接执行*/ 
		printf("\n");/*	getchar();	/*接收上条语句的回车键，否则回车键也会被认为是字符*/ 
		switch(str)
		{ 
			case 'a'://初始化产生一个空的双向循环链表
			{
				back=DuInit_List(&L);
				if(back)
					printf("双向循环链表初始化成功。\n");
				else
					printf("双向循环链表初始化失败。\n");
				break;
			}
			case 'b'://将L表置为空表
			{
				back=DuClear_List(&L);
				if(back)
					printf("清空双向循环链表成功。\n");
				else
					printf("链表清空失败。\n");
				break;
			}
			case 'c'://销毁双向链表L 
			{
				back=DuDestroy_List(&L);
				if(back)
					printf("销毁链表成功。\n");
				else
					printf("销毁链表失败。\n");
				break;
			}
			case 'd'://判断L是否为空表
			{
				back=DuEmpty_List(&L);
				if(back)
					printf("这是一个空的链表。\n");
				else
					printf("这不是一个空链表。\n");
				break;
			}
			case 'e'://返回L中数据元素的个数
			{
				back=DuLength_List(&L);
				printf("链表的长度是：   %d\n",back);
				break;
			}
			case 'f'://返回第i个元素的值  
			{
				printf("请输入你想知道元素的位置：   ");
				scanf("%d",&I);
				DuGetElem_List(&L,I,&E);
				printf("第 %d 个位置的元素是:   %d\n",I,E);
				break;
			}
			case 'g'://返回第一个与e元素满足关系的元素的位序
			{
				printf("请输入元素：    ");
				scanf("%d",&E);
				back=DuLocateElem_List(&L,E,cmp);
				printf("该元素在链表中的位序是：   %d\n",back);
				break;
			}
			case 'h'://在第i个元素前插入元素e
			{
				printf("请输入插入元素的位置：  ");
				scanf("%d",&I);
				printf("请输入插入元素的值：  ");
				scanf("%d",&E);
				back=DuInsert_List(&L,I,&E);
				if(back)
				{
					printf("插入后链表的值为：\n");
					DuPrintf_List(&L);
					printf("\n");
				} 
				break; 	
			}
			case 'i'://删除第i个位置的元素 
			{
				printf("请输入删除元素的位置：  ");
				scanf("%d",&I);
				back=DuDelete_List(&L,I,&E);
				if(back)
				{
					printf("删除该位置的元素值为:  %d\n",E);
					printf("删除后线性表为:\n");
					DuPrintf_List(&L);
					printf("\n");
				}
				break;
			}
			case 'j'://正向输出
			{
				DuPrintf_List(&L);
				break;
			}
			case 'k'://逆向输出
			{
				DurePrintf_List(&L);
				break;
			}
			case 'l'://向双向循环链表中输入数据
			{
				printf("请输入创建链表的长度：  ");
				scanf("%d",&N);
				DuCreate_List(&L,&N);
				break;
			}
			default:printf("wrong!\n");
		}
	 }while(str!='q');
	 return 0;
  } 
