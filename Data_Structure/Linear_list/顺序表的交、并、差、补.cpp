#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include "singlelist.h"

//将两个集合La，Lb中的元素按值的非减排列
//归并后的线性表Lc的数据元素也按值非递减排列
 Status MergeList(SqList *La,SqList *Lb,SqList *Lc)
 {
 	ElemType ai,bj;
 	int i = 1, j = 1, k = 1;
 	
 	(*La).length = LengthList(La);				/*得到La的长度*/ 
 	(*Lb).length = LengthList(Lb);				/*得到Lb的长度*/ 
 	
 	while((i <= (*La).length) && (j <= (*Lb).length))	/*当La和Lb都还没有遍历完进行，有一个遍历完即退出循环*/ 
 	{
 		GetElemList(La, i, &ai);					/*得到La在i位置的元素*/ 
 		GetElemList(Lb, j, &bj);					/*得到Lb在j位置的元素*/
 		
 		if(ai <= bj)								/*如果La中的元素小于Lb中的*/ 
 		{
 			InsertList(Lc, k++, ai);				/*把La(即小的插入到Lc表中*/ 
 			i++;									/*La中元素位置加一，判断下一个元素*/ 
		 }
		 else
		 {
		 	InsertList(Lc, k++, bj);				/*把Lb(即大的插入到Lc表中*/ 
		 	j++;									/*Lb中元素位置加一，判断下一个元素*/ 
		 }
	 }
	 /*退出上面循环即表明La或Lb有一个链表已经遍历完成，接下来只需要对没有遍历的线性表处理*/ 
	 while(i <= (*La).length)		 				/*把La后面的元素接到Lc的后面*/ 
	 {
	 	GetElemList(La,i++,&ai);	
	 	InsertList(Lc,k++,ai);
	 }
	 
	 while(j <= (*Lb).length)						/*把Lb后面的元素接到Lc的后面*/
	 {
	 	GetElemList(Lb,j++,&bj);
	 	InsertList(Lc,k++,bj);
	 }
} 


//将所有不在线性表La中但在La中的数据插入到La中，即数学意义上的并集
/*  说明：该函数是正确的，但是如果放在此程序的菜单中不能连续执行，
		  因为它改变了线性表La中的存储数据，是La不是我们输入的数据
		  我们可以使用它的改进函数。		 */  
Status UnionList(SqList *La, SqList *Lb)
{
	(*La).length = LengthList(La);
	(*Lb).length = LengthList(Lb);
	
	int i, k;
	ElemType e;
	
	for(i = 1; i <= (*Lb).length; i++)
	{
		GetElemList(Lb,i,&e);				//从Lb中获得该位置的元素
		k = LocateElemList(La,e);			//返回该元素在La中的位置
		
		if(k == 0)							//如果La中不存在与e相同的元素，即位置返回为0，则插入 
			InsertList(La,(*La).length+1,e);
	}
 } 					
 	
//对两个集合La,Lb取交集，即取相同元素放到Lc线性表中
Status MixList(SqList *La,SqList *Lb,SqList *Lc)
{
	ElemType e;
	int i, k, j=1;
	
	(*La).length = LengthList(La);
	(*Lb).length = LengthList(Lb);
	
	for(i = 1;i <= (*La).length; i++)
	{
		GetElemList(La,i,&e);				/*把La中位置i处的元素赋给e.*/ 
		k = LocateElemList(Lb,e);			/*判断e在Lb中有没有，有就返回位置，没有返回0.*/ 
		
		if(k)								/*如果在Lb中有与e相同的元素，则插入*/ 
			InsertList(Lc,j++,e);
	}
}

//对两个集合取差（即取两个集合不同的元素），并把结果放入到Lc中。 
 Status DifferList(SqList *La,SqList *Lb,SqList *Lc)
{
	ElemType e;
	int i, k, j = 1;
	
	(*La).length = LengthList(La);
	(*La).length = LengthList(Lb);
	
	for(i = 1; i <= (*La).length; i++)
	{
		GetElemList(La,i,&e);				/*把La中位置i处的元素赋给e.*/ 
		k = LocateElemList(Lb,e);			/*判断e在Lb中有没有，有就返回位置，没有返回0.*/ 
		
		if(!k)								/*如果在Lb中没有与e相同的值，就插入。*/ 
			InsertList(Lc,j++,e);
	}
	
	for(i = 1; i <= (*Lb).length; i++)
	{
		GetElemList(Lb,i,&e);				/*把Lb中位置i处的元素赋给e.*/ 
		k = LocateElemList(La,e);				/*判断e在La中有没有，有就返回位置，没有返回0.*/ 
		if(!k)								/*如果在La中没有与e相同的值，就插入。*/ 
		
			InsertList(Lc,j++,e);
	}
}

//La相当于大的集合，把La中Lb没有的集合输出到Lc中，
//即求Lb在La中的补集。		*/
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
 	
 	printf("********此程序的功能是执行集合的交并差补，请按提示进行操作********\n");
 	printf("********        对La，Lb进行赋值，Please enter 'a'        ********\n");
 	printf("********    对La，Lb进行排序并集操作，Please enter 'b'    ********\n");
 	printf("********    对La，Lb进行数学并集操作，Please enter 'c'    ********\n");
 	printf("********    对La，Lb进行交集操作，Please enter 'd'        ********\n");
 	printf("********    对La，Lb进行差集操作，Please enter 'e'        ********\n");
 	printf("********    对La，Lb进行补集操作，Please enter 'f'        ********\n");
 	Status back;
 	SqList La,Lb,Lc;
 	int N1,N2;
 	back=InitList(&La);
 	if(back)
 	printf("La线性表赋值成功!!!\n");
 	back=InitList(&Lb);
 	if(back)
 	printf("La线性表赋值成功!!!\n");
 	printf("请为La表赋值.\n");
 	printf("请确定输入数据的个数：  ");
	scanf("%d",&N1);
	printf("请输入数据，以空格隔开：\n");	
	CreateList(&La,N1);
	printf("请为Lb表赋值.\n");
 	printf("请确定输入数据的个数：  ");
	scanf("%d",&N2);
	printf("请输入数据，以空格隔开：\n");	
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
			case 'b':  /*对La，Lb进行排序并集操作*/
					{
						InitList(&Lc);
						MergeList(&La,&Lb,&Lc);
						printf("集合La与集合Lb的排序并集为：\n");
						PrintfList(&Lc);
						break;
					 }
			case 'c':  /* 对La，Lb进行数学并集操作*/
					{
						UnionList(&La,&Lb);
						printf("集合La与集合Lb的数学并集为：\n");
						PrintfList(&La);
						break;	
					}
			case 'd':	/*对La，Lb进行交集操作*/
					{
						InitList(&Lc);
					 	MixList(&La,&Lb,&Lc);
						printf("集合La与集合Lb的交集为：  \n");
						PrintfList(&Lc);
						break;	
					}
			case 'e':	/* 对集合La与Lb进行差集操作 */
					{
						InitList(&Lc);
						DifferList(&La,&Lb,&Lc);
						printf("集合La与集合Lb的差集为：  \n");
						PrintfList(&Lc);
						break;
					}
			case 'f':	/*求Lb在La中的补集*/
					{
						InitList(&Lc);
						CompleList(&La,&Lb,&Lc);
						printf("Lb在La中的补集为：\n");
						PrintfList(&Lc); 
						break;
					}
			default:printf("wrong!\n");
		}
	}while(str!='q');
}
/*	//对La，Lb进行排序并集操作 
	MergeList(La,Lb,Lc);
	printf("集合La与集合Lb的排序并集为：\n");
	ListSee(Lc);
	//对La，Lb进行数学并集操作
	Union_Sq(La,Lb);
	printf("集合La与集合Lb的数学并集为：\n");
	ListSee(La);								
	//对La，Lb进行交集操作
	Mix_Sq(La,Lb,Lc);
	printf("集合La与集合Lb的交集为：  \n");
	ListSee(Lc);								 
	//对集合La与Lb进行差集操作 
	Differ_Sq(La,Lb,Lc);
	printf("集合La与集合Lb的差集为：  \n");
	ListSee(Lc);								
	//求Lb在La中的补集
	Comple_Sq(La,Lb,Lc);
	printf("Lb在La中的补集为：\n");
	ListSee(Lc); 							*/
	 
	
	 
	
 	
 
