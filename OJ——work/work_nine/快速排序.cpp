#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define MAX_NUM 100002
#define NUM_MODLE 100

typedef int ElemType;

struct SqList
{
    ElemType list[MAX_NUM];
    int length;
};

//对每次排序，求得枢轴的位置
int partition(SqList &L, int low, int high)
{
    int pivotkey;

    pivotkey = L.list[low];
    while (low < high)
    {
        while (low < high && L.list[high] >= pivotkey)     //从后寻找比枢轴小的值，交换位置
            high--;
        swap(L.list[low], L.list[high]);

        while (low < high && L.list[low] <= pivotkey)      //从前寻找比枢轴大的值，交换位置
            low++;
        swap(L.list[low], L.list[high]);
    }
    return low;
}

//快速排序
void Quick_Sort(SqList &L, int low, int high)
{
    int pivotloc;

    if (low < high)
    {
        pivotloc = partition(L, low, high);
        Quick_Sort(L, low, pivotloc - 1);                  //对枢轴前面数据进行排序
        Quick_Sort(L, pivotloc+1, high);                   //对枢轴后面数据进行排序
    }
}


//随机产生数组
void CreateList(SqList &L)
{
    int i;
    for (i = 1; i <= L.length; i++)
    {
        cin>>L.list[i];
    }
}

void PrintfList(SqList &L)
{
    int i;
    for (i = 1; i <= L.length; i++)
        cout<<L.list[i]<<" ";
    cout<<endl;
}

int main()
{
    SqList L;
    cin>>L.length;
    CreateList(L);
    Quick_Sort(L, 1, L.length);
    PrintfList(L);

}
