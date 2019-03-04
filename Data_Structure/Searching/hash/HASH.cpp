/**
* Author : ZhangJunFeng
* Date : 2018-12-18-16.46.48
* Function: 哈希查找算法
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

int hashsize[] = {11, 19, 29, 37};      //哈希表容量递增表
int length, c;                             //哈希表表长

typedef int ElemType;

struct HashTable
{
    ElemType *elem;                     //数据元素存储基址，动态分配数组
    int count;                          //当前数据元素个数
    int sizeindex;                      //hashsize[sizeindex] 为当前容量
};

//构造一个空的哈希表
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

//哈希函数，求哈希地址
int Hash(ElemType K)
{
    return (K % length);
}

//开放定址法--线性探测再散列
int collision(ElemType K)
{
    return (Hash(K) + 1) % length;
}

//查看哈希表中是否存在K元素
int SearchHash(HashTable H, ElemType K, int &p)
{
    int c = 0;
    p = Hash(K);
    while (H.elem[p] != NULL_KEY && H.elem[p] != K)     //如果该地址有记录 并且 该记录与K不相等
    {
        c++;
        p = collision(K);                               //地址向后移动
    }
    //跳出循环时 p 处值为空 或者 该处值等于K

    if (H.elem[p] == K)
        return success;
    else
        return unsuccess;
}

void ReCreateHashTable(HashTable H);


//向哈希表中插入元素
int InsertHash(HashTable H, ElemType e)
{
    int p;
    if (SearchHash(H, e, p))
        return duplicate;
    else if (c < hashsize[H.sizeindex] / 2)         //为什么除以2？？？？？？？？？？？？？？
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

//重建哈希表
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
    cout<<"哈希地址:"<<endl;
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
    cout<<"数据个数:    ";
    cin>>n;
    for (i = 0; i < n; i++)
    {
        cin>>help[i];
        back = InsertHash(H, help[i]);
        if (back == duplicate)
            cout<<"已有关键字!!!"<<endl;
        else if (back == ok)
            cout<<"插入成功!!!"<<endl;
        else if (back == unsuccess)
            cout<<"重建哈希表!!!"<<endl;

    }
    TraverseHash(H);

}





