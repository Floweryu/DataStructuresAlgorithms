/**
* Author : ZhangJunFeng
* Date : 2018-12-23-20.07.19
* Function: 基数排序
* Algorithm description :           1，输入每个数的各位(个，十，百)上的数字，按照个位、十位、百位把每个数分配，再按顺序收集。
                                    2，输入和输出的只是关键字，并没有把他们组成数再分离
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define MAX_NUM_OF_KEY 8            //关键字项数 的最大值
#define RADIX          10           //关键字基数
#define MAX_SPACE      100

#define NUM_MODLE 10

typedef int ElemType;

//每个数关键字的存储结构
typedef struct
{
    ElemType keys[MAX_NUM_OF_KEY];      //存储关键字
    int next;                           //链接关键字为一个数
}SLCell;

//每个数的存储结构
typedef struct
{
    SLCell r[MAX_SPACE];        //静态链表，r[0]为头结点，存储数
    int keynum;                 //当前关键字的个数
    int recnum;                 //静态链表当前长度
}SLList;

typedef int ArrType[RADIX];     //辅助数组，只有10个空间

void CreateSLList(SLList &L)
{
    cout<<"输入数据个数：     ";
    cin>>L.recnum;
    cout<<"输入关键字个数(位数):     ";
    cin>>L.keynum;

    int i, j;
    srand(time(0));
    for (i = 1; i <= L.recnum; i++)                 //从 r[1] 开始计数，数的个数
    {
        for (j = L.keynum-1; j >= 0; j--)           //输入每个数位上的关键字
        {
            L.r[i].keys[j] = rand() % NUM_MODLE;
        }
    }
    //静态链表初始化
    for (i = 0; i < L.recnum; i++)                  //链接下一个节点
        L.r[i].next = i + 1;
    L.r[L.recnum].next = 0;
}

void PrintfSLList(SLList L)
{
    int i, j;
    for (i = L.r[0].next; i; i = L.r[i].next)       //链表遍历
    {
        for (j = L.keynum-1; j >= 0; j--)           //输出每个数的关键字
            cout<<L.r[i].keys[j];
        cout<<" ";
    }
    cout<<endl;
}

//分配算法————按关键字将keys[]建立子表
void Distribute(SLCell (&r)[MAX_SPACE], int i, ArrType &f, ArrType &e)
{
    int j, p;
    for (j = 0; j < RADIX; j++)             //初始化辅助数组
    {
        f[j] = 0;
        e[j] = 0;
    }

    for (p = r[0].next; p; p = r[p].next)
    {
        j = r[p].keys[i];
        if (!f[j])
            f[j] = p;
        else
            r[e[j]].next = p;

        e[j] = p;
    }
}

//收集算法————按keys[i]从小到大将f[]子表连接成链表
void Collect(SLCell (&r)[MAX_SPACE], int i, ArrType f, ArrType e)
{
    int j, t;
    for (j = 0; !f[j]; j++);

    r[0].next = f[j];
    t = e[j];

    while (j < RADIX - 1)
    {
        for (j++; j < RADIX - 1 && !f[j]; j++);     //fuck

        if (f[j])
        {
            r[t].next = f[j];
            t = e[j];
        }

    }
    r[t].next = 0;
}

//对静态链表作基数排序
void RadixSort(SLList &L)
{
    int i;
    ArrType f, e;

    for (i = 0; i < L.keynum; i++)
    {
        Distribute(L.r, i, f, e);
        Collect(L.r, i, f, e);
        cout<<"第 "<<i+1<<"趟收集后："<<endl;
        PrintfSLList(L);
        cout<<endl;
    }

}



int main()
{
    SLList L;

    CreateSLList(L);
    cout<<"排序前："<<endl;
    PrintfSLList(L);
    cout<<endl;
    RadixSort(L);
    cout<<"排序后："<<endl;
    PrintfSLList(L);

    return 0;
}






