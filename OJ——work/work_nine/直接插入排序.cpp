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
    Direct_InsertSort(L);
    PrintfList(L);

}
