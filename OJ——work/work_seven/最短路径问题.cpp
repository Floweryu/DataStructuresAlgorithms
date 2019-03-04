#include <iostream>
using namespace std;

#define MAX_VERTEX_NUM  100
#define MAXCOST 65535

typedef struct
{
    int cost;       //花费
    int distant;    //距离
}AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct MGraph
{
    int vexs[MAX_VERTEX_NUM];       		    //顶点值存储数组
    AdjMatrix arcs;                             //邻接矩阵
    int vexnum, arcnum;               		    //图的当前顶点数和边数
}MGraph;

typedef int ShortPathTable[MAX_VERTEX_NUM];
typedef int CostPath[MAX_VERTEX_NUM];
int start, over;


//Dijkstra 算法求最短路径
void ShortestPath_DIJ(MGraph G, int v0, ShortPathTable &D, CostPath &C)
{
    int v, w, i, j;
    int min;
    bool final[MAX_VERTEX_NUM];
    for (v = 1; v <= G.vexnum; v++)
    {
        final[v] = false;           //初始化
        D[v] = G.arcs[v0][v].distant;
        C[v] = G.arcs[v0][v].cost;
    }

    D[v0] = 0;
    C[v0] = 0;
    final[v0] = true;

    for (i = 2; i <= G.vexnum; i++)
    {
        min = MAXCOST;
        for (w = 1; w <= G.vexnum; w++)
        {
            if (! final[w] && D[w] < min)
            {
                v = w;
                min = D[w];
            }
        }


        final[v] = true;

        for (w = 1; w <= G.vexnum; w++)
        {
            if (! final[w] && (min + G.arcs[v][w].distant < D[w]))
            {

                D[w] = min + G.arcs[v][w].distant;
                C[w] = C[v] + G.arcs[v][w].cost;
            }
            else if (! final[w] && (min + G.arcs[v][w].distant == D[w]))
            {
                if ((C[v] + G.arcs[v][w].cost) < C[w])
                    C[w] = C[v] + G.arcs[v][w].cost;
            }


        } // for
    }  // for

}

//获取字符在存储数组中的位置
int LocateVex(MGraph &G, int v)
{
    int i;
    for (i = 1; i <= G.vexnum; i++)
    {
        if (G.vexs[i] == v)
        	return i;
    }
    return -1;
}


int main()
{
    int i, j, k;		        //计数器
    int v1, v2, dis, cos;		        //顶点值
    MGraph G;

    while (cin>>G.vexnum>>G.arcnum, G.vexnum!=0 && G.arcnum!=0)
    {
        ShortPathTable d;
        CostPath c;

        for (i = 1; i <= G.vexnum; i++)
        {
            G.vexs[i] = i;
        }

        for (i = 1; i <= G.vexnum; i++)      //把邻接矩阵数组置为0
        {
            for (j = 1; j <= G.vexnum; j++)
            {
                G.arcs[i][j].distant = MAXCOST;
                G.arcs[i][j].cost = 0;
            }
        }

        for (k = 0; k < G.arcnum; k++)
        {
            cin>>v1>>v2>>dis>>cos;

            i = LocateVex(G, v1);			//寻找顶点值在存储数组中的位置
            j = LocateVex(G, v2);

            G.arcs[i][j].distant = dis; 			        	//构建邻接矩阵，有关系的赋值为1
            G.arcs[j][i].distant = G.arcs[i][j].distant;	//无向图，两个单元信息相同

            G.arcs[i][j].cost = cos;
            G.arcs[j][i].cost = G.arcs[i][j].cost;
        }

        cin>>start>>over;
        ShortestPath_DIJ(G, start, d, c);
        cout<<d[over]<<" "<<c[over]<<endl;;
    }
}
