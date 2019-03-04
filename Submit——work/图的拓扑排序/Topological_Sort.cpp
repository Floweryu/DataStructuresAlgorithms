/**
* Author : ZhangJunFeng
* Date : 2018-12-03-20.33.25
* Function: 拓扑排序
* Description :     使用邻接矩阵来表示图，借用了栈来实现
*/
#include "single_stack.h"
#include <iostream>
using namespace std;


#define MAX_VERTEX_NUM  100
typedef struct MGraph       //图的邻接矩阵存储结构
{
    int vexs[MAX_VERTEX_NUM];       		    //顶点值存储数组
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   //权值
    int vexnum, arcnum;               		    //图的当前顶点数和边数
}MGraph;


void FindInDegree(MGraph G, int indegree[])     //计算每个顶点的入度
{
    int i, j;
    for (i = 0; i < G.vexnum; ++i)              //初始化
    {
        indegree[i] = 0;
    }

    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
        {
            if (G.arcs[i][j])           //从i顶点到j顶点有入度
            {
                indegree[j]++;
            }
        }
    }
}


//拓扑排序
void TopologicalSort(MGraph G)
{
    LinkStack S;
    int count, k = 0, i, j;
    int num[MAX_VERTEX_NUM];            //记录存储输出顶点
    int indegree[MAX_VERTEX_NUM];

    FindInDegree(G, indegree);

    Init_Stack(S);

    for (i = 0; i < G.vexnum; ++i)
    {
        if (! indegree[i])          //入度为 0 的进栈，此时按照顶点下标的顺序
            Push_Stack(S, i);
    }

    count = 0;          //统计输出顶点个数

    while (! Empty_Stack(S))
    {
        Pop_Stack(S, i);
        num[k] = G.vexs[i];
        k++;
        count++;

        for (j = 0; j < G.vexnum; ++j)
        {
            if (G.arcs[i][j])
            {
                if (! (--indegree[j]))      //入度减一，入度为 0 的入栈
                    Push_Stack(S, j);
            }
        }
    }

    if (count < G.vexnum)
    {
        cout<<"这是一个有环图！！"<<endl;
    }
    else
    {
        cout<<"拓扑序列为：   ";
        for (i = 0; i < G.vexnum; i++)
            cout<<num[i]<<" ";
    }
}

//采用邻接矩阵构造有向图
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
		}
	}

}

int main()
{
    MGraph G;
    CreateUDG(G);
    TopologicalSort(G);
}
