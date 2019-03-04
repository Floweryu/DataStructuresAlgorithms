#include<stdio.h>
#include "single_list.h"
int main()
{
	LNode L;
	int N;
	InitList(&L);
	printf("请输入创建链表的长度：  ");
	scanf("%d",&N);
	Create_L(&L,N);
	printf("此单向链表中的数据为：\n");
	Printf_L(&L);
	return 0;
 } 
