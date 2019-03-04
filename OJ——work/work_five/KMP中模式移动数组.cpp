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

int main()
{
	string s;
	cin>>s;
	int *p, i;
	p = new int[s.size()];
		
	get_next(s, p);							//得到 next 数组并输出 
	for(i = 0; i < s.size(); i++)
		cout<<*(p+i)+1<<" "; 
	cout<<endl;
 } 
