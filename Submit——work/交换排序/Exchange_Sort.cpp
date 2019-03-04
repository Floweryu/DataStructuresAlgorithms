/**
* Author : ZhangJunFeng
* Date : 2018-12-21-18.02.10
* Function: ���������㷨��������ð�����򣬿�������
* Algorithm description :       1������������������������飬ֻ��Ҫ�������������ݵĸ������ɡ�
                                2�������±�Ϊ 0 �ĵ�ַ������ʱ�洢��ǰ������ֵ
                                3����������ÿ����low��ֵΪ��׼����С����������ߣ�����������ұߡ���˵ݹ飬ֱ���ݹ����䳤��Ϊ 1��

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

//ð������
void Bubble_Sort(SqList &L)
{
    int i, j;

    for (i = 1; i <= L.length-1; i++)       //�������Ϊ L.length-1
    {
        for (j = 1; j <= L.length-i; j++)   //ÿ����һ�Σ�ȷ��һ��Ԫ��λ��
        {
            if (L.list[j] > L.list[j+1])
                swap(L.list[j], L.list[j+1]);
        }
    }
}

//��ÿ��������������λ��
int partition(SqList &L, int low, int high)
{
    int pivotkey;

    pivotkey = L.list[low];
    while (low < high)
    {
        while (low < high && L.list[high] >= pivotkey)     //�Ӻ�Ѱ�ұ�����С��ֵ������λ��
            high--;
        swap(L.list[low], L.list[high]);

        while (low < high && L.list[low] <= pivotkey)      //��ǰѰ�ұ�������ֵ������λ��
            low++;
        swap(L.list[low], L.list[high]);
    }
    return low;
}

//��������
void Quick_Sort(SqList &L, int low, int high)
{
    int pivotloc;

    if (low < high)
    {
        pivotloc = partition(L, low, high);
        Quick_Sort(L, low, pivotloc - 1);                  //������ǰ�����ݽ�������
        Quick_Sort(L, pivotloc+1, high);                   //������������ݽ�������
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

    cout<<"�������鳤:    ";
    cin>>lilong;
    Li.length = lilong;

    CreateList(Li);
    cout<<"���������Ϊ:"<<endl;
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
                    cout<<"����������Ϊ:"<<endl;
                    PrintfList(Li);
                    break;
                }
            case 'e':
                {
                    Quick_Sort(Li, 1, lilong);
                    cout<<"����������Ϊ:"<<endl;
                    PrintfList(Li);
                    break;
                }
            default: cout<<"Wrong!!!"<<endl;
        }
    } while (str != 'q');

    return 0;
}








