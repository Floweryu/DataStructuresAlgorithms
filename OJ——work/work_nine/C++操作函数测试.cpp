#include <iostream>
#include <string>
using namespace std;

#define MAX 100000

struct tele
{
    string str;
    int length;
};

int main()
{
    int n;
    cin>>n;
    int i, j;
    struct tele phone[MAX];
    int a[n];
    for (i = 0; i < n; i++)
    {
        cin>>phone[i].str;
        phone[i].length = phone[i].str.size();
        a[i] = phone[i].length;
    }

    for (i = 0; i < n; i++)
    {
        cout<<phone[i].length<<endl;
    }
    
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < a[i]; j++)
        {
            if (phone[i].str[j] >= '0' && phone[i].str[j] <= '9')
            {
                continue;
            }
            else
            {
                phone[i].str.erase(j);
                phone[i].length--;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
    	for (j = 0; j < phone[i].length; j++)
        	cout<<phone[i].str[j];
        cout<<endl;
    }
}
