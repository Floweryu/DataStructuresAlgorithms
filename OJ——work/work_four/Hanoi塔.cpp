#include<iostream>
#include<iomanip>

int c = 0;

using namespace std;

void move(char x, int n, char z)
{
	cout<<setw(2)<<++c<<". "<<"Move disk "<<n<<" from "<<x<<" to "<<z<<endl;
}

void hanoi(int n, char x, char y, char z)
{
	if(n == 1)
		move(x, 1, z);
	else
	{
		hanoi(n - 1, x, z, y);
		move(x, n, z);
		hanoi(n -1, y, x, z);
	}
}
 
int main()
{
	int n;
	while(scanf("%d", &n) != EOF)
	{
		hanoi(n, 'X', 'Y', 'Z');
		c = 0;
		cout<<endl;
	}
}
