/**
* Author : ZhangJunFeng
* Date : 2018-12-23-20.07.19
* Function: ��������
* Algorithm description :
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define MAX_NUM_OF_KEY 8            //�ؼ������� �����ֵ
#define RADIX          10           //�ؼ��ֻ���
#define MAX_SPACE      100

#define NUM_MODLE 10

typedef int ElemType;

typedef struct
{
    ElemType keys[MAX_NUM_OF_KEY];
    int next;
}SLCell;

typedef struct
{
    SLCell r[MAX_SPACE];        //��̬����r[0]Ϊͷ���
    int keynum;                 //��ǰ�ؼ��ֵĸ���
    int recnum;                 //��̬����ǰ����
}SLList;

typedef int ArrType[RADIX];

void CreateSLList(SLList &L)
{
    cout<<"�������ݸ�����     ";
    cin>>L.recnum;
    cout<<"����ؼ��ָ���(λ��):     ";
    cin>>L.keynum;

    int i, j;
    srand(time(0));
    for (i = 1; i <= L.recnum; i++)
    {
        for (j = L.keynum-1; j >= 0; j--)
        {
            L.r[i].keys[j] = rand() % NUM_MODLE;
        }
    }
    for (i = 0; i < L.recnum; i++)
        L.r[i].next = i + 1;
    L.r[L.recnum].next = 0;
}

void PrintfSLList(SLList L)
{
    int i, j;
    for (i = L.r[0].next; i; i = L.r[i].next)
    {
        for (j = L.keynum-1; j >= 0; j--)
            cout<<L.r[i].keys[j];
        cout<<" ";
    }
    cout<<endl;
}

//�����㷨�����������ؼ��ֽ�keys[]�����ӱ�
void Distribute(SLCell (&r)[MAX_SPACE], int i, ArrType &f, ArrType &e)
{
    int j, p;
    for (j = 0; j < RADIX; j++)
        f[j] = 0;

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

//�ռ��㷨����������keys[i]��С����f[]�ӱ����ӳ�����
void Collect(SLCell (&r)[MAX_SPACE], int i, ArrType f, ArrType e)
{
    int j, t;
    for (j = 0; !f[j]; j++);

    r[0].next = f[j];
    t = e[j];

    while (j < RADIX - 1)           //????
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

//�Ծ�̬��������������
void RadixSort(SLList &L)
{
    int i;
    ArrType f, e;

    for (i = 0; i < L.keynum; i++)
    {
        Distribute(L.r, i, f, e);
        Collect(L.r, i, f, e);
        cout<<"�� "<<i+1<<"���ռ���"<<endl;
        PrintfSLList(L);
        cout<<endl;
    }

}



int main()
{
    SLList L;

    CreateSLList(L);
    cout<<"����ǰ��"<<endl;
    PrintfSLList(L);
    RadixSort(L);
    cout<<"�����"<<endl;
    PrintfSLList(L);

    return 0;
}






