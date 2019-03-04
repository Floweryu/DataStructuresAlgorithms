/**
* Author : ZhangJunFeng
* Date : 2018-12-18-16.46.48
* Function: ��ϣ�����㷨
* Description :
* Algorithm description :
* The test data :
*/
#include <iostream>
#include <cstdlib>
using namespace std;

#define success 1
#define unsuccess 0
#define duplicate -1
#define ok 1

#define NULL_KEY -1
#define N 50

int hashsize[] = {11, 19, 29, 37};      //��ϣ������������
int length, c;                             //��ϣ���

typedef int ElemType;

struct HashTable
{
    ElemType *elem;                     //����Ԫ�ش洢��ַ����̬��������
    int count;                          //��ǰ����Ԫ�ظ���
    int sizeindex;                      //hashsize[sizeindex] Ϊ��ǰ����
};

//����һ���յĹ�ϣ��
void InitHashTable(HashTable &H)
{
    int i;
    H.count = 0;
    H.sizeindex = 0;
    length = hashsize[0];
    H.elem = new ElemType[length];
    if (! H.elem)
        exit(EXIT_SUCCESS);
    for (i = 0; i < length; i++)
    {
        H.elem[i] = NULL_KEY;
    }
}

//��ϣ���������ϣ��ַ
int Hash(ElemType K)
{
    return (K % length);
}

//���Ŷ�ַ��--����̽����ɢ��
int collision(ElemType K)
{
    return (Hash(K) + 1) % length;
}

//�鿴��ϣ�����Ƿ����KԪ��
int SearchHash(HashTable H, ElemType K, int &p)
{
    int c = 0;
    p = Hash(K);
    while (H.elem[p] != NULL_KEY && H.elem[p] != K)     //����õ�ַ�м�¼ ���� �ü�¼��K�����
    {
        c++;
        p = collision(K);                               //��ַ����ƶ�
    }
    //����ѭ��ʱ p ��ֵΪ�� ���� �ô�ֵ����K

    if (H.elem[p] == K)
        return success;
    else
        return unsuccess;
}

void ReCreateHashTable(HashTable H);


//���ϣ���в���Ԫ��
int InsertHash(HashTable H, ElemType e)
{
    int p;
    if (SearchHash(H, e, p))
        return duplicate;
    else if (c < hashsize[H.sizeindex] / 2)         //Ϊʲô����2����������������������������
    {
        H.elem[p] = e;
        H.count++;
        return ok;
    }
    else
    {
        ReCreateHashTable(H);
        return unsuccess;
    }
}

//�ؽ���ϣ��
void ReCreateHashTable(HashTable H)
{
    int i, count = H.count;
    ElemType *p, *elem;
    p = elem = new ElemType[count];

    for (i = 0; i < length; i++)
    {
        if (H.elem[i] != NULL_KEY)
            *p++ = H.elem[i];
    }
    H.count = 0;
    H.sizeindex++;
    length = hashsize[H.sizeindex];
    H.elem = new ElemType[length];

    for (i = 0; i < length; i++)
        H.elem[i] = NULL_KEY;
    for (p = elem; p < elem + count; p++)
        InsertHash(H, *p);
    delete [] elem;
}


void TraverseHash(HashTable &H)
{
    int i;
    cout<<"��ϣ��ַ:"<<endl;
    for (i = 0; i < length; i++)
    {
        if (H.elem[i] != NULL_KEY)
        {
            cout<<i<<" -> "<<H.elem[i]<<endl;
        }
    }
    cout<<endl;
}


int main()
{
    HashTable H;
    InitHashTable(H);
    ElemType help[N];
    int i, n;
    int back;
    cout<<"���ݸ���:    ";
    cin>>n;
    for (i = 0; i < n; i++)
    {
        cin>>help[i];
        back = InsertHash(H, help[i]);
        if (back == duplicate)
            cout<<"���йؼ���!!!"<<endl;
        else if (back == ok)
            cout<<"����ɹ�!!!"<<endl;
        else if (back == unsuccess)
            cout<<"�ؽ���ϣ��!!!"<<endl;

    }
    TraverseHash(H);

}





