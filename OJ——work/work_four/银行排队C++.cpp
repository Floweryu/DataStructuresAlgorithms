#include <iostream>
#include <string.h>
#include <iomanip>
using namespace std;

int main()
{
    int m, total;
    int cur, x, y, i, j, k, n;
    int a[100];
    double sum;
    while (cin>>m>>total)
    {
        sum = 0;
        cur = 0;
        memset(a, 0, sizeof(a));
        for (i = 0; i < total; i++)
        {
            cin>>x>>y;
            int min = 1000000;

            for (j = 0; j < m; j++)
            {
                if (a[j] < a[cur])
                {
                    min = a[j];
                    cur = j;
                }
            }

            if (x <= a[cur])
            {
                sum += (a[cur] - x);
                a[cur] += y;
            }
            else
            {
                a[cur] = x + y;
            }
        }

        cout<<setiosflags(ios::fixed)<<setprecision(2)<<sum/(1.0*total)<<endl;
    }
}
