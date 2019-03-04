#include<stdio.h>
#include<string.h>
int main()
{
	int n;
	int a[1000];
	int i, j, t, k, flag1, flag2;
	while(scanf("%d",&n) != EOF)
	{
	if(n)
	{
		for(i = 0; i < n; i++)		//输入数据存到数组 a 中 
			scanf("%d",&a[i]);
		
		for(j = 0; j < a[0]; j++)	//对第一个数进行处理 
			printf("P");			
		printf("Q");				//第一个数最先出栈 
		
		for(i = 0, j = i+1; i < n, j < n; i++, j++)		//根据相邻两个数之差来判断 
		{	
			for(k = 0; k < j; k++)		//寻找 a[j]-1 是否在前面出现 
			{
				if((a[k]+1)== a[j])
				{
					flag1 = 1;			//出现 
					break;
				}
				else
					flag1 = 0; 			//没有出现 
			}
			
					
			t = a[j] - a[i];
			
			if(t >= 1)					//如果相差大于一 
			{	
				if(flag1 == 1)			//并且 a[j]-1 已经出现过 
				{
					printf("P");		//只需要进栈一次 
					printf("Q");
				}
				else					//并且 a[j]-1 没有出现过
				{
					for(k = 0; k < t; k++)		//进栈多次到 a[j] 
						printf("P");
					printf("Q");
				}
			}
				
			
			else if(t == -1)				//如果相邻两数递减 
					printf("Q");			//直接出栈 
					
			else if(t < -1)					//如果 a[j] 与前一个数差大于 -1 
			{
				int count = 0;
				for(k = 0; k < j; k++)		//判断比 a[j] 大的数是否已经全部出现 
				{
					if(a[k] > a[j])
						count++;
				}
				if(count == n - a[j])
					flag2 = 1;				//全部出现 
				else
					flag2 = 0;				//没全出现 
					
				if(flag2 == 1)				//如果全部出现，就不会有数在 a[j] 上面 
					printf("Q");
				else						//如果没有全部出现，有数在 a[j] 上面 ，a[j] 出不了栈 
				{	
					printf(" error");
					break;
				}
			}
		}
	}
		memset(a,0,sizeof(a));
		printf("\n");
	}
} 
