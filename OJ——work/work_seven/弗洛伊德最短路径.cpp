#include <iostream>
using namespace std;

#define MAX_VERTEX_NUM  100
#define MAXCOST 65535

typedef struct MGraph
{
    int vexs[MAX_VERTEX_NUM];       		    //顶点值存储数组
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   //邻接矩阵
    int vexnum, arcnum;               		    //图的当前顶点数和边数
}MGraph;

typedef bool PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int ShortPathTable[MAX_VERTEX_NUM];

//Dijkstra 算法求最短路径
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &P, ShortPathTable &D)
{
    int v, w, i, j;
    int min;
    bool final[MAX_VERTEX_NUM];
    for (v = 0; v < G.vexnum; v++)
    {
        final[v] = false;           //初始化
        D[v] = G.arcs[v0][v];

        for (w = 0; w < G.vexnum; w++)
        {
            P[v][w] = false;        //初始化没有路径
        }
        if (D[v] < MAXCOST)        //有路径
        {
            P[v][v0] = P[v][v] = true;
        }
    }

    D[v0] = 0;
    final[v0] = true;

    for (i = 1; i < G.vexnum; i++)
    {
        min = MAXCOST;
        for (w = 0; w < G.vexnum; w++)
        {
            if (! final[w] && D[w] < min)
            {
                v = w;
                min = D[w];
            }
        }
        final[v] = true;

        for (w = 0; w < G.vexnum; w++)
        {
            if (! final[w] && (min + G.arcs[v][w] < D[w]))
            {
                D[w] = min + G.arcs[v][w];
                for (j = 0; j < G.vexnum; j++)
                {
                    P[w][j] = P[v][j];
                }
                P[w][w] = true;
            }   // if
        } // for
    }  // for
    for (i = 0; i < G.vexnum; i++)
    {
        if (D[i] == 0 && i == v0)
            cout<<"0 ";
        if (D[i] == 0 && i != v0)
            cout<<"-1 ";
        if (D[i] != 0)
            cout<<D[i]<<" ";
    }
}


//采用邻接矩阵构造无向图
void CreateUDG(MGraph &G)
{
    int i, j, k;		        //计数器
    int v1, v2;		        //顶点值
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
    PathMatrix p;
    ShortPathTable d;
    CreateUDG(G);
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        ShortestPath_DIJ(G, G.vexs[i], p, d);
        cout<<endl;
    }
}
