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

//�ѵ���
void AdjustHeap(SqList &L, int s, int m)        //ÿ���жϸýڵ��������������ֵ�����ڵ㽻��λ��
{
    int j;
    int rc = L.list[s];
    for (j = 2*s; j <= m; j *= 2)
    {
        if (j < m && L.list[j] < L.list[j+1])   //Ѱ������ӽڵ�
            j++;
        if (rc >= L.list[j])
            break;
        L.list[s] = L.list[j];
        s = j;
    }
    L.list[s] = rc;
}

//��С�������򡪡������󶥶�
void Heap_Sort(SqList &L)
{
    int i;
    for (i = L.length/2; i >= 1; i--)       //��������Ϊ�󶥶�
        AdjustHeap(L, i, L.length);
    for (i = L.length; i >= 2; i--)         //��ȥ���һ��Ԫ�أ������ļ�������Ϊ�󶥶�
    {
        swap(L.list[1], L.list[i]);         //�����ֵ�����һ��Ԫ�ؽ���λ��
        AdjustHeap(L, 1, i-1);
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
    Heap_Sort(L);;
    PrintfList(L);

}
