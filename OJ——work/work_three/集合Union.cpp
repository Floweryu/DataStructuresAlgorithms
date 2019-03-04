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
 

Status Union_Sq(SqList &La,SqList Lb)
{
	La.length=ListLength(La);
	Lb.length=ListLength(Lb);
	int i,k;
	ElemType e;
	for(i=1;i<=Lb.length;i++)
	{
		GetElem(Lb,i,e);		/*��Lb�л�ø�λ�õ�Ԫ��*/ 
		k=LocateElem(La,e);	/*���ظ�Ԫ����La�е�λ��*/ 
		if(k==0)			/*���La�в�������e��ͬ��Ԫ�أ���λ�÷���Ϊ0�������*/ 
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

