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

void get_nextval(string T, int nextval[])
{
	int i = 0, j = -1;
	nextval[0] = -1;
	while(i < T.size() - 1)
	{
		if(j == -1 || T[i] == T[j])
		{
			i++;
			j++;
			if(T[i] != T[j])
			{
				nextval[i] = j;
			}
			else
			nextval[i] = nextval[j];
		}
		else
			j = nextval[j];
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
	string s1, s2;
	int *p, i;
	while(cin>>s1>>s2)
	{
		p = new int[s2.size()];	
		
		get_nextval(s2, p);
		i = Index_KMP(s1, s2, 0, p);
		if(i)
			cout<<i<<endl;
		else
			cout<<"0"<<endl;
		
		delete [] p;
	}
 } 
