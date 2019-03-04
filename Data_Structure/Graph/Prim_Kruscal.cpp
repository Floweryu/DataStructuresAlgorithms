/**
* Author : ZhangJunFeng
* Date : 2018-12-06-19.52.14
* Function: PRIM和Kruscal算法构造最小生成树
* Description : 图的存储结构为邻接矩阵，此算法可求 生成树上的边 和 最小代价。
* Algorithm description :   1，借助了辅助变量closedge[], {adjvex (顶点), lowcost (与该顶点相关顶点的代价)}
                            2，从某个顶点出发，求与之相连顶点代价最小值。
                            3，遍历各个顶点，重复2步骤。
* The test data :
4
0 2 4 0
2 0 3 5
4 3 0 1
0 5 1 0
*/
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
    int j, k, min = MAXCOST;

    k = 0;
    for (j = 0; j < G.vexnum; j++)
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

    for (j = 0; j < G.vexnum; ++j)          //closedge[]赋值为与 u 相关的权值
    {
        if (j != k)
        {
            closedge[j].adjvex = u;
            closedge[j].lowcost = G.arcs[k][j];
        }
    }
    closedge[k].lowcost = 0;                //表示该顶点已被选取

    for (i = 1; i < G.vexnum; i++)
    {
        k = minimum(closedge, G);           //寻找最小代价

        cout<<G.vexs[closedge[k].adjvex]<<"->"<<G.vexs[k]<<endl;
        closedge[k].lowcost = 0;             //第 k 个顶点并入U集

        for(j = 1; j < G.vexnum; j++)
        {
            if (G.arcs[k][j] < closedge[j].lowcost)     //与新起始点有关的权值 和 与上一个顶点有关的权值比较
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

    cout<<"输入顶点数：   ";
    cin>>G.vexnum;
    for (i = 0; i < G.vexnum; i++)
    {
    	G.vexs[i] = i;
	}

    cout<<"输入邻接矩阵:  "<<endl;
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
    cout<<"最小生成树的边："<<endl;
    MiniSpanTree_PRIM(G, G.vexs[0]);
    cout<<endl;
    cout<<"最小代价:   ";
    cout<<count;
}
