#include<stdio.h>
int main()
{
	int a1,b1,c1,a2,b2,c2,a3,b3,c3;
	int i;
	scanf("%d:%d:%d",&a1,&b1,&c1);
	scanf("%d:%d:%d",&a2,&b2,&c2);
	if(b2>=b1&&c2>c1)
	{
		a3=a2-a1;
		b3=b2-b1;
		c3=c2-c1;
	} 
	if(b2<b1&&c2<c1)
	{
		c3=c2+60-c1;
		b3=b2+59-b1;
		a3=a2-1-a1;
	}
	if(b2<b1&&c2>=c1)
	{
		c3=c2-c1;
		b3=b2+60-b1;
		a2--;
		a3=a2-a1;
	}
	if(c2<c1&&b2>=b1)
	{
		c3=c2+60-c1;
		b2--;
		b3=b2-b1;
		a3=a2-a1;
	}
	printf("%02d:%02d:%02d",a3,b3,c3);
 } 
