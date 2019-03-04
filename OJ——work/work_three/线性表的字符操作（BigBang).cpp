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

/*���Ա�ṹ��Ķ���*/
typedef struct
{
	ElemType*elem;  //�洢�ռ��ַ
	int  length;	//��ǰ����Ԫ�صĸ���
	int  listsize;	//��ǰ������������Ԫ�ص����� 
 } SqList; 
 
 /*��������InitList()
  ���ܣ�����һ�������Ա�
  ����ֵ���洢����ʧ�ܣ�OVERFLOW
          �洢����ɹ���OK   */
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
 
 /*��������ListInsert������
  ��ʼ���������Ա�L�Ѵ��ڣ�1 <= i <=L.length + 1;
  ���ܣ������Ա��i��Ԫ��ǰ����e,��ĳ��ȼ�1
  ����ֵ��ʧ�ܣ�ERROR
          �ɹ���OK 	*/
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

/*��������ListDelete����
  ��ʼ���������Ա�L�Ѵ��ڡ�1<= i <= L.length
  ���ܣ�ɾ�����Ա��е�i��Ԫ��,����e���ر�ɾ����ֵ 
  ����ֵ��ʧ�ܣ�ERROR
          �ɹ���OK		*/
Status ListDelete(SqList &L,int i)
{
	ElemType *p,*q;
	if(i<1||i>L.length)
	return ERROR;
	p=L.elem+i-1;	/*pָ��ָ���i��Ԫ�صĵ�ַ*/ 
	//	e=*p;		/*�ѵ�i����ַ��ֵ����e*/ 
	q=L.elem+L.length-1;	/*q����ֵΪ�����Ա�����ַ*/ 
	for(p;p<=q;p++)		/*��p����ַ��ʼ���Ѻ�һ��ֵ����ǰһ�����Ӷ��ﵽɾ��Ч��*/ 
	{
		*p=*(p+1);
	}
	L.length--;	/*���Ա��ʵ�ʴ洢ֵ�ĳ��ȼ�һ*/ 
	return OK;
}

/*��������LocateElem()
  ���ܣ�����˳����е�һ����element��ȵ�Ԫ�ص�λ�� 
  ����ֵ����L�д�����element��ȵ�Ԫ�أ��򷵻ص�һ������������Ԫ��λ��
          �������ڣ��򷵻�0		*/
Status LocateElem(SqList &L,ElemType e,Status(*compare)(ElemType,ElemType))
{
	int i; 
	ElemType *p;
	p=L.elem;	/*p��ֵΪͷ��ַ*/ 
	for(i=1;i<=L.length;i++)
	{
		if(compare(*p,e))	
		{
			return i;
		}
		p++;	/*����ƶ����������Ա�*/ 
	}
	return FALSE;
}

/*��������ListSee()
  ���ܣ�������Ա��е�Ԫ��	*/
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
//�ж���Ԫ���Ƿ���ȣ���ͬ����1����ͬ����0
Status cmp(ElemType e1,ElemType e2)
{
	return (Status)!strcmp(e1.name,e2.name);
}

int main()
{
	SqList La;		//����һ�����Ա� 
	ElemType e;		//����洢���ֵ��ַ����� 
	int a;		//�洢λ��
	char str[10];	//������ȡָ��
	InitList(La);
	while(scanf("%s",str)!=EOF)
	{
		if(strcmp(str,"insert")==0)		//����Ԫ��
		{
			scanf("%d%s",&a,e.name);		//�������λ�úͲ���Ԫ��
			ListInsert(La,a,e); 
		}
		else if(strcmp(str,"delete")==0)	//ɾ��Ԫ��
		{
			scanf("%s",e.name);
			ListDelete(La,LocateElem(La,e,cmp));
		} 
		else if(strcmp(str,"show")==0)	//�������Ա���Ԫ��
		{
			ListSee(La);
		} 
		else if(strcmp(str,"search")==0)	//����Ԫ�ص�λ��
		{
			scanf("%s",e.name);
			printf("%d\n",LocateElem(La,e,cmp));
		 } 
	} 
	return 0;	
 } 
