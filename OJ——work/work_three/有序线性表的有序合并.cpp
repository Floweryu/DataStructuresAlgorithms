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
	ElemType*elem;  //�洢�ռ��ַ
	int  length;	//��ǰ����Ԫ�صĸ���
	int  listsize;	//��ǰ������������Ԫ�ص����� 
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
			L.listsize+=LISTINCREMENT;//���Ӵ洢����+1
		}
	}
	return OK;
 } 
 
 Status LocateElem(SqList &L,ElemType e)
{
	int i; 
	ElemType *p;
	p=L.elem;	/*p��ֵΪͷ��ַ*/ 
	for(i=1;i<=L.length;i++)
	{
		if(e==*p)	
		{
			return i;
		}
		p++;	/*����ƶ����������Ա�*/ 
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
	e=*(L.elem+i-1); //����ַ+i-1)�ǵ�i��Ԫ�صĵ�ַ
	return OK; 
}

Status ListInsert(SqList &L,int i,ElemType e)
 {
 	ElemType *q,*p,*newbase;
 	if(i<1||i>L.length+1)  /*i����lengthʱ�����뵽���һ��*/
	return ERROR;
	if(L.length>=L.listsize) //�洢�ռ���������Ҫ���ӷ���
	{
		newbase=(ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(newbase==NULL)
		exit(OVERFLOW);
		L.elem=newbase;
		L.listsize+=LISTINCREMENT;//���Ӵ洢����+1
	} 
		q=L.elem+i-1;//qΪ����λ�ã���0��ʼ����
		for(p=L.elem+L.length-1;p>=q;p--)
		{
			*(p+1)=*p; //�Ѳ���λ��֮���Ԫ������ƶ�һλ 
		 } 
		 *q=e; //����e
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
 	int i=1,j=1,k=1;/*GetElem()�������Ѿ���ȥ�ˡ�1�������i��jʵ�ʱ�ʾ�ľ���Ԫ�ص�λ�á�
	�����׵�������k=0�������������ϲ��õ�Lcʱ�����˵�һ��Ԫ�أ����Ҹĳ�k=1���������ȷ��*/ 
 	La.length=ListLength(La);		/*�õ�La�ĳ���*/ 
 	Lb.length=ListLength(Lb);		/*�õ�Lb�ĳ���*/ 
 	while((i<=La.length)&&(j<=Lb.length))	/*��La��Lb����û�б�������У���һ�������꼴�˳�ѭ��*/ 
 	{
 		GetElem(La,i,ai);		/*�õ�La��iλ�õ�Ԫ��*/ 
 		GetElem(Lb,j,bj);		/*�õ�Lb��jλ�õ�Ԫ��*/
 		if(ai<=bj)	/*���La�е�Ԫ��С��Lb�е�*/ 
 		{
 			ListInsert(Lc,k++,ai);	/*��La(��С�Ĳ��뵽Lc����*/ 
 			i++;	/*La��Ԫ��λ�ü�һ���ж���һ��Ԫ��*/ 
		 }
		 else
		 {
		 	ListInsert(Lc,k++,bj);	/*��Lb(����Ĳ��뵽Lc����*/ 
		 	j++;	/*Lb��Ԫ��λ�ü�һ���ж���һ��Ԫ��*/ 
		 }
	 }
	 /*�˳�����ѭ��������La��Lb��һ�������Ѿ�������ɣ�������ֻ��Ҫ��û�б��������Ա���*/ 
	 while(i<=La.length)	 /*��La�����Ԫ�ؽӵ�Lc�ĺ���*/ 
	 {
	 	GetElem(La,i++,ai);	
	 	ListInsert(Lc,k++,ai);
	 }
	 while(j<=Lb.length)	/*��Lb�����Ԫ�ؽӵ�Lc�ĺ���*/
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

