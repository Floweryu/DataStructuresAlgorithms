#include<iostream>
#include<string>
using namespace std;

void Concat(string s, string t)
{
	string ss;
	ss = s + t;
	if(ss.size() > 100)
		cout<<"Result String is cutted."<<endl;	//����ܶ��ģ���Ҫ���ǵ㡰.�� 
	else
		cout<<ss<<endl;
}

int main()
{
	string S, T;
	while(cin>>S>>T)
	Concat(S, T);
}
