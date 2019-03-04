#include<stdio.h>
int main()
{
	int a1,b1,a2,b2,count,time;
	scanf("%d:%d %d:%d %d",&a1,&b1,&a2,&b2,&count);
	if(b2<b1&&a2>a1)
	{
		time=b2+60-b1+(a2-1-a1)*60+20*count;
	}
	else
	time=b2-b1+(a2-a1)*60+20*count;
	printf("%d\n",time);
 } 
