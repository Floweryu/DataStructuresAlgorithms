//循环实现斐波那契数列
#include<iostream>
#include<ctime>
using namespace std;
int main()
{ 	
	long long n;
	clock_t t1, t2;
	int t;
	cin>>n;
	long long first = 1;
	long long second = 1;
	long long res = 0;
	
	t1 = clock();
	
	for(long long i = 3; i <= n; i++)
	{
		res = first + second;
		first = second;
		second = res;
	}
	
	t2 = clock();
	
	t = t2- t1;
	cout<<t<<endl;
	cout<<res<<endl;
} 

