#include <iostream>
using namespace std;

int main()
{
    int a[501];
    int ka[501];
    int key, count = 0;
    int n, k, flag;
    cin>>n>>k;

    int i, j;
    for (i = 0; i < n; i++)
        cin>>a[i];
    for (i = 0; i < k; i++)
        cin>>ka[i];

    for (j = 0; j < k; j++)
    {
        for (i = 0; i < n; i++)
        {
            if (a[i] == ka[j])
            {
                flag = 1;
                break;
            }
            else
            {
                flag = 0;
            }
        }
        cout<<flag<<" ";
    }
}
