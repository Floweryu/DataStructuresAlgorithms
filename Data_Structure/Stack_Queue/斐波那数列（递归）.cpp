#include<stdio.h>
//#include<time.h>
int def(int n)
{
	if(n<3)
		return 1;
	else
		return def(n-1)+def(n-2);
} 

int main()
{
	int year, k;
//	int t1, t2;
	scanf("%d",&year);
//	t1 = clock();
	k = def(year);
//	t2 = clock();
	printf("%d\n",k);
///	printf("%d\n",t2 - t1);
}
