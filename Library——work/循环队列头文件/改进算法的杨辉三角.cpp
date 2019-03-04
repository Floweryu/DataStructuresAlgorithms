/*
	Name: 
	Copyright: 
	Author: 
	Date: 01/11/18 18:48
	Description: 	此程序只使用了一个队列进行操作。 
*/

#include "circle_queue.h"

int main()
{
	SqQueue q1;				 					//q1 队列存放杨辉三角数据，并承担计算 
	int n, num, i, j, e1, e2;					//n 表示输入的行数，num 表示要存入q1队列中的杨辉三角的数值 
						
	InitQueue(q1);								//初始化q1队列 
	while(scanf("%d", &n) != EOF)				//输入如多组数据 
	{	
		int len, len0 = 0, count = 3;			//len 表示队列长度，len0 表示每一行的长度，
												//count 表示从初始值 3 位置开始输出杨辉三角 
		for(i = 0; i <= n; i++)		
		{
			if(i == 0)							//这行是初始化前面的数据，不必输出 
			{	
				InsertQueue(q1, 0);				
				InsertQueue(q1, 1);
				InsertQueue(q1, 0);
			
				num = 1;						
			}	//end if
			
			else
			{
				len = LengthQueue(q1);			//计算队列的长度 
				InsertQueue(q1, 0);				//在上一行结束后，下一行开始前插入 0  
				for(j = len0; j < len-1; j++)	//从该行的第一个位置开始循环计算 
				{	
					GetQueue(q1, j, e1);		//得到相邻两个位置的值 
					GetQueue(q1, j+1, e2);
					num = e1 + e2;			 	//相加 
					
					InsertQueue(q1, num);		//保存到q1队列后面 
					
				}	// end while 
				len0 = len;						//len0 等于上一次队列的长度 
				InsertQueue(q1, 0);				//每行结束后在末尾插入 0  
					
			} // end else
			
		}	// end for
	
		for(i = 1; i <= n; i++)					//输出 n 行 
		{		
			for(j = 1; j <= n - i + 1; j++)		//每行输出的空格数关系 
				printf("  ");
			for(j = 1; j <= i + 3; j++)			//q1 队列中对应的每行的个数 
			{
				GetQueue(q1, count, num);		//得到指定位置的值 
				if(num)							//如果不是 0  
				printf("%d   ", num);			//输出该数据 
				
				count++;						//位置后移 
			}		
			printf("\n");					
		}
		
		ClearQueue(q1);							//清空队列q1 

	}	//end while
	
}
