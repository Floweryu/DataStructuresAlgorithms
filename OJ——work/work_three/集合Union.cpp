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
 

Status Union_Sq(SqList &La,SqList Lb)
{
	La.length=ListLength(La);
	Lb.length=ListLength(Lb);
	int i,k;
	ElemType e;
	for(i=1;i<=Lb.length;i++)
	{
		GetElem(Lb,i,e);		/*从Lb中获得该位置的元素*/ 
		k=LocateElem(La,e);	/*返回该元素在La中的位置*/ 
		if(k==0)			/*如果La中不存在与e相同的元素，即位置返回为0，则插入*/ 
		{
			ListInsert(La,La.length+1,e);
		}
		ListSee(La);
	}
 } 
 
int main()
{
	int N1,N2;
	SqList La,Lb;
	InitList(La);
	InitList(Lb);
	while(scanf("%d",&N1)!=EOF)
	{
		CreateList(La,N1);
		scanf("%d",&N2);
		CreateList(Lb,N2);
		ListSee(La);
		ListSee(Lb);
		Union_Sq(La,Lb);
		printf("\n");
		ClearList(La);
		ClearList(Lb);	
	}
}

