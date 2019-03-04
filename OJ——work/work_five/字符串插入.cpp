#include<iostream>
#include<string>
using namespace std;

void Insert(char S[], int pos, string T)
{
	int i;
	string ss;

	ss = &S[pos-1];
	S[pos-1] = '\0';
	cout<<S<<T<<ss<<endl;
} 

int main()
{
	string t;
	char s[150];
	int p;
	while(cin>>s>>t>>p)
	Insert(s, p, t);
	
}
