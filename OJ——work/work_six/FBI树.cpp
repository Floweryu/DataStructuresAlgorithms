#include <iostream>
#include <cmath>
using namespace std;

char str[1024];

void FBI(int low, int up)
{
    int mid = (up+low) / 2;

    if (low != up)
    {
        FBI(low, mid);
        FBI(mid + 1, up);
    }

    int i, a = 0, b = 0;

    for (i = low; i <= up; i++)
    {
        if (str[i] == '1')
            a = 1;
        else
            b = 1;
    }

    if (a && b)
        cout<<"F";
    else if(a && !b)
        cout<<"I";
    else if(b && !a)
        cout<<"B";
}

int main()
{
    int n, len;
    cin>>n;
    len = pow(2, n);
    cin>>str+1;
    FBI(1, len);
}
