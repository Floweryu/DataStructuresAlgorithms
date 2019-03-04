#include<stdio.h>
int main()
{
	int a,b,c;
	while(scanf("%d %d",&a,&b)!=EOF)
	{
		if(!b)
		{
			printf("error\n");
		}
		else
		{
			printf("%d\n",(a+b/2)/b);
		}
	}
}
