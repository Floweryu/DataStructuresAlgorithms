#include<stdio.h>
int cry(int n)
{
	if(n<=0)
	return 0;
	else
	return n+cry(n-1);
 } 
int main()
{
	int n,res;
	scanf("%d",&n);
	res=cry(n);
	printf("%d",res);
}
	
