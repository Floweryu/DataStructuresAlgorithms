/**
* Author : ZhangJunFeng
* Date : 2018-12-06-15.24.20
* Function: 迪杰斯特拉算法求最短路径
* Description : 采用邻接矩阵的存储方式。输出情况按照OJ要求。
* Algorithm description :   1，算法可以求从任何顶点到其余各点的最短路径。
                            2，从一点v出发，选择一条从v出发的最短路径的边。修改下一次可达的最短路径的长度。
* The test data :  out: 6 4 7
4 1
0 3 0 1
0 0 4 0
2 0 0 0
0 0 1 0
*/
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

typedef bool PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];    //若P[v][w]为true，则w是v0到v当前求得的最短路径的顶点。
typedef int ShortPathTable[MAX_VERTEX_NUM];                 //D[]表示从起始点v0到终点v的最短路径的长度。
int start;      //开始顶点

//Dijkstra 算法求最短路径
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &P, ShortPathTable &D)   //v0是起始点
{
    int v, w, i, j;
    int min;
    bool final[MAX_VERTEX_NUM];             //final[v]为true，即以求得v0到v的最短路径。

    for (v = 0; v < G.vexnum; v++)
    {
        final[v] = false;                   //初始化
        D[v] = G.arcs[v0][v];               //v0到v最短路径的长度

        for (w = 0; w < G.vexnum; w++)
        {
            P[v][w] = false;                //初始化没有路径
        }
        if (D[v] < MAXCOST)                 //从v0 到v 有路径
        {
            P[v][v0] = P[v][v] = true;      //v0和v是  v0到v当前求得最短路径顶点
        }
    }   //for

    D[v0] = 0;               //v0到v0最短路径为0
    final[v0] = true;        //v0已被求得最短路径

    for (i = 1; i < G.vexnum; i++)          //除去v0的其余各顶点
    {
        min = MAXCOST;                      //初始化

        //求v0到各顶点中路径最短的一个顶点，赋值给v
        for (w = 0; w < G.vexnum; w++)
        {
            if (! final[w] && D[w] < min)   //w顶点还没被访问，且w顶点离v0顶点更近
            {
                v = w;                      //记录w顶点
                min = D[w];                 //记录w到v0的最短路径
            }
        }
        final[v] = true;                    //v被访问（即w顶点已被访问）

        for (w = 0; w < G.vexnum; w++)      //更新当前最短路径及距离
        {
            //此时v表示上述w，此w为当前遍历的顶点。
            if (! final[w] && (min + G.arcs[v][w] < D[w]))  //若新w顶点未被访问，比较路径(v0,v,w)和路径(v0,w)
            {
                D[w] = min + G.arcs[v][w];                  //更新v0到w的最短路径

                for (j = 0; j < G.vexnum; j++)              //第v行赋值于第w行
                {
                    P[w][j] = P[v][j];
                }
                P[w][w] = true;                  //此时w为v0到w的最短路径的顶点。
            }   // if
        } // for
    }  // for

}


//采用邻接矩阵构造无向图
void CreateUDG(MGraph &G)
{
    int i, j, k;		        //计数器
    int v1, v2;		        //顶点值
    cout<<"输入顶点数：   ";
    cin>>G.vexnum;
    cout<<"输入起始点:    ";
    cin>>start;
    for (i = 0; i < G.vexnum; i++)
    {
    	G.vexs[i] = i;
	}
    cout<<"输入邻接矩阵:   "<<endl;
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
    ShortestPath_DIJ(G, start, p, d);
    int i;
    cout<<"从起始点到终点的最短路径为："<<endl;
    for (i = 0; i < G.vexnum; i++)
    {
        if (i == start)
            continue;
        if (d[i] == 0)
            cout<<"-1 ";
        if (d[i] != 0)
            cout<<d[i]<<" ";
    }
}
