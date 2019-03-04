#include<stdio.h>
#include<string.h>
int main()
{
	char str[11];
	gets(str);
	int length;
	length=strlen(str);
	printf("%d\n",length);
	for(int i=length-1;i>=0;i--)
	printf("%c",str[i]);
 } 
