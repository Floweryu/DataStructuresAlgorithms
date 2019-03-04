/**
* Author : ZhangJunFeng
* Date : 2018-12-21-18.02.10
* Function: 交换排序算法————冒泡排序，快速排序
* Algorithm description :       1，程序输入数据用了随机数组，只需要输入数组中数据的个数即可。
                                2，数组下标为 0 的地址用来临时存储当前待插入值
                                3，快速排序：每次以low处值为基准，把小的排在其左边，大的排在其右边。如此递归，直至递归区间长度为 1。

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

//冒泡排序
void Bubble_Sort(SqList &L)
{
    int i, j;

    for (i = 1; i <= L.length-1; i++)       //排序次数为 L.length-1
    {
        for (j = 1; j <= L.length-i; j++)   //每排序一次，确定一个元素位置
        {
            if (L.list[j] > L.list[j+1])
                swap(L.list[j], L.list[j+1]);
        }
    }
}

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


int main()
{
    cout<<"*************************************************"<<endl;
    cout<<"*****Bubble_Sort              enter   'd'  ******"<<endl;
    cout<<"*****Quick_Sort               enter   'e'  ******"<<endl;
    cout<<"*************************************************"<<endl;
    SqList Li;
    int lilong;
    char str;

    cout<<"输入数组长:    ";
    cin>>lilong;
    Li.length = lilong;

    CreateList(Li);
    cout<<"输入的数组为:"<<endl;
    PrintfList(Li);


    do
    {
        cout<<endl;
        cout<<"Please enter a char :        ";
        cin>>str;
        switch(str)
        {
            case 'd':
                {
                    Bubble_Sort(Li);
                    cout<<"排序后的数组为:"<<endl;
                    PrintfList(Li);
                    break;
                }
            case 'e':
                {
                    Quick_Sort(Li, 1, lilong);
                    cout<<"排序后的数组为:"<<endl;
                    PrintfList(Li);
                    break;
                }
            default: cout<<"Wrong!!!"<<endl;
        }
    } while (str != 'q');

    return 0;
}








