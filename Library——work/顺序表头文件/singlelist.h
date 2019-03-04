#ifndef SINGLELIST_H
#define SINGLELIST_H


#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

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


#endif // SINGLELIST_H

