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

    cout<<"�������ݸ���:    ";
    cin>>n;
    cout<<"��������ֵ:"<<endl;
    for (int i = 1; i <= n; i++)
    {
        cin>>store[i];
    }

    cout<<"����Ҫ���ҵ�ֵ��     ";
    cin>>keys;

    back = Search(store, n, keys);
    if(back)
    {
        cout<<"��ֵ�ڵ� "<<back<<" ��λ��"<<endl;
    }
    else
        cout<<"û��Ҫ�ҵ�ֵ!!"<<endl;
}
