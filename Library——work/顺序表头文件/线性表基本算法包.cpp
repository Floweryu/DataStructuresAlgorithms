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

int main()
{

		printf("The functions of this program are as follows, please follow the instructions to operate:\n");
		printf("********************************************************************************\n");
		printf("      *****���ܣ������Ա�ֵ                               please enter  a   **\n");
		printf("      *****���ܣ��ж����Ա��Ƿ�Ϊ��                         please enter  b   **\n");
		printf("      *****���ܣ��������Ա���                             please enter  c   **\n");
		printf("      *****���ܣ������Ա��i��Ԫ��ǰ����e,��ĳ��ȼ�1       please enter  d   **\n");
		printf("      *****���ܣ�ɾ�����Ա��е�i��Ԫ��,����e���ر�ɾ����ֵ  please enter  e   **\n");
		printf("      *****���ܣ���e�������Ա��i��Ԫ�ص�ֵ                 please enter  f   **\n");
		printf("      *****���ܣ�����˳����е�һ����element��ȵ�Ԫ�ص�λ��please enter  g   **\n");
		printf("      *****���ܣ�������Ա��е�Ԫ��                         please enter  h   **\n");
		printf("      *****���ܣ�������Ա�                                 please enter  i   **\n");
		printf("      *****���ܣ�ɾ�����Ա����ظ���Ԫ�ء�                   please enter  j   **\n");
		printf("      *****���ܣ������Ա���ֵΪe��Ԫ��ǰ����E��             please enter  k   **\n");
		printf("      *****���ܣ�ɾ�����Ա���ֵΪe��Ԫ��                    please enter  l   **\n");
		printf("********************************************************************************\n");
		printf("\n");
		SqList La;	/*����main()�����е����Ա�*/ 
		char str;	/*�Ӽ��̽���һ���ַ�*/ 
		Status back;	/*���庯�����صı�ʾ�߼��жϵ�*/ 
		int I,N,k;		/*I�� ��ʾλ�õģ�N��ʾ��ֵ�ĸ�����kΪ���صı�ĳ��Ȼ��������δ���*/ 
		ElemType E,M;		/* E�Ƿ���ĳλ�õ�Ԫ�ص�ֵ*/ 
		back=InitList(&La);	/*��ʼ�����Ա�*/ 
		if(back) 
		printf("��ʼ���ɹ�!!!\n");
		
	do
	{
		printf("\n");
		printf("Please enter a char:    ");
		str=getche();/*�Ӽ��̻�ȡһ���ַ�����ʾ�������س�ֱ��ִ��*/ 
		printf("\n");/*	getchar();	/*�����������Ļس���������س���Ҳ�ᱻ��Ϊ���ַ�*/ 
		switch(str)
			{
				case 'a': /*�����Ա�ֵ*/
						{
							printf("��ȷ���������ݵĸ�����  ");
							scanf("%d",&N);
							printf("���������ݣ��Կո������\n");	
							CreateList(&La,N);
							break;
						}
				case 'b':/*�ж����Ա��Ƿ�Ϊ��*/
						{
				      		back=EmptyList(&La);
							if(!back)
							printf("This is an empty list\n");
							else
							printf("This is not an empty list.\n");
							break;
						}
				case 'c':/*�������Ա���  */ 
						{
							k=LengthList(&La);
							printf("The length of the list is :  %d",k);
							printf("\n");
							break;
						}
				case 'd':/* �����Ա��i��Ԫ��ǰ����e,��ĳ��ȼ�1 */ 
						{
							printf("���������Ԫ�ص�λ�ã�  ");
							scanf("%d",&I);
							printf("���������Ԫ�ص�ֵ��  ");
							scanf("%d",&E); 
							back=iInsertList(&La,I,E);
							if(back)
							PrintfList(&La);
							printf("\n");
							break;
						}
				case 'e':/*ɾ�����Ա��е�i��Ԫ��,����e���ر�ɾ����ֵ*/ 
						{
							printf("������ɾ��Ԫ�ص�λ�ã�  ");
							scanf("%d",&I);
							back=iDeleteList(&La,I,&E);
							if(back)
							{
								printf("ɾ����λ�õ�Ԫ��ֵΪ:  %d\n",E);
								printf("ɾ�������Ա�Ϊ:\n");
								PrintfList(&La);
								printf("\n");
							}
							break;
						}
				case 'f':/*��e�������Ա��i��Ԫ�ص�ֵ */ 
						{
							printf("��Ҫ���ҵڼ���Ԫ��:   ");
							scanf("%d",&I); 
							back=GetElemList(&La,I,&E);
							if(back)
							printf("��  %d  ��Ԫ�ص�ֵΪ��  %d\n",I,E);
							else
							printf("��λ��û�д洢Ԫ��\n");
							break;
						}
				case 'g':/*����˳����е�һ����element��ȵ�Ԫ�ص�λ��*/ 
						{
							printf("��������֪���Ƿ��ڱ��е���ֵ��  ");
							scanf("%d",&E);
							k=LocateElemList(&La,E);
							if(k)
								printf("ֵΪ  %d  �Ǳ��еĵ�  %d  ��Ԫ��\n",E,k);
							else
								printf("�����Ա���û��ֵΪ%d��Ԫ��\n",E);
							break;
						}
				case 'h':/*������Ա��е�Ԫ��*/ 
						{
							printf("���Ա��и�Ԫ�ص�ֵΪ��\n");
							PrintfList(&La);
							printf("\n");
							break;
						}
				case 'i':/*������Ա� */ 
						{
							back=ClearList(&La);
							if(back)
								printf("���Ա��ѱ���ա�\n");
							break;
						}
				case 'j'://ɾ�����Ա��е��ظ�Ԫ��
						{
							DeleteReList(&La);
							PrintfList(&La);
							break;
						}
				case 'k'://�����Ա���ֵΪe��Ԫ��ǰ����E
						{
							printf("��������ֵΪ�ĸ�Ԫ��ǰ���룺  ");
							scanf("%d",&M);
							printf("���������Ԫ�ص�ֵ��  ");
							scanf("%d",&E); 
							back=eInsertList(&La,M,E);
							if(back)
							PrintfList(&La);
							else
							printf("����ʧ��\n");
							printf("\n");
							break;
						}
				case 'l'://ɾ�����б���ֵΪe��Ԫ��
						{
							printf("������ɾ��Ԫ�ص�ֵ��  ");
							scanf("%d",&E);
							back=eDeleteList(&La,E);
							if(back)
							{
								printf("ɾ�������Ա�Ϊ:\n");
								PrintfList(&La);
							}
							else
								printf("ɾ��ʧ��\n");
							printf("\n");
							break;
						}
				default:printf("wrong!\n");
			}
	}while(str!='q');
} 
   
