/**
* Author : ZhangJunFeng
* Date : 2018-12-21-19.56.24
* Function: ѡ�������㷨����������ѡ�����򣬶�����
* Algorithm description :   1������������������������飬ֻ��Ҫ�������������ݵĸ������ɡ�
                            2�������±�Ϊ 0 �ĵ�ַ������ʱ�洢��ǰ������ֵ
                            3��ѡ������: ÿ������ѡ��һ����ֵ����ǰ��(��ȷ��һ��ֵλ�� �� ǰ��λ�õ�Ԫ��)��ÿ��ѡ�񶼴Ӵ�����������ѡ����ֵ��
                            4��������ÿ�ΰѶѶ�Ԫ�طŵ����棬����Ԫ���ؽ����ѡ�ѭ��L.length - 1 �Ρ���һ���ѽ��ö��ѡ�
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

//ֱ��ѡ������
void Select_Sort(SqList &L)
{
    int i, j;
    for (i = 1; i <= L.length-1; i++)
    {
        int min = i;                            //��Сֵ��λ�ñ��
        for (j = i+1; j <= L.length; j++)
        {
            if (L.list[j] < L.list[min])
                min = j;
        }                                       //ÿ�α����궼�ҵ�δ������������Сֵ���±�
        swap(L.list[i], L.list[min]);
   //     cout<<"�� "<< i <<" �˺�����Ϊ:      ";
   //     PrintfList(L);
    }
}

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


int main()
{
    cout<<"*************************************************"<<endl;
    cout<<"*****Select_Sort              enter   'f'  ******"<<endl;
    cout<<"*****Heap_Sort                enter   'g'  ******"<<endl;
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
            case 'f':
                {
                    Select_Sort(Li);
                    cout<<"����������Ϊ:"<<endl;
                    PrintfList(Li);
                    break;
                }
            case 'g':
                {
                    Heap_Sort(Li);
                    cout<<"����������Ϊ:"<<endl;
                    PrintfList(Li);
                    break;
                }
            default: cout<<"Wrong!!!"<<endl;
        }
    } while (str != 'q');

    return 0;
}
