#include <cstring>
#include <iostream>

using namespace std;

typedef struct{
    unsigned int weight;
    unsigned int parent,lchild,rchild;
}HTNode, * HuffmanTree;

typedef char** HuffmanCode;

void select(HuffmanTree HT,int n,int &s1,int &s2)
{
    unsigned min1 = 2 * INT_MAX + 1, min2 = 2 * INT_MAX + 1;

    for(int i = 1;i <= n;i++)
    {
        if(HT[i].parent != 0)
            continue;

        if(HT[i].weight < min1)
        {
            min1 = HT[i].weight;
            s1 = i;
        }
    }
    for(int i = 1;i <= n;i++)
    {
        if(HT[i].parent != 0 || i == s1)
            continue;

        if(HT[i].weight < min2)
        {
            min2 = HT[i].weight;
            s2 = i;
        }
    }
    if(s1 > s2)
    {
        int temp;
        temp = s1;
        s1 = s2;
        s2 = temp;
    }

}

void huffmanCoding(HuffmanTree &HT,HuffmanCode &HC, int *w,int n)
{
    //如果只有1个节点或者小于1个节点
    if(n <= 1)
        return ;
    //总节点的个数
    int num_of_node = 2 * n - 1;

    HT = new HTNode [num_of_node + 1];

    //初始化
    HT[0] = {0,0,0,0};
    for(int i = 1;i <= n;i++)
        HT[i] = {w[i-1],0,0,0};
    for(int i = n + 1;i <= num_of_node;i++)
        HT[i] = {0,0,0,0};
//    for(int i = 0;i <= num_of_node;i++)
//        cout<<i<<" "<<HT[i].weight<<" "<<HT[i].parent<<" "<<HT[i].lchild<<" "<<HT[i].rchild<<endl;

    for(int i = n+1;i <= num_of_node;i++)
    {
        int s1,s2;  //s1,s2为最小的两个序列
        select(HT,i - 1,s1,s2);
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
//    cout<<"霍夫曼树的存储"<<endl;
//    for(int i = 0;i <= num_of_node;i++)
//        cout<<i<<" "<<HT[i].weight<<" "<<HT[i].parent<<" "<<HT[i].lchild<<" "<<HT[i].rchild<<endl;

    HC = new char* [n+1];
    char *radis = new char [n];
    radis[n-1] = '\0';
    for(int i = 1;i <= n;i++)
    {
        int start = n - 2;
        int c = i;
        int f = HT[i].parent;
        for(;f != 0;c = f,f = HT[f].parent)
        {
            if(HT[f].lchild == c)
                radis[start] = '0';
            else
                radis[start] = '1';
            start--;
        }
        HC[i] = new char (n - start - 1);
        strcpy(HC[i],&radis[++start]);
    }
    delete radis;
}

