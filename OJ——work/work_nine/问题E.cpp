#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

#define MAX 100000

string str;

struct tele
{
    char number[20];
};


char trans(char s)
{
    if (s >= 'A' && s <= 'C')
        return '2';
    else if (s >= 'D' && s <= 'F')
        return '3';
    else if (s >= 'G' && s <= 'I')
        return '4';
    else if (s >= 'J' && s <= 'L')
        return '5';
    else if (s >= 'M' && s <= 'O')
        return '6';
    else if (s >= 'P' && s <= 'S')
        return '7';
    else if (s >= 'T' && s <= 'V')
        return '8';
    else if (s >= 'W' && s <= 'Y')
        return '9';
}

int cmp(const void *s, const void *t)
{
    return strcmp( (*(tele*)s).number, (*(tele*)t).number);
}

int main()
{
    int n;
    cin>>n;
    int i, j;
    struct tele phone[100000];

    for (i = 0; i < n; i++)
    {
        int pos = 0;
        cin>>str;
        for (j = 0; j < str.size(); j++)
        {
            if (str[j] == '-')
                continue;
            if (str[j] >= '0' && str[j] <= '9')
                phone[i].number[pos++] = str[j];
            else if (str[j] >= 'A' && str[j] <= 'Z')
                phone[i].number[pos++] = trans(str[j]);
            if (pos == 3)
                phone[i].number[pos++] = '-';
        }
        phone[i].number[pos] = '\0';                    //fuck you fuck fuck fuck fuck fuck fuck fuck
    }

    qsort(phone, n, sizeof(phone[0]), cmp);
    int count, flag = 1;
    for (i = 0; i < n; i++)
    {
        count = 1;
        while (!strcmp(phone[i].number, phone[i+1].number))
        {
            count++;
            i++;
        }
        if (count > 1)
        {
            cout<<phone[i].number<<" "<<count<<endl;
            flag = 0;
        }
    }
    if (flag)
        cout<<"No duplicates."<<endl;

    return 0;
}








