#include<stdio.h>
#include "single_list.h"
int main()
{
	LNode L;
	int N;
	InitList(&L);
	printf("�����봴������ĳ��ȣ�  ");
	scanf("%d",&N);
	Create_L(&L,N);
	printf("�˵��������е�����Ϊ��\n");
	Printf_L(&L);
	return 0;
 } 
