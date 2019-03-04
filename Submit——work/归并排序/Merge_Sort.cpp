/**
* Author : ZhangJunFeng
* Date : 2018-12-23-16.20.38
* Function: 归并排序算法
* Algorithm description :
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define MAX_NUM 100
#define NUM_MODLE 100

typedef int ElemType;

struct SqList
{
    ElemType list[MAX_NUM];
    int length;
};

void CreateList(SqList &L)
{
    int i;
    srand(time(0));
    for (i = 1; i <= L.length; i++)
    {
        L.list[i] = rand() % NUM_MODLE;
    }
}


void PrintfList(SqList &L)
{
    int i;
    for (i = 1; i <= L.length; i++)
        cout<<L.list[i]<<" ";
    cout<<endl;
}

void Merge(SqList SR, SqList &TR, int i, int m, int n)
{
    int j, k;
    for (j = m+1, k = i; i <= m && j <=n; ++k)
    {
        if (SR.list[i] < SR.list[j])
            TR.list[k] = SR.list[i++];
        else
            TR.list[k] = SR.list[j++];
    }

    while (i <= m)
        TR.list[k++] = SR.list[i++];
    while (j <= n)
        TR.list[k++] = SR.list[j++];
}

void MSort(SqList SR, SqList &TR1, int s, int t)
{
    int m;
    SqList R;

    if (s == t)                         //上、下界相等时赋值
        TR1.list[s] = SR.list[s];       //这里TR1实际为R, SR就是L
    else
    {
        m = (s+t) / 2;
        MSort(SR, R, s, m);
        MSort(SR, R, m+1, t);
       // cout<<"s   m   t"<<endl;
        //cout<<s<<"~~~"<<m<<"!!!"<<t<<endl;
        Merge(R, TR1, s, m, t);         //在所有递归结束之后，TR1 为L
    }
}

void Merge_Sort(SqList &L)
{
    MSort(L, L, 1, L.length);
}

int main()
{
    SqList Li;
    int lilong;
    char str;

    cout<<"输入数组长:    ";
    cin>>lilong;
    Li.length = lilong;

    CreateList(Li);
    cout<<"输入的数组为:"<<endl;
    PrintfList(Li);

    Merge_Sort(Li);
    cout<<"排序后的数组为:"<<endl;
    PrintfList(Li);
}






