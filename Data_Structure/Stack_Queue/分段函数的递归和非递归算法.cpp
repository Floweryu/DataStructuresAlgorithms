#include<iostream>
#include<ctime>
using namespace std;

long long indef(long long n)
{
	long long first = 1;
	long long second = 1;
	long long res = 0;
	for(long long i = 3; i <= n; i++)
	{
		res = first + second;
		first = second;
		second = res;
	}
	return res;
} 

long long def(long long n)
{
	if(n<3)
		return 1;
	else
		return def(n-1)+def(n-2);
} 

int main()
{
	printf("***********************************\n");
	printf("****·ÇµÝ¹é£¬please enter 'a'  *****\n");
	printf("****µÝ¹é£¬  please enter 'b'  *****\n");
	printf("****ÍË³ö£¬  please enter 'q'  *****\n");
	
	int year;
	char str;
	clock_t start, finish;
	double dur;
	do
	{
		cout<<"Please enter a char:      ";
		cin>>str;
		switch(str)
		{
			case 'a'://·ÇµÝ¹é
			{	
				cin>>year;
				
				start = clock();
				cout<<indef(year)<<endl;
				finish = clock();
				
				dur = (double)(finish - start)/CLOCKS_PER_SEC;
				
				cout<<"The running time is:   ";
				cout<<dur<<endl; 
				
				break;
			} 
			case 'b'://µÝ¹é
			{
				cin>>year;
				
				start = clock();
				cout<<def(year)<<endl;
				finish = clock();
				
				dur = (double)(finish - start)/CLOCKS_PER_SEC;
				
				cout<<"The running time is:   ";
				cout<<dur<<endl; 
				
				break;
			} 
			default:	cout<<"wrong!!!"<<endl;
		}
	}while(str != 'q');
	return 0;
}
