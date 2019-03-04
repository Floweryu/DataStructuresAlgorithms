#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define MAX_NUM 1001
#define NUM_MODLE 100

typedef int ElemType;

struct SqList
{
    ElemType list[MAX_NUM];
    int length;
};

//直接插入排序————从小到大
void Direct_InsertSort(SqList &L)
{
    int i, j;
    for (i = 2; i <= L.length; i++)                      //从第二个位置开始寻找
    {
        if (L.list[i] < L.list[i-1])
        {
            L.list[0] = L.list[i];                       //将该值存储
            L.list[i] = L.list[i-1];                     //把前一个值向后移动一位
            for (j = i - 2; L.list[j] > L.list[0]; --j)  //从待插入值的前两个值起，把比 L.list[i] 大的值向后移动一位
            {
                L.list[j+1] = L.list[j];
            }  //跳出循环时 j 已经指到小于或等于L.list[0]的位置
            L.list[j+1] = L.list[0];
        }
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
    Direct_InsertSort(L);
    PrintfList(L);

}
