#include<stdio.h>
int main()
{
	int i;
	for(i=1;i<=1000;i++)
	{
		if(i%5==0&&i%3==0)
		printf("great\n");
		else if(i%5==0)
		printf("fri\n");
		else if(i%3==0)
		printf("tri\n");
		else
		printf("%d\n",i);
	}
 } 
