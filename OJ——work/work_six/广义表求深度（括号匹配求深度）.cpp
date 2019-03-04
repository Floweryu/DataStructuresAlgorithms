#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    int count = 0, max = 0, len;
    char str[100];
    int i;
    cin>>str;
    len = strlen(str);

    for (i = 0; i < len; i++)
    {
        if (str[i] == '(')
        {
            count++;
            if (count > max)
            {
                max = count;
            }
        }
        if (str[i] == ')')
        {
            count--;
        }
    }
    cout<<max<<endl;
}
