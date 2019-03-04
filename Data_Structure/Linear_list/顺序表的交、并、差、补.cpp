#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include "singlelist.h"

//����������La��Lb�е�Ԫ�ذ�ֵ�ķǼ�����
//�鲢������Ա�Lc������Ԫ��Ҳ��ֵ�ǵݼ�����
 Status MergeList(SqList *La,SqList *Lb,SqList *Lc)
 {
 	ElemType ai,bj;
 	int i = 1, j = 1, k = 1;
 	
 	(*La).length = LengthList(La);				/*�õ�La�ĳ���*/ 
 	(*Lb).length = LengthList(Lb);				/*�õ�Lb�ĳ���*/ 
 	
 	while((i <= (*La).length) && (j <= (*Lb).length))	/*��La��Lb����û�б�������У���һ�������꼴�˳�ѭ��*/ 
 	{
 		GetElemList(La, i, &ai);					/*�õ�La��iλ�õ�Ԫ��*/ 
 		GetElemList(Lb, j, &bj);					/*�õ�Lb��jλ�õ�Ԫ��*/
 		
 		if(ai <= bj)								/*���La�е�Ԫ��С��Lb�е�*/ 
 		{
 			InsertList(Lc, k++, ai);				/*��La(��С�Ĳ��뵽Lc����*/ 
 			i++;									/*La��Ԫ��λ�ü�һ���ж���һ��Ԫ��*/ 
		 }
		 else
		 {
		 	InsertList(Lc, k++, bj);				/*��Lb(����Ĳ��뵽Lc����*/ 
		 	j++;									/*Lb��Ԫ��λ�ü�һ���ж���һ��Ԫ��*/ 
		 }
	 }
	 /*�˳�����ѭ��������La��Lb��һ�������Ѿ�������ɣ�������ֻ��Ҫ��û�б��������Ա���*/ 
	 while(i <= (*La).length)		 				/*��La�����Ԫ�ؽӵ�Lc�ĺ���*/ 
	 {
	 	GetElemList(La,i++,&ai);	
	 	InsertList(Lc,k++,ai);
	 }
	 
	 while(j <= (*Lb).length)						/*��Lb�����Ԫ�ؽӵ�Lc�ĺ���*/
	 {
	 	GetElemList(Lb,j++,&bj);
	 	InsertList(Lc,k++,bj);
	 }
} 


//�����в������Ա�La�е���La�е����ݲ��뵽La�У�����ѧ�����ϵĲ���
/*  ˵�����ú�������ȷ�ģ�����������ڴ˳���Ĳ˵��в�������ִ�У�
		  ��Ϊ���ı������Ա�La�еĴ洢���ݣ���La�����������������
		  ���ǿ���ʹ�����ĸĽ�������		 */  
Status UnionList(SqList *La, SqList *Lb)
{
	(*La).length = LengthList(La);
	(*Lb).length = LengthList(Lb);
	
	int i, k;
	ElemType e;
	
	for(i = 1; i <= (*Lb).length; i++)
	{
		GetElemList(Lb,i,&e);				//��Lb�л�ø�λ�õ�Ԫ��
		k = LocateElemList(La,e);			//���ظ�Ԫ����La�е�λ��
		
		if(k == 0)							//���La�в�������e��ͬ��Ԫ�أ���λ�÷���Ϊ0������� 
			InsertList(La,(*La).length+1,e);
	}
 } 					
 	
//����������La,Lbȡ��������ȡ��ͬԪ�طŵ�Lc���Ա���
Status MixList(SqList *La,SqList *Lb,SqList *Lc)
{
	ElemType e;
	int i, k, j=1;
	
	(*La).length = LengthList(La);
	(*Lb).length = LengthList(Lb);
	
	for(i = 1;i <= (*La).length; i++)
	{
		GetElemList(La,i,&e);				/*��La��λ��i����Ԫ�ظ���e.*/ 
		k = LocateElemList(Lb,e);			/*�ж�e��Lb����û�У��оͷ���λ�ã�û�з���0.*/ 
		
		if(k)								/*�����Lb������e��ͬ��Ԫ�أ������*/ 
			InsertList(Lc,j++,e);
	}
}

//����������ȡ���ȡ�������ϲ�ͬ��Ԫ�أ������ѽ�����뵽Lc�С� 
 Status DifferList(SqList *La,SqList *Lb,SqList *Lc)
{
	ElemType e;
	int i, k, j = 1;
	
	(*La).length = LengthList(La);
	(*La).length = LengthList(Lb);
	
	for(i = 1; i <= (*La).length; i++)
	{
		GetElemList(La,i,&e);				/*��La��λ��i����Ԫ�ظ���e.*/ 
		k = LocateElemList(Lb,e);			/*�ж�e��Lb����û�У��оͷ���λ�ã�û�з���0.*/ 
		
		if(!k)								/*�����Lb��û����e��ͬ��ֵ���Ͳ��롣*/ 
			InsertList(Lc,j++,e);
	}
	
	for(i = 1; i <= (*Lb).length; i++)
	{
		GetElemList(Lb,i,&e);				/*��Lb��λ��i����Ԫ�ظ���e.*/ 
		k = LocateElemList(La,e);				/*�ж�e��La����û�У��оͷ���λ�ã�û�з���0.*/ 
		if(!k)								/*�����La��û����e��ͬ��ֵ���Ͳ��롣*/ 
		
			InsertList(Lc,j++,e);
	}
}

//La�൱�ڴ�ļ��ϣ���La��Lbû�еļ��������Lc�У�
//����Lb��La�еĲ�����		*/
Status CompleList(SqList *La,SqList *Lb,SqList *Lc)
{
	ElemType e;
	int i, k, j = 1;
	
	(*La).length = LengthList(La);
	(*La).length = LengthList(Lb);
	
	for(i = 1; i <= (*La).length; i++)
	{
		GetElemList(La,i,&e);
		k = LocateElemList(Lb,e);
		
		if(!k)
			InsertList(Lc,j++,e);
	}
 } 
 
 
 
 
 
 
 
 
 int main()
 {
 	
 	printf("********�˳���Ĺ�����ִ�м��ϵĽ�������밴��ʾ���в���********\n");
 	printf("********        ��La��Lb���и�ֵ��Please enter 'a'        ********\n");
 	printf("********    ��La��Lb�������򲢼�������Please enter 'b'    ********\n");
 	printf("********    ��La��Lb������ѧ����������Please enter 'c'    ********\n");
 	printf("********    ��La��Lb���н���������Please enter 'd'        ********\n");
 	printf("********    ��La��Lb���в������Please enter 'e'        ********\n");
 	printf("********    ��La��Lb���в���������Please enter 'f'        ********\n");
 	Status back;
 	SqList La,Lb,Lc;
 	int N1,N2;
 	back=InitList(&La);
 	if(back)
 	printf("La���Ա�ֵ�ɹ�!!!\n");
 	back=InitList(&Lb);
 	if(back)
 	printf("La���Ա�ֵ�ɹ�!!!\n");
 	printf("��ΪLa��ֵ.\n");
 	printf("��ȷ���������ݵĸ�����  ");
	scanf("%d",&N1);
	printf("���������ݣ��Կո������\n");	
	CreateList(&La,N1);
	printf("��ΪLb��ֵ.\n");
 	printf("��ȷ���������ݵĸ�����  ");
	scanf("%d",&N2);
	printf("���������ݣ��Կո������\n");	
	CreateList(&Lb,N2);
	
	
	char str;
	do
	{
		printf("\n");
		printf("Please enter a char :    ");
		str=getche();
		printf("\n");
		switch(str)
		{
			case 'b':  /*��La��Lb�������򲢼�����*/
					{
						InitList(&Lc);
						MergeList(&La,&Lb,&Lc);
						printf("����La�뼯��Lb�����򲢼�Ϊ��\n");
						PrintfList(&Lc);
						break;
					 }
			case 'c':  /* ��La��Lb������ѧ��������*/
					{
						UnionList(&La,&Lb);
						printf("����La�뼯��Lb����ѧ����Ϊ��\n");
						PrintfList(&La);
						break;	
					}
			case 'd':	/*��La��Lb���н�������*/
					{
						InitList(&Lc);
					 	MixList(&La,&Lb,&Lc);
						printf("����La�뼯��Lb�Ľ���Ϊ��  \n");
						PrintfList(&Lc);
						break;	
					}
			case 'e':	/* �Լ���La��Lb���в���� */
					{
						InitList(&Lc);
						DifferList(&La,&Lb,&Lc);
						printf("����La�뼯��Lb�ĲΪ��  \n");
						PrintfList(&Lc);
						break;
					}
			case 'f':	/*��Lb��La�еĲ���*/
					{
						InitList(&Lc);
						CompleList(&La,&Lb,&Lc);
						printf("Lb��La�еĲ���Ϊ��\n");
						PrintfList(&Lc); 
						break;
					}
			default:printf("wrong!\n");
		}
	}while(str!='q');
}
/*	//��La��Lb�������򲢼����� 
	MergeList(La,Lb,Lc);
	printf("����La�뼯��Lb�����򲢼�Ϊ��\n");
	ListSee(Lc);
	//��La��Lb������ѧ��������
	Union_Sq(La,Lb);
	printf("����La�뼯��Lb����ѧ����Ϊ��\n");
	ListSee(La);								
	//��La��Lb���н�������
	Mix_Sq(La,Lb,Lc);
	printf("����La�뼯��Lb�Ľ���Ϊ��  \n");
	ListSee(Lc);								 
	//�Լ���La��Lb���в���� 
	Differ_Sq(La,Lb,Lc);
	printf("����La�뼯��Lb�ĲΪ��  \n");
	ListSee(Lc);								
	//��Lb��La�еĲ���
	Comple_Sq(La,Lb,Lc);
	printf("Lb��La�еĲ���Ϊ��\n");
	ListSee(Lc); 							*/
	 
	
	 
	
 	
 
