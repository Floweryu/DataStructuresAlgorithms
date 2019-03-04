#include<iostream>
#include<string>

using namespace std;

void get_next(string T, int next[])			//得到 next 数组函数 
{
	int i = 0, j = -1;						//从第一个字符开始比较，i = 0 。 j 的初始值应该和 next 数组的第一个存储值一样 
	
	next[0] = -1;							// next 数组第一个地址存 -1 。没有从 next[1] 存数 
	
	while(i < T.size() - 1)					//如果 T.size()是 5 ，当 i 循环到 3 时 next 数组已经存了 4 地址即5个数。 
	{
		if(j == -1 || T[i] == T[j])
		{
			i++;
			j++;
			next[i] = j;					//如果相等， next + 1;
		}
		else
			j = next[j];					//否则，j 等于失配处的 next 值。 
	}
	
}

void get_nextval(string T, int nextval[])	//改进的 KMP 算法 ，当相同字符个数多时可以简单 
{
	int i = 0, j = -1;
	nextval[0] = -1;						//与 上面 的不同 
	while(i < T.size() - 1)
	{
		if(j == -1 || T[i] == T[j])
		{
			i++;
			j++;
			if(T[i] != T[j])
			{
				nextval[i] = j;				//与 上面 的不同 
			}
			else
			nextval[i] = nextval[j];		//与 上面 的不同 
		}
		else
			j = nextval[j];					//与 上面 的不同 
	}	
}

int Index_KMP(string S, string T, int pos, int next[])
{
	int i = pos, j = 0;								// pos 值我认为应该确定，不知道为什么要函数传递 
	
	while(i < (int)S.size() && j < (int)T.size())	//当 i 和 j 都不超过他们对应的字符长度时 
	{
		if(j == -1 || S[i] == T[j])					//如果相等，就遍历 
		{
			i++;
			j++;
		}		
		else										//否则 
			j = next[j];							//模式串向右移动 
	}

	if(j >= T.size())								//当 j 大于模式串长度时，说明把模式串经历了一遍 
		return i - T.size() + 1;					/*此时 i 指到模式串最后一个字符在主串中的位置，要减去模式串长度。
													  由于从 0 开始存数，所以加上一方便查看  */ 
	else		
		return 0;
	 
}

int main()
{
	cout<<"************************************"<<endl;
	cout<<"*******KMP原始算法    enter  a *****"<<endl;
	cout<<"*******KMP改进算法    enter  b *****"<<endl;
	cout<<"************************************"<<endl; 
	string s1, s2;
	int *p, i;
	char str;
	
	cout<<"主串为："<<endl;						//输入主串 
	cin>>s1;
	cout<<"子串为："<<endl;						//输入子串 
	cin>>s2;
		
	do
	{
		cout<<endl;
		cout<<"Please enter a char  :   ";
		cin>>str;
		switch(str)
		{
			case 'a':
				{
					p = new int[s2.size()];	
					
					get_next(s2, p);							//得到 next 数组并输出 
					
					cout<<"next 数组为："<<endl;
					for(i = 0; i < s2.size(); i++)
						cout<<*(p+i)<<" "; 
						cout<<endl;
	 
					i = Index_KMP(s1, s2, 0, p);				//返回匹配位置 
	
					if(i)
						cout<<"在第"<<i<<"个字符处匹配"<<endl;
					else
						cout<<"不成功"<<endl;
							
					delete [] p;
					
					break;
				}
				
			case 'b':
				{
					p = new int[s2.size()];	
		
					get_nextval(s2, p);	
					
					cout<<"nxtval数组为："<<endl;			
					for(i = 0; i < s2.size(); i++)
						cout<<*(p+i)<<" "; 
					cout<<endl;
	 
					i = Index_KMP(s1, s2, 0, p);
	
					if(i)
						cout<<"在第"<<i<<"个字符处匹配"<<endl;
					else
						cout<<"不成功"<<endl;
					delete [] p;
					
					break;
				}
		}

	}while(str != 'q');
 } 
