#include<iostream>
#include<string>

using namespace std;


int Index_KMP(string S, string T)
{
	int i = 0, j = 0;								// pos 值我认为应该确定，不知道为什么要函数传递 
	
	while(i < (int)S.size() && j < (int)T.size())	//当 i 和 j 都不超过他们对应的字符长度时 
	{	
		if(S[i] == T[j])
		{
			cout<<S[i];
			i++;
			j++;
		}	
		else 
		{	
			cout<<S[i];									//否则 
			i = i - j + 1;
			j = 0;
		}							//模式串向右移动 
	}
	cout<<endl;
	if(j >= T.size())								//当 j 大于模式串长度时，说明把模式串经历了一遍 
		return i - T.size() + 1;					/*此时 i 指到模式串最后一个字符在主串中的位置，要减去模式串长度。
													  由于从 0 开始存数，所以加上一方便查看  */ 
	else		
		return 0;
	 
}

int main()
{
	string s1, s2;
	int t = 3, i;
	while(t--)
	{
		cin>>s1;
		cin>>s2;
		
		i = Index_KMP(s1, s2);
		if(i)
			cout<<i<<endl;
		else
			cout<<"0"<<endl;
		
	}
 } 
