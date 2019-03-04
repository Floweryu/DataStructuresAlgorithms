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


//�����������
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
