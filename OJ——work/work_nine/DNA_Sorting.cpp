#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

struct DNA
{
    char str[51];
    int num;
};


bool cmp(DNA a, DNA b)
{
    return a.num < b.num;
}

int main()
{
    int n, m;
    cin>>n>>m;
    struct DNA AGCT[101];
    int i, j, k;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            cin>>AGCT[i].str[j];
        }
    }

    for (i = 0; i < m; i++)
        AGCT[i].num = 0;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n-1; j++)
        {
            for (k = j+1; k < n; k++)
            {
                if (AGCT[i].str[j] > AGCT[i].str[k])
                    AGCT[i].num++;
            }
        }
    }

    sort(AGCT, AGCT+m, cmp);

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            cout<<AGCT[i].str[j];
        }
        cout<<endl;
    }
}










