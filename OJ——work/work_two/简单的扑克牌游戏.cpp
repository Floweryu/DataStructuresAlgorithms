#include<stdio.h>
int main()
{
	int a,b,c,d,num1,num2;
	while(scanf("%d %d %d %d",&a,&b,&c,&d)!=EOF)
	{
		if(a==b&&c==d)
		{
			if(a>c)
			printf("A\n");
			else if(a<c)
			printf("B\n");
			else
			printf("N\n");
		}
		else if(a==b&&c!=d)
		printf("A\n");
		else if(c==d&&a!=b)
		printf("B\n");
		else
		{
			num1=(a+b)%10;
			num2=(c+d)%10;
			if(num1>num2)
			printf("A\n");
			else if(num1<num2)
			printf("B\n");
			else 
			printf("N\n");
		}
	}
}
