#include<stdio.h>
#include<stdlib.h>


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

typedef struct
{
	ElemType*elem;  //存储空间基址
	int  length;	//当前数据元素的个数
	int  listsize;	//当前分配的最大数据元素的容量 
 } SqList; 
 
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

Status ClearList(SqList &L)
{
  	if(L.elem==NULL)
 	   return ERROR;
 	else
 	{
 		L.length=0;
 		return OK;
	}
} 

Status CreateList(SqList &L,int n)
{
	for(int i=0;i<n;i++)
	{
		scanf("%d",&L.elem[i]);
		L.length++;
		if(L.length>=L.listsize)
		{
			ElemType *newbase=(ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
			if(newbase==NULL)
			exit(OVERFLOW);
			L.elem=newbase;
			L.listsize+=LISTINCREMENT;//增加存储容量+1
		}
	}
	return OK;
 } 
 
 Status LocateElem(SqList &L,ElemType e)
{
	int i; 
	ElemType *p;
	p=L.elem;	/*p赋值为头地址*/ 
	for(i=1;i<=L.length;i++)
	{
		if(e==*p)	
		{
			return i;
		}
		p++;	/*向后移动，遍历线性表*/ 
	}
	return FALSE;
}

int ListLength(SqList &L)
{
	return L.length;
}

Status GetElem(SqList &L,int i,ElemType &e)
{
	if(i<1||i>L.length)
	return OVERFLOW;
	e=*(L.elem+i-1); //（基址+i-1)是第i个元素的地址
	return OK; 
}

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
Status ListSee(SqList &L)
{
	if(L.elem==NULL||L.length==0)
	return ERROR;
	else
	{
		int i;
		for(i=0;i<L.length;i++)
			printf("%d ",L.elem[i]);
		printf("\n");	
	}	
	return OK;
}
 

Status MergeList(SqList La,SqList Lb,SqList &Lc)
 {
 	ElemType ai,bj;
 	InitList(Lc);
 	int i=1,j=1,k=1;/*GetElem()函数中已经减去了“1”，因此i和j实际表示的就是元素的位置。
	不明白的是书上k=0，这样最后输出合并好的Lc时会少了第一个元素；而我改成k=1后，输出就正确。*/ 
 	La.length=ListLength(La);		/*得到La的长度*/ 
 	Lb.length=ListLength(Lb);		/*得到Lb的长度*/ 
 	while((i<=La.length)&&(j<=Lb.length))	/*当La和Lb都还没有遍历完进行，有一个遍历完即退出循环*/ 
 	{
 		GetElem(La,i,ai);		/*得到La在i位置的元素*/ 
 		GetElem(Lb,j,bj);		/*得到Lb在j位置的元素*/
 		if(ai<=bj)	/*如果La中的元素小于Lb中的*/ 
 		{
 			ListInsert(Lc,k++,ai);	/*把La(即小的插入到Lc表中*/ 
 			i++;	/*La中元素位置加一，判断下一个元素*/ 
		 }
		 else
		 {
		 	ListInsert(Lc,k++,bj);	/*把Lb(即大的插入到Lc表中*/ 
		 	j++;	/*Lb中元素位置加一，判断下一个元素*/ 
		 }
	 }
	 /*退出上面循环即表明La或Lb有一个链表已经遍历完成，接下来只需要对没有遍历的线性表处理*/ 
	 while(i<=La.length)	 /*把La后面的元素接到Lc的后面*/ 
	 {
	 	GetElem(La,i++,ai);	
	 	ListInsert(Lc,k++,ai);
	 }
	 while(j<=Lb.length)	/*把Lb后面的元素接到Lc的后面*/
	 {
	 	GetElem(Lb,j++,bj);
	 	ListInsert(Lc,k++,bj);
	 }
} 
 
int main()
{
	int N1,N2;
	SqList La,Lb,Lc;
	InitList(La);
	InitList(Lb);
	while(scanf("%d",&N1)!=EOF)
	{
		CreateList(La,N1);
		scanf("%d",&N2);
		CreateList(Lb,N2);
		MergeList(La,Lb,Lc);
		ListSee(Lc);
		ClearList(La);
		ClearList(Lb);	
	}
}

