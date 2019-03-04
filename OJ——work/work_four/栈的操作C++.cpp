#include<iostream>
#include<string.h> 
using namespace std;

int main()
{
	int a[1000], num[1000];
	int top, count, i;
	int n;
	
	while(cin>>n)
	{
		top = -1;
		count = 1;
		a[0] = 0;
		
		for(i = 0; i < n; i++)
			cin>>num[i];
			
		for(i = 0; i < n; i++)
		{
			top++;
			while(a[top-1] < num[i])
			{
				a[top] = count;
				count++;
				top++;
				cout<<"P";
			}
			
			top--;
			
			if(a[top] == num[i])
			{
				cout<<"Q";
				top--;
			}
			
			else if(a[top] > num[i])
			{
				cout<<" error";
				break;
			}
		}
		memset(a, 0, sizeof(a));
		memset(num, 0, n);
		cout<<endl;
	}
}
