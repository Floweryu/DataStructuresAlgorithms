#include<stdio.h>
#include<string.h>
int main()
{
	int n,len,i,j;
	scanf("%d",&n);
	char str1[1000];
	while(n--)
	{
		int count=0;
		scanf("%s",str1);
		len=strlen(str1);
		char str2[len];
		for(j=0,i=len-1;j<len,i>=0;i--,j++)
			str2[j]=str1[i];
		for(i=0;i<len;i++)
		{
			if(str1[i]==str2[i])
				count++;
		}
		if(count==len)
		printf("YES\n");
		else
		printf("NO\n");
	}
}
