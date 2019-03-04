/**
* Author : ZhangJunFeng
* Date : 2018-12-21-19.56.24
* Function: 选择排序算法————简单选择排序，堆排序。
* Algorithm description :   1，程序输入数据用了随机数组，只需要输入数组中数据的个数即可。
                            2，数组下标为 0 的地址用来临时存储当前待插入值
                            3，选择排序: 每次排序都选择一个最值放在前面(即确定一个值位置 或 前面位置的元素)，每次选择都从待排序序列中选择最值。
                            4，堆排序：每次把堆顶元素放到后面，其余元素重建顶堆。循环L.length - 1 次。第一次已建好顶堆。
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

//直接选择排序
void Select_Sort(SqList &L)
{
    int i, j;
    for (i = 1; i <= L.length-1; i++)
    {
        int min = i;                            //最小值得位置编号
        for (j = i+1; j <= L.length; j++)
        {
            if (L.list[j] < L.list[min])
                min = j;
        }                                       //每次遍历完都找到未排序序列中最小值的下标
        swap(L.list[i], L.list[min]);
   //     cout<<"第 "<< i <<" 趟后序列为:      ";
   //     PrintfList(L);
    }
}

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


int main()
{
    cout<<"*************************************************"<<endl;
    cout<<"*****Select_Sort              enter   'f'  ******"<<endl;
    cout<<"*****Heap_Sort                enter   'g'  ******"<<endl;
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
            case 'f':
                {
                    Select_Sort(Li);
                    cout<<"排序后的数组为:"<<endl;
                    PrintfList(Li);
                    break;
                }
            case 'g':
                {
                    Heap_Sort(Li);
                    cout<<"排序后的数组为:"<<endl;
                    PrintfList(Li);
                    break;
                }
            default: cout<<"Wrong!!!"<<endl;
        }
    } while (str != 'q');

    return 0;
}
