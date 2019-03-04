/**
* Author : ZhangJunFeng
* Date : 2018-12-16-12.21.19
* Function: ����������
* Description :  ��̬�����е���������õ�
* Algorithm description :   �еݹ���ǵݹ�
* The test data :
*/
#include <iostream>
#include <time.h>
using namespace std;

typedef int KeyType;
#define MAX_NUM 1000

KeyType store[MAX_NUM];
int n;
clock_t start, finish;
double duration;

int binary_search(KeyType key)
{
    int low = 0, high = n;
    start = clock();
    while (high - low >= 1)
    {
        int i = (high + low) / 2;
        if (store[i] == key)
            return i;
        else if (store[i] < key)
        {
            low = i + 1;
        }
        else
        {
            high = i - 1;
        }
    }
    finish = clock();
    return -1;
}

int DFS(int low, int high, KeyType key)
{
    if ((high - low) < 1)
        return -1;
    int i = (high + low) / 2;
    if (store[i] == key)
        return i;
    else if (store[i] < key)
        return DFS(i + 1, high, key);
    else
        return DFS(low, i - 1, key);
}


int main()
{
    KeyType keys;
    int back;
    cout<<"���������    ";
    cin>>n;
    cout<<"��������ֵ��"<<endl;
    for (int i = 0; i < n; i++)
    {
        cin>>store[i];
    }

    cout<<"�������ֵ��   ";
    cin>>keys;
    back = DFS(0, n, keys);
    if (back != -1)
        cout<<"����Ԫ���ڵ� "<<back+1<<" ��λ��"<<endl;
    else
        cout<<"û�д�Ԫ��!!!"<<endl;

 //   duration = (double)(start-finish) / CLOCKS_PER_SEC;
 //   cout<<"����ʱ��:   "<<duration<<endl;
}
