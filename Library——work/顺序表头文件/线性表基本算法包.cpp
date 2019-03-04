#include "stdio.h"
#include "stdlib.h"
#include "conio.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define maxnum 100
#define LISTINCREMENT 10

typedef int Status;
typedef int ElemType;

/*线性表结构体的定义*/
typedef struct
{
	ElemType*elem;  //存储空间基址
	int  length;	//当前数据元素的个数
	int  listsize;	//当前分配的最大数据元素的容量 
 } SqList; 


//构造一个空线性表
//返回值：存储分配失败：OVERFLOW存储分配成功：OK 
Status InitList(SqList *L)
{
	(*L).elem=(ElemType*)malloc(maxnum*sizeof(ElemType));
	if((*L).elem==NULL)
	return(OVERFLOW);
	else
	{
		(*L).length=0;
		(*L).listsize=maxnum;
		return OK;
	}
}
//给一个空线性表赋值 
//返回值：赋值失败：OVERFLOW      赋值成功：OK  
Status CreateList(SqList *L,int n)
{
	for(int i=0;i<n;i++)
	{
		scanf("%d",&(*L).elem[i]);
		(*L).length++;
		if((*L).length>=(*L).listsize)
		{
			ElemType *newbase=(ElemType*)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
			if(newbase==NULL)
			exit(OVERFLOW);
			(*L).elem=newbase;
			(*L).listsize+=LISTINCREMENT;//增加存储容量+1
		}
	}
	return OK;
 } 
 
//销毁线性表
//返回值：L.elem == NULL:ERRor   L.elem != NUll:OK
Status DestroyList(SqList *L)
{
 	if((*L).elem==NULL)
 	   return ERROR;
 	else
 	{
 		free((*L).elem);
 		return OK;
	}
} 

//清空线性表
//返回值：L.elem == NULL :ERROR   L.elem != NULL :OK
Status ClearList(SqList *L)
{
  	if((*L).elem==NULL)
 	   return ERROR;
 	else
 	{
 		(*L).length=0;
 		return OK;
	}
} 

//判断线性表是否为空
//返回：空：FALSE  非空：TRUE	
Status EmptyList(SqList *L)
{
  	if(!(*L).length)
  	return(FALSE);
  	else
  	return(TRUE);
}  

//返回线性表长度
// 返回值：线性表长度（L.length）
int LengthList(SqList *L)
{
	return (*L).length;
}
  
//在线性表第i个元素前插入e,表的长度加1
//失败：ERROR 。成功：OK 
 Status iInsertList(SqList *L,int i,ElemType e)
 {
 	ElemType *q,*p,*newbase;
 	if(i<1||i>(*L).length+1)  /*i等于length时即插入到最后一个*/
	return ERROR;
	if((*L).length>=(*L).listsize) //存储空间已满，需要增加分配
	{
		newbase=(ElemType*)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
		if(newbase==NULL)
		exit(OVERFLOW);
		(*L).elem=newbase;
		(*L).listsize+=LISTINCREMENT;//增加存储容量+1
	} 
		q=(*L).elem+i-1;//q为插入位置，从0开始计算
		for(p=(*L).elem+(*L).length-1;p>=q;p--)
		{
			*(p+1)=*p; //把插入位置之后的元素向后移动一位 
		 } 
		 *q=e; //插入e
		 (*L).length++;
		 return OK;
} 

//线性表L已存在。1<= i <= L.length
//删除线性表中第i个元素,并用e返回被删数的值 
Status iDeleteList(SqList *L,int i,ElemType *e)
{
	ElemType *p,*q;
	if(i<1||i>(*L).length)
	return ERROR;
	p=(*L).elem+i-1;	/*p指针指向第i个元素的地址*/ 
	*e=*p;		/*把第i个地址的值赋给e*/ 
	q=(*L).elem+(*L).length-1;	/*q被赋值为该线性表的最长地址*/ 
	for(p;p<=q;p++)		/*从p处地址开始，把后一个值赋给前一个，从而达到删除效果*/ 
	{
		*p=*(p+1);
	}
	(*L).length--;	/*线性表的实际存储值的长度减一*/ 
	return OK;
}



//用e返回线性表第i个元素的值
// (i < 1)||(i > ListLength(L)) : OVERFLOW.  1<= i <=ListLength(l) :OK
Status GetElemList(SqList *L,int i,ElemType *e)
{
	if(i<1||i>(*L).length)
		return (ERROR);
	else
	*e=*((*L).elem+i-1); //（基址+i-1)是第i个元素的地址
	return OK; 
}


//返回顺序表中第一个与element相等的元素的位序 
//若L中存在与element相等的元素，则返回第一个符合条件的元素位序若不存在，则返回0	
Status LocateElemList(SqList *L,ElemType e)
{
	int i; 
	ElemType *p;
	p=(*L).elem;	/*p赋值为头地址*/ 
	for(i=1;i<=(*L).length;i++)
	{
		if(e==*p)	
		{
			return i;
		}
		p++;	/*向后移动，遍历线性表*/ 
	}
	return FALSE;
}

//删除有序线性表中的重复元素
Status DeleteReList(SqList *L)
{
	ElemType *p,*q,E;
	int i; 
	p=(*L).elem;
	q=p+1;
	for(i=1;i<=(*L).length;i++)
	{
		if(*p==*q)
		{
			p=q;
			q=q+1;
			iDeleteList(L,i,&E);
		}
		else
		{
			p=q;
			q=q+1;
		}
	}
	
}

//在线性表中值为e的元素前插入E，长度加一
Status eInsertList(SqList *L,ElemType e,ElemType E)
{
	ElemType *q,*p,*newbase;
	int i;
	i=LocateElemList(L,e);
	iInsertList(L,i,E);
 } 

//删除现行表中值为e的元素
Status  eDeleteList(SqList *L,ElemType e)
{
	ElemType *p,*q;
	int i;
	i=LocateElemList(L,e);
	if(i<1||i>(*L).length)
	return ERROR;
	p=(*L).elem+i-1;	/*p指针指向第i个元素的地址*/ 
	q=(*L).elem+(*L).length-1;	/*q被赋值为该线性表的最长地址*/ 
	for(p;p<=q;p++)		/*从p处地址开始，把后一个值赋给前一个，从而达到删除效果*/ 
	{
		*p=*(p+1);
	}
	(*L).length--;	/*线性表的实际存储值的长度减一*/ 
	return OK;
}

//输出线性表中的元素	
Status PrintfList(SqList *L)
{
	if((*L).elem==NULL||(*L).length==0)
	return ERROR;
	else
	{
		int i;
		for(i=0;i<(*L).length;i++)
			printf("%d ",(*L).elem[i]);
		printf("\n");	
	}	
	return OK;
}

int main()
{

		printf("The functions of this program are as follows, please follow the instructions to operate:\n");
		printf("********************************************************************************\n");
		printf("      *****功能：给线性表赋值                               please enter  a   **\n");
		printf("      *****功能：判断线性表是否为空                         please enter  b   **\n");
		printf("      *****功能：返回线性表长度                             please enter  c   **\n");
		printf("      *****功能：在线性表第i个元素前插入e,表的长度加1       please enter  d   **\n");
		printf("      *****功能：删除线性表中第i个元素,并用e返回被删数的值  please enter  e   **\n");
		printf("      *****功能：用e返回线性表第i个元素的值                 please enter  f   **\n");
		printf("      *****功能：返回顺序表中第一个与element相等的元素的位序please enter  g   **\n");
		printf("      *****功能：输出线性表中的元素                         please enter  h   **\n");
		printf("      *****功能：清空线性表                                 please enter  i   **\n");
		printf("      *****功能：删除线性表中重复的元素。                   please enter  j   **\n");
		printf("      *****功能：在线性表中值为e的元素前插入E，             please enter  k   **\n");
		printf("      *****功能：删除现性表中值为e的元素                    please enter  l   **\n");
		printf("********************************************************************************\n");
		printf("\n");
		SqList La;	/*定义main()函数中的线性表*/ 
		char str;	/*从键盘接受一个字符*/ 
		Status back;	/*定义函数返回的表示逻辑判断的*/ 
		int I,N,k;		/*I是 表示位置的，N表示赋值的个数，k为返回的表的长度或其他整形代数*/ 
		ElemType E,M;		/* E是返回某位置的元素的值*/ 
		back=InitList(&La);	/*初始化线性表*/ 
		if(back) 
		printf("初始化成功!!!\n");
		
	do
	{
		printf("\n");
		printf("Please enter a char:    ");
		str=getche();/*从键盘获取一个字符并显示，不按回车直接执行*/ 
		printf("\n");/*	getchar();	/*接收上条语句的回车键，否则回车键也会被认为是字符*/ 
		switch(str)
			{
				case 'a': /*给线性表赋值*/
						{
							printf("请确定输入数据的个数：  ");
							scanf("%d",&N);
							printf("请输入数据，以空格隔开：\n");	
							CreateList(&La,N);
							break;
						}
				case 'b':/*判断线性表是否为空*/
						{
				      		back=EmptyList(&La);
							if(!back)
							printf("This is an empty list\n");
							else
							printf("This is not an empty list.\n");
							break;
						}
				case 'c':/*返回线性表长度  */ 
						{
							k=LengthList(&La);
							printf("The length of the list is :  %d",k);
							printf("\n");
							break;
						}
				case 'd':/* 在线性表第i个元素前插入e,表的长度加1 */ 
						{
							printf("请输入插入元素的位置：  ");
							scanf("%d",&I);
							printf("请输入插入元素的值：  ");
							scanf("%d",&E); 
							back=iInsertList(&La,I,E);
							if(back)
							PrintfList(&La);
							printf("\n");
							break;
						}
				case 'e':/*删除线性表中第i个元素,并用e返回被删数的值*/ 
						{
							printf("请输入删除元素的位置：  ");
							scanf("%d",&I);
							back=iDeleteList(&La,I,&E);
							if(back)
							{
								printf("删除该位置的元素值为:  %d\n",E);
								printf("删除后线性表为:\n");
								PrintfList(&La);
								printf("\n");
							}
							break;
						}
				case 'f':/*用e返回线性表第i个元素的值 */ 
						{
							printf("你要查找第几个元素:   ");
							scanf("%d",&I); 
							back=GetElemList(&La,I,&E);
							if(back)
							printf("第  %d  个元素的值为：  %d\n",I,E);
							else
							printf("该位置没有存储元素\n");
							break;
						}
				case 'g':/*返回顺序表中第一个与element相等的元素的位序*/ 
						{
							printf("输入你想知道是否在表中的数值：  ");
							scanf("%d",&E);
							k=LocateElemList(&La,E);
							if(k)
								printf("值为  %d  是表中的第  %d  个元素\n",E,k);
							else
								printf("此线性表中没有值为%d的元素\n",E);
							break;
						}
				case 'h':/*输出线性表中的元素*/ 
						{
							printf("线性表中各元素的值为：\n");
							PrintfList(&La);
							printf("\n");
							break;
						}
				case 'i':/*清空线性表 */ 
						{
							back=ClearList(&La);
							if(back)
								printf("线性表已被清空。\n");
							break;
						}
				case 'j'://删除线性表中的重复元素
						{
							DeleteReList(&La);
							PrintfList(&La);
							break;
						}
				case 'k'://在线性表中值为e的元素前插入E
						{
							printf("请输入在值为哪个元素前插入：  ");
							scanf("%d",&M);
							printf("请输入插入元素的值：  ");
							scanf("%d",&E); 
							back=eInsertList(&La,M,E);
							if(back)
							PrintfList(&La);
							else
							printf("插入失败\n");
							printf("\n");
							break;
						}
				case 'l'://删除现行表中值为e的元素
						{
							printf("请输入删除元素的值：  ");
							scanf("%d",&E);
							back=eDeleteList(&La,E);
							if(back)
							{
								printf("删除后线性表为:\n");
								PrintfList(&La);
							}
							else
								printf("删除失败\n");
							printf("\n");
							break;
						}
				default:printf("wrong!\n");
			}
	}while(str!='q');
} 
   
