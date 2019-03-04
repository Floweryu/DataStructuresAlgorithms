#include <iostream>

using namespace std;

typedef int TElemType;
#define MAX_VERTEX_NUM 100   	//定义最大顶点数
#define MAX_NUM 100
#define MAXCOST 10000

typedef struct CSNode
{
	TElemType data;
	CSNode *firstchild, *nextsibling;
}CSNode, *CSTree;

//邻接矩阵
typedef struct MGraph
{
    int vexs[MAX_VERTEX_NUM];       		    //顶点值存储数组
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   //邻接矩阵
    int vexnum, arcnum;               		    //图的当前顶点数和边数
}MGraph;


bool visited[MAX_NUM];

//获取字符在存储数组中的位置
int LocateVex(MGraph &G, int v)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vexs[i] == v)
        	return i;
    }
    return -1;
}

//返回图中某顶点的值
int  GetVex(MGraph G, int v)
{
    return G.vexs[v];
}

//返回第一个邻接顶点的序号
int FirstAdjVex(MGraph G, int v)
{
    int j, t;
    t = MAXCOST;
    for (j = 0; j < G.vexnum; j++)
    {
        if (G.arcs[v][j] != t)
            return j;
    }
    return -1;
}

//返回下一个邻接顶点的序号
int NextAdjVex(MGraph G, int v, int w)
{
    int j, t;
    t = MAXCOST;
    for (j = w + 1; j < G.vexnum; j++)
    {
        if (G.arcs[v][j] != MAXCOST)
            return j;
    }
    return -1;
}

//深度遍历图建立生成树
void DFSTree(MGraph G, int v, CSTree &T)
{

    cout<<G.vexs[v]<<" ";
    int w;
    CSTree p, q;
    bool first = true;
    visited[v] = true;

    for (w = FirstAdjVex(G, v); w != -1; w = NextAdjVex(G, v, w))
    {
        if (! visited[w])
        {
            p = new CSNode;
            p->data = GetVex(G, w);
            p->firstchild = NULL;
            p->nextsibling = NULL;
            if (first)
            {
                T->firstchild = p;
                first = false;
            }
            else
            {
                q->nextsibling = p;
            }
            q = p;
            DFSTree(G, w, q);
        }  //if
    }   //DFSTree
}

//无向图深度优先生成森林的左孩子又兄弟链表
void DFSForest(MGraph G, CSTree &T)
{
    int v, j = 0;
    CSTree p, q;
    T = NULL;

    for (v = 0; v < G.vexnum; ++v)  //初始化
    {
        visited[v] = false;
    }
    for (v = 0; v < G.vexnum; ++v)
    {
        if ( ! visited[v])           //v 为新的生成树根节点
        {
            p = new CSNode;
            p->data = GetVex(G, v);
            p->firstchild = NULL;
            p->nextsibling = NULL;
            if (! T)                //第一个生成树的根
            {
                T = p;
            }
            else
            {
                q->nextsibling = p;    //其他生成树的根
            }
            q = p;               //指向当前
            DFSTree(G, v, p);
            cout<<endl;
        }   //if
    } //for
}   //DFSForest


//采用邻接矩阵构造无向图
void CreateUDG(MGraph &G)
{
    int i, j, k;		         //计数器
    int v1, v2;		             //顶点值

    cin>>G.vexnum;
    for (i = 0; i < G.vexnum; i++)
    {
    	G.vexs[i] = i;
	}

	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
		{
		    cin>>G.arcs[i][j];
		    if(G.arcs[i][j] == 0)
                G.arcs[i][j] = MAXCOST;
		}
	}

}



int main()
{
    MGraph G;
    CreateUDG(G);
    CSTree T;
    DFSForest(G, T);

}
