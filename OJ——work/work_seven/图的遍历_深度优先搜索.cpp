#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
using namespace std;

#define MAX_VERTEX_NUM 26   	//定义最大顶点数

bool visited[MAX_VERTEX_NUM] = {0};	//记录已访问过得顶点

typedef struct MGraph       	//图的结构
{
    char vexs[MAX_VERTEX_NUM];       				 //顶点值存储数组
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];        //邻接矩阵
    int vexnum, arcnum;               		         //图的当前顶点数和边数
}MGraph;

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
			//G.arcs[i][j] = 0;
		}
	}

}

//图的深度优先递归遍历
void DFS(MGraph &G, int v)
{
	int w;

	printf("%d ", G.vexs[v]);                   //输出顶点
	visited[v] = 1;                             //输出过得顶点标志位置一

	for (w = 0; w < G.vexnum; w++)              //对存储数组遍历
	{
		if (G.arcs[v][w] && visited[w] == 0)    //如果遍历的顶点与已经输出的顶点有关系（即邻接矩阵为1）
			DFS(G, w);                          //递归输出
	}
}

int main()
{
    MGraph G;
    CreateUDG(G);
    DFS(G, 0);
    cout<<endl;

}
