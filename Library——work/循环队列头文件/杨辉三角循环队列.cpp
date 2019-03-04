#include "circle_queue.h"

int main()
{
	SqQueue q1, q2, temp, q3;					// q1 存放每行数据；q2 存放由q1中计算的下一行数据，
												//temp为q1和q2交换的中间数组，q3是用来存放最终要输出的数据 
	int n, num, e, i, j;						//n 是要输出杨辉三角的行数，num 存放每行要输出的数据，e接收函数返回值，i,j为计数器 
	
	InitQueue(q1);								//初始化定义q1,q2,q3,temp; 
	InitQueue(q2);
	InitQueue(temp);
	InitQueue(q3);
	
	while(scanf("%d", &n) != EOF)				//多组数据输入 
	{
		for(i = 0; i <= n; i++)					//由于第一行特殊情况不输出，所以实际输出还是 1 ~ n 行。 
		{
			if(i == 0)							//第 0 行， 
			{	
				InsertQueue(q1, 0);				//在 q1 中存入的起始行为 0 1 0 
				InsertQueue(q1, 1);
				InsertQueue(q1, 0);
			
				num = 1;						//第 0 行应该输出的数，实际没有输出 
			}	//end if
			
			else
			{
				InsertQueue(q2, 0);				//q1队列计算完成后，先向 q2 中插入 0 
				while(LengthQueue(q1) != 1)		//当 q1 队列长度不为 1 时 
				{	
					DeleteQueue(q1, num);		//删除头部的值并返回到 num 上 ，此值为 0 

					GetHeadQueue(q1, e);		//得到下一个值，返回到 e 上 

					num = num + e;				//将相邻两个数的值相加赋给 num，因为要输出 

					InsertQueue(q2, num);		//将得到的新一行的值存到 q2 队列中，因为 q1 队列还要计算。此处可以优化。 
					
					InsertQueue(q3, num);		//将得到的要输出的值存到q3中保存 
				}	// end while 
				InsertQueue(q2, 0);				//将 q2 队列的尾部存入0 
					
				temp = q1;						//把q2队列内容与q1队列交换 
				q1 = q2;
				q2 = temp;
				
				ClearQueue(q2);					//清空 q2 队列，以备下次使用 
			} // end else
			
		}	// end for
		for(i = 0; i < n; i++)					//输出n行杨辉三角 
		{		
			for(j = 0; j <= n - i; j++)			//在每行前输出 n - i 个空格 
				printf("  ");
			for(j = 0; j < i + 2; j++)			//每行输出的数据个数是 i + 2 个，因为 i 从 0 开始计数 
			{
				DeleteQueue(q3, e);				//输出并删除队头元素 
				printf("%d   ", e);
			}	
			printf("\n");						//输完没行后换行 
		}
		
		ClearQueue(q1);							//清空 q1 , q3 队列 
		ClearQueue(q3);
	}	//end while
}
