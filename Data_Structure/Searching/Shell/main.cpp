/**
* Author : ZhangJunFeng
* Date : 2018-12-18-20.59.01
* Function: ��������������㷨
* Algorithm description :   1������������������������飬ֻ��Ҫ�������������ݵĸ������ɡ�
                            2�������±�Ϊ 0 �ĵ�ַ������ʱ�洢��ǰ������ֵ
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

//ֱ�Ӳ������򡪡�������С����
void Direct_InsertSort(SqList &L)
{
    int i, j;
    for (i = 2; i <= L.length; i++)                      //�ӵڶ���λ�ÿ�ʼѰ��
    {
        if (L.list[i] < L.list[i-1])
        {
            L.list[0] = L.list[i];                       //����ֵ�洢
            L.list[i] = L.list[i-1];                     //��ǰһ��ֵ����ƶ�һλ
            for (j = i - 2; L.list[j] > L.list[0]; --j)  //�Ӵ�����ֵ��ǰ����ֵ�𣬰ѱ� L.list[i] ���ֵ����ƶ�һλ
            {
                L.list[j+1] = L.list[j];
            }  //����ѭ��ʱ j �Ѿ�ָ��С�ڻ����L.list[0]��λ��
            L.list[j+1] = L.list[0];
        }
    }
}

//�۰��������
void Binary_InsertSort(SqList &L)
{
    int low, high, half;
    int i, j;
    for (i = 2; i <= L.length; i++)
    {
        L.list[0] = L.list[i];
        low = 1; high = i-1;
        while(high >= low)
        {
            half = (high + low) / 2;
            if (L.list[0] < L.list[half])
                high = half - 1;
            else
                low = half + 1;
        }   //����ѭ��ʱ high �Ѿ�ָ��С�ڻ����L.list[0]��λ��
        for (j = i - 1; j > high; j--)
            L.list[j+1] = L.list[j];
        L.list[high+1] = L.list[0];
    }
}

void Shell_Array(SqList &L, int dlta[], int &k)
{
    while(L.length >=2)
    {
        dlta[k] = L.length / 2;
        k++;
        L.length /= 2;
    }
}

//ϣ������
void Shell_Insert(SqList &L, int dk)
{
    int i;

    for (i = dk + 1; i <= L.length; i++)
    {
        if (L.list[i] < L.list[i-dk])
            swap(L.list[i], L.list[i-dk]);
    }
}

//ϣ������
void Shell_InsertSort(SqList &L, int dlta[], int t)
{
    int k;
    for (k = 0; k < t; k++)
        Shell_Insert(L, dlta[k]);
}


//�����������
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
    SqList Li;
    int lilong;
    cout<<"�������鳤:    ";
    cin>>lilong;
    Li.length = lilong;

    CreateList(Li);
    cout<<"���������Ϊ:"<<endl;
    PrintfList(Li);
    //Direct_InsertSort(Li);
    //Binary_InsertSort(Li);
    int increase[lilong], leng;

    Shell_Array(Li, increase, leng);
    for (int m =0; m < leng; m++)
        cout<<increase[m]<<" ";

    Shell_InsertSort(Li, increase, leng);

    cout<<"����������Ϊ:"<<endl;
    PrintfList(Li);

}







