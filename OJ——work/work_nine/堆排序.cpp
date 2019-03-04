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

//堆调整
void AdjustHeap(SqList &L, int s, int m)        //每次判断该节点的左右子树，将值大的与节点交换位置
{
    int j;
    int rc = L.list[s];
    for (j = 2*s; j <= m; j *= 2)
    {
        if (j < m && L.list[j] < L.list[j+1])   //寻找最大子节点
            j++;
        if (rc >= L.list[j])
            break;
        L.list[s] = L.list[j];
        s = j;
    }
    L.list[s] = rc;
}

//从小到大排序————大顶堆
void Heap_Sort(SqList &L)
{
    int i;
    for (i = L.length/2; i >= 1; i--)       //调整数组为大顶堆
        AdjustHeap(L, i, L.length);
    for (i = L.length; i >= 2; i--)         //除去最后一个元素，其他的继续调整为大顶堆
    {
        swap(L.list[1], L.list[i]);         //将最大值与最后一个元素交换位置
        AdjustHeap(L, 1, i-1);
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
    Heap_Sort(L);;
    PrintfList(L);

}
