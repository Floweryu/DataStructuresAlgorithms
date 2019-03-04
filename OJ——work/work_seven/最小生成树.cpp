#include <iostream>
using namespace std;

#define MAX_VERTEX_NUM  100
#define MAXCOST 10000
int count = 0;
typedef struct
{
    int adjvex;
    int lowcost;
} Edge;         //PRIM 算法中的辅助信息

typedef struct MGraph
{
    int vexs[MAX_VERTEX_NUM];       		    //顶点值存储数组
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   //邻接矩阵
    int vexnum, arcnum;               		    //图的当前顶点数和边数
}MGraph;

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


//求最小正直并返回序号
int minimum(Edge closedge[], MGraph G)
{
    int i= 0, j, k, min;
    while (!closedge[i].lowcost)
    {
        i++;
    }
    min = closedge[i].lowcost;
    k = i;
    for (j = i + 1; j < G.vexnum; j++)
    {
        if (closedge[j].lowcost > 0 && closedge[j].lowcost < min)
        {
            min = closedge[j].lowcost;
            k = j;
        }
    }
    count = count + min;
    return k;
}

//普利姆算法构造最小生成树
void MiniSpanTree_PRIM(MGraph &G, int u)
{
    int i, j, k;
    Edge closedge[MAX_VERTEX_NUM];

    k = LocateVex(G, u);

    for (j = 0; j < G.vexnum; ++j)
    {
        if (j != k)
        {
            closedge[j].adjvex = u;
            closedge[j].lowcost = G.arcs[k][j];
        }
    }
    closedge[k].lowcost = 0;        //初始值

    for (i = 1; i < G.vexnum; i++)
    {
        k = minimum(closedge, G);

        //cout<<G.vexs[closedge[k].adjvex]<<"->"<<G.vexs[k]<<"  ";
        closedge[k].lowcost = 0;        //第 k 个顶点并入U集

        for(j = 1; j < G.vexnum; j++)
        {
            if (G.arcs[k][j] < closedge[j].lowcost)     //重新选取最小边
            {
                closedge[j].adjvex = G.vexs[k];
                closedge[j].lowcost = G.arcs[k][j];
            }
        }
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
    CreateUDG(G);
    MiniSpanTree_PRIM(G, G.vexs[0]);
    cout<<count;
}

















