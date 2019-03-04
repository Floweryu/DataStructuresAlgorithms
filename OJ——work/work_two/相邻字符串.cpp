#include<stdio.h>
#include<string.h>
int main()
{
	char str[1000];
	gets(str);
	int i,len;
	len=strlen(str);
	for(i=0;i<len-1;i++)
	{
		if(str[i]==str[i+1])
		{
			printf("%c\n",str[i]);
			break;
		}
	}
	if(i==len-1)
	printf("No\n");				
}
