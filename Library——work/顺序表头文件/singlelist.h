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

/*���Ա�ṹ��Ķ���*/
typedef struct
{
	ElemType*elem;  //�洢�ռ��ַ
	int  length;	//��ǰ����Ԫ�صĸ���
	int  listsize;	//��ǰ������������Ԫ�ص�����
 } SqList;


//����һ�������Ա�
//����ֵ���洢����ʧ�ܣ�OVERFLOW�洢����ɹ���OK
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
//��һ�������Ա�ֵ
//����ֵ����ֵʧ�ܣ�OVERFLOW      ��ֵ�ɹ���OK
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
			(*L).listsize+=LISTINCREMENT;//���Ӵ洢����+1
		}
	}
	return OK;
 }

//�������Ա�
//����ֵ��L.elem == NULL:ERRor   L.elem != NUll:OK
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

//������Ա�
//����ֵ��L.elem == NULL :ERROR   L.elem != NULL :OK
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

//�ж����Ա��Ƿ�Ϊ��
//���أ��գ�FALSE  �ǿգ�TRUE
Status EmptyList(SqList *L)
{
  	if(!(*L).length)
  	return(FALSE);
  	else
  	return(TRUE);
}

//�������Ա���
// ����ֵ�����Ա��ȣ�L.length��
int LengthList(SqList *L)
{
	return (*L).length;
}

//�����Ա��i��Ԫ��ǰ����e,��ĳ��ȼ�1
//ʧ�ܣ�ERROR ���ɹ���OK
 Status iInsertList(SqList *L,int i,ElemType e)
 {
 	ElemType *q,*p,*newbase;
 	if(i<1||i>(*L).length+1)  /*i����lengthʱ�����뵽���һ��*/
	return ERROR;
	if((*L).length>=(*L).listsize) //�洢�ռ���������Ҫ���ӷ���
	{
		newbase=(ElemType*)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
		if(newbase==NULL)
		exit(OVERFLOW);
		(*L).elem=newbase;
		(*L).listsize+=LISTINCREMENT;//���Ӵ洢����+1
	}
		q=(*L).elem+i-1;//qΪ����λ�ã���0��ʼ����
		for(p=(*L).elem+(*L).length-1;p>=q;p--)
		{
			*(p+1)=*p; //�Ѳ���λ��֮���Ԫ������ƶ�һλ
		 }
		 *q=e; //����e
		 (*L).length++;
		 return OK;
}

//���Ա�L�Ѵ��ڡ�1<= i <= L.length
//ɾ�����Ա��е�i��Ԫ��,����e���ر�ɾ����ֵ
Status iDeleteList(SqList *L,int i,ElemType *e)
{
	ElemType *p,*q;
	if(i<1||i>(*L).length)
	return ERROR;
	p=(*L).elem+i-1;	/*pָ��ָ���i��Ԫ�صĵ�ַ*/
	*e=*p;		/*�ѵ�i����ַ��ֵ����e*/
	q=(*L).elem+(*L).length-1;	/*q����ֵΪ�����Ա�����ַ*/
	for(p;p<=q;p++)		/*��p����ַ��ʼ���Ѻ�һ��ֵ����ǰһ�����Ӷ��ﵽɾ��Ч��*/
	{
		*p=*(p+1);
	}
	(*L).length--;	/*���Ա��ʵ�ʴ洢ֵ�ĳ��ȼ�һ*/
	return OK;
}



//��e�������Ա��i��Ԫ�ص�ֵ
// (i < 1)||(i > ListLength(L)) : OVERFLOW.  1<= i <=ListLength(l) :OK
Status GetElemList(SqList *L,int i,ElemType *e)
{
	if(i<1||i>(*L).length)
		return (ERROR);
	else
	*e=*((*L).elem+i-1); //����ַ+i-1)�ǵ�i��Ԫ�صĵ�ַ
	return OK;
}


//����˳����е�һ����element��ȵ�Ԫ�ص�λ��
//��L�д�����element��ȵ�Ԫ�أ��򷵻ص�һ������������Ԫ��λ���������ڣ��򷵻�0
Status LocateElemList(SqList *L,ElemType e)
{
	int i;
	ElemType *p;
	p=(*L).elem;	/*p��ֵΪͷ��ַ*/
	for(i=1;i<=(*L).length;i++)
	{
		if(e==*p)
		{
			return i;
		}
		p++;	/*����ƶ����������Ա�*/
	}
	return FALSE;
}

//ɾ���������Ա��е��ظ�Ԫ��
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

//�����Ա���ֵΪe��Ԫ��ǰ����E�����ȼ�һ
Status eInsertList(SqList *L,ElemType e,ElemType E)
{
	ElemType *q,*p,*newbase;
	int i;
	i=LocateElemList(L,e);
	iInsertList(L,i,E);
 }

//ɾ�����б���ֵΪe��Ԫ��
Status  eDeleteList(SqList *L,ElemType e)
{
	ElemType *p,*q;
	int i;
	i=LocateElemList(L,e);
	if(i<1||i>(*L).length)
	return ERROR;
	p=(*L).elem+i-1;	/*pָ��ָ���i��Ԫ�صĵ�ַ*/
	q=(*L).elem+(*L).length-1;	/*q����ֵΪ�����Ա�����ַ*/
	for(p;p<=q;p++)		/*��p����ַ��ʼ���Ѻ�һ��ֵ����ǰһ�����Ӷ��ﵽɾ��Ч��*/
	{
		*p=*(p+1);
	}
	(*L).length--;	/*���Ա��ʵ�ʴ洢ֵ�ĳ��ȼ�һ*/
	return OK;
}

//������Ա��е�Ԫ��
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

