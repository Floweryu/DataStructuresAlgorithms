#include <iostream>
using namespace std;


void store(int un[], int a, int n)
{
    int i, flag = 0;
    for (i = 1; i <= n; i++)
    {
        if (un[i] == a)
            flag = 1;
    }
    if (flag == 0)
        un[a] = a;
}



int main()
{
    int n, k, x, y, p1, p2;
    int i;
    cin>>n>>k;
    int un[n] = {0};
    for (i = 0; i < k; i++)
    {
        cin>>x>>y;
        store(un, x, n);
        store(un, y, n);
    }

    cin>>p1>>p2;
    if (store[p1] && store[p2])
        cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;
}
