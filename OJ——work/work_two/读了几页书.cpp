#include<stdio.h>
int main()
{
	int x,m,n,sum=0,i,y=0;
	scanf("%d %d %d",&x,&m,&n);
	for(i=1;i<=n;i++)
	{
		y=(i-1)*m+x; 
		sum=sum+y;
	}
	printf("%d\n",sum);
 } 
