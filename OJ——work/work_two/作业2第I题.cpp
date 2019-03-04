#include<stdio.h>
#include<string.h>
int main()
{
    int i,j,k,len;
    char s[1000];
    while(scanf("%s",s)!=EOF)
    {
        int count=0;//count统计有几个正确的句子
        len=strlen(s);
        for(i=len-1;i>=0;i--)
        {
            if(s[i]>='p'&&s[i]<='z')
                count++;
            else if(s[i]=='N')
            {
                if(count==0)
                    break;
            }
            else if(s[i]=='C'||s[i]=='D'||s[i]=='E'||s[i]=='I')
            {
                if(count>=2)
                    count--;
                else
                {
                    count=0;
                    break;
                }
            }
            else
            {
                count=0;
                break;
            }
        }
        if(count==1)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
