#include <iostream>

using namespace std;

#define MAX_TREE_SIZE 100
typedef int TElemType;

typedef struct PTNode
{
    TElemType data;
    int parent;
}PTNode;

typedef struct      //树结构
{
    PTNode nodes[MAX_TREE_SIZE];
    int r, n;       //根的位置和节点数
}PTree;

//找集合中所在子集的根
int find_mfset(PTree S, int i)
{
    int j;
    if (i < 1 || i > S.n)
        return -1;
    for (j = i; S.nodes[j].parent > 0; j = S.nodes[j].parent);
    return j;
}

//合并函数
bool merge_mfset(PTree &S, int i, int j)
{
    if (i < 1 || i > S.n || j < 1 || j > S.n)
        return false;

    S.nodes[i].parent = j;
    return true;
}

//优化后的合并函数
bool mix_mfset(PTree &S, int i, int j)
{
    if (i < 1 || i > S.n || j < 1 ||j > S.n)
        return false;

    if (S.nodes[i].parent > S.nodes[j].parent)
    {
        S.nodes[j].parent += S.nodes[i].parent;
        S.nodes[i].parent = j;
    }
    else
    {
        S.nodes[i].parent += S.nodes[j].parent;
        S.nodes[j].parent = i;
    }
    return true;
}

//优化后的查找函数
int fix_mfset(PTree &S, int i)
{
    int j, k, t;
    if (i < 1 || i >S.n)
        return false;
    for (j = i; S.nodes[j].parent > 0; j = S.nodes[j].parent);
    for (k = i; k != j; k = t)
    {
        t = S.nodes[k].parent;
        S.nodes[k].parent = j;
    }
    return j;
}


int main()
{
    PTree S;
    int n, k;
    cin>>n>>k;
    int i, j;
    for (i = 1; i <= n; i++)
    {
        S.nodes[i].data = i;
        S.nodes[i].parent = -1;
        S.n++;
    }

    int x, y;
    int root1, root2;
    for (i = 0; i < k; i++)
    {
        cin>>x>>y;
        for (j = 1; j <= n; j++)
        {
            if (S.nodes[j].data == x)
                root1 = fix_mfset(S, j);
            if (S.nodes[j].data == y)
                root2 = fix_mfset(S, j);
        }
        mix_mfset(S, root1, root2);
    }

    int p1, p2;
    cin>>p1>>p2;
    root1 = fix_mfset(S, p1);
    root2 = fix_mfset(S, p2);
    if (root1 == root2)
        cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;

}









