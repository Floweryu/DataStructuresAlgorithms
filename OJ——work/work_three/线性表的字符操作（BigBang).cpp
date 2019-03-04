#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define maxnum 100
#define LISTINCREMENT 10

typedef int Status;

typedef struct
{
	char name[100];
}ElemType;

/*线性表结构体的定义*/
typedef struct
{
	ElemType*elem;  //存储空间基址
	int  length;	//当前数据元素的个数
	int  listsize;	//当前分配的最大数据元素的容量 
 } SqList; 
 
 /*函数名：InitList()
  功能：构造一个空线性表
  返回值：存储分配失败：OVERFLOW
          存储分配成功：OK   */
Status InitList(SqList &L)
{
	L.elem=(ElemType*)malloc(maxnum*sizeof(ElemType));
	if(L.elem==NULL)
	return(OVERFLOW);
	else
	{
		L.length=0;
		L.listsize=maxnum;
		return OK;
	}
}
 
 /*函数名：ListInsert（）；
  初始条件：线性表L已存在，1 <= i <=L.length + 1;
  功能：在线性表第i个元素前插入e,表的长度加1
  返回值：失败：ERROR
          成功：OK 	*/
 Status ListInsert(SqList &L,int i,ElemType e)
 {
 	ElemType *q,*p,*newbase;
 	if(i<1||i>L.length+1)  /*i等于length时即插入到最后一个*/
	return ERROR;
	if(L.length>=L.listsize) //存储空间已满，需要增加分配
	{
		newbase=(ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(newbase==NULL)
		exit(OVERFLOW);
		L.elem=newbase;
		L.listsize+=LISTINCREMENT;//增加存储容量+1
	} 
	q=L.elem+i-1;//q为插入位置，从0开始计算
	for(p=L.elem+L.length-1;p>=q;p--)
	{
		*(p+1)=*p; //把插入位置之后的元素向后移动一位 
	 } 
	 *q=e; //插入e
	 L.length++;
	 return OK;
} 

/*函数名：ListDelete（）
  初始条件：线性表L已存在。1<= i <= L.length
  功能：删除线性表中第i个元素,并用e返回被删数的值 
  返回值：失败：ERROR
          成功：OK		*/
Status ListDelete(SqList &L,int i)
{
	ElemType *p,*q;
	if(i<1||i>L.length)
	return ERROR;
	p=L.elem+i-1;	/*p指针指向第i个元素的地址*/ 
	//	e=*p;		/*把第i个地址的值赋给e*/ 
	q=L.elem+L.length-1;	/*q被赋值为该线性表的最长地址*/ 
	for(p;p<=q;p++)		/*从p处地址开始，把后一个值赋给前一个，从而达到删除效果*/ 
	{
		*p=*(p+1);
	}
	L.length--;	/*线性表的实际存储值的长度减一*/ 
	return OK;
}

/*函数名：LocateElem()
  功能：返回顺序表中第一个与element相等的元素的位序 
  返回值：若L中存在与element相等的元素，则返回第一个符合条件的元素位序
          若不存在，则返回0		*/
Status LocateElem(SqList &L,ElemType e,Status(*compare)(ElemType,ElemType))
{
	int i; 
	ElemType *p;
	p=L.elem;	/*p赋值为头地址*/ 
	for(i=1;i<=L.length;i++)
	{
		if(compare(*p,e))	
		{
			return i;
		}
		p++;	/*向后移动，遍历线性表*/ 
	}
	return FALSE;
}

/*函数名：ListSee()
  功能：输出线性表中的元素	*/
void ListSee(SqList &L)
{
	int i;
	for(i=0;i<L.length;i++)
	{
		if(i)
			printf(" ");
		printf("%s",L.elem[i].name);
	}
	printf("\n");		
}
//判断两元素是否相等，相同返回1，不同返回0
Status cmp(ElemType e1,ElemType e2)
{
	return (Status)!strcmp(e1.name,e2.name);
}

int main()
{
	SqList La;		//定义一个线性表 
	ElemType e;		//定义存储名字的字符数组 
	int a;		//存储位置
	char str[10];	//用来获取指令
	InitList(La);
	while(scanf("%s",str)!=EOF)
	{
		if(strcmp(str,"insert")==0)		//插入元素
		{
			scanf("%d%s",&a,e.name);		//输入插入位置和插入元素
			ListInsert(La,a,e); 
		}
		else if(strcmp(str,"delete")==0)	//删除元素
		{
			scanf("%s",e.name);
			ListDelete(La,LocateElem(La,e,cmp));
		} 
		else if(strcmp(str,"show")==0)	//输入线性表中元素
		{
			ListSee(La);
		} 
		else if(strcmp(str,"search")==0)	//返回元素的位序
		{
			scanf("%s",e.name);
			printf("%d\n",LocateElem(La,e,cmp));
		 } 
	} 
	return 0;	
 } 
