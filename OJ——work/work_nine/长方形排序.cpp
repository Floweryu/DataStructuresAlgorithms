#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_NUM 10001

struct SqList
{
    int number;
    int length;
    int wide;
};

bool cmp(SqList a, SqList b)            //把小的放前面排序
{
    if (a.number != b.number)
        return a.number < b.number;
    else if(a.length != b.length)
        return a.length < b.length;
    else if(a.wide != b.wide)
        return a.wide < b.wide;
}


int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        struct SqList rect[n];
        int i;
        for (i = 0; i < n; i++)
        {
            cin>>rect[i].number>>rect[i].length>>rect[i].wide;
            if (rect[i].length < rect[i].wide)
                swap(rect[i].length, rect[i].wide);

        }

        sort(rect, rect+n, cmp);
        for (i = 0; i < n; i++)
        {
            if (!(rect[i].number == rect[i+1].number && rect[i].length == rect[i+1].length && rect[i].wide == rect[i+1].wide))  //遇到重复的不用输出直接跳过
                cout<<rect[i].number<<" "<<rect[i].length<<" "<<rect[i].wide<<endl;
        }
    }
}












