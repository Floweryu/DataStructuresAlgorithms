#include <iostream>
using namespace std;

#define MAX_NUM 100
typedef int KeyType;

int Search(KeyType *store, int N, KeyType key)
{
    int i;
    for (i = 1; i <= N; i++)
    {
        if (store[i] == key)
        {
            return i;
            break;
        }
    }
    return 0;
}


int main()
{
    KeyType store[MAX_NUM], keys;
    int n, back;

    cout<<"输入数据个数:    ";
    cin>>n;
    cout<<"输入数据值:"<<endl;
    for (int i = 1; i <= n; i++)
    {
        cin>>store[i];
    }

    cout<<"输入要查找的值：     ";
    cin>>keys;

    back = Search(store, n, keys);
    if(back)
    {
        cout<<"此值在第 "<<back<<" 个位置"<<endl;
    }
    else
        cout<<"没有要找的值!!"<<endl;
}
