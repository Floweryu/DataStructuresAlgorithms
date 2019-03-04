/**
* Author : ZhangJunFeng
* Date : 2018-12-06-19.49.54
* Function: 实现图的关键路径
* Description :
* Algorithm description :
* The test data :
*/

#include "single_stack.h"
#include <iostream>
#include <stack>
using namespace std;

#define MAX_VERTEX_NUM  100
#define ERROR 0
#define OK 1
int ve[MAX_VERTEX_NUM];
int vl[MAX_VERTEX_NUM];
LinkStack T;

typedef struct MGraph                           //图的邻接矩阵存储结构
{
    int vexs[MAX_VERTEX_NUM];
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
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
            if (G.arcs[i][j])                   //从i顶点到j顶点有入度
            {
                indegree[j]++;                  //该顶点入度数加一
            }
        }
    }
}

//拓扑排序
int TopologicalOrder(MGraph G)
{
    LinkStack S;
    int count, i, j;             //k 和num[]数组配合
    int indegree[MAX_VERTEX_NUM];

    FindInDegree(G, indegree);

    Init_Stack(S);
    Init_Stack(T);

    for (i = 0; i < G.vexnum; ++i)
    {
        if (! indegree[i])              //入度为 0 的进栈，此时按照顶点下标的顺序
            Push_Stack(S, i);
    }

    for (i = 0; i < G.vexnum; i++)
    {
        ve[i] = 0;
    }

    count = 0;                          //统计输出顶点个数

    while (! Empty_Stack(S))
    {
        Pop_Stack(S, i);                //输出栈顶元素
        Push_Stack(T, i);               //存储输出的元素

        count++;

        for (j = 0; j < G.vexnum; ++j)  //相邻顶点入度数减一，并把入度数为 0 的入栈
        {
            if (G.arcs[i][j])
            {
                if (! (--indegree[j]))    //入度减一，入度为 0 的入栈
                    Push_Stack(S, j);

                if (ve[i] + G.arcs[i][j] > ve[j])
                {
                    ve[j] = ve[i] + G.arcs[i][j];
                }
            }
        }   //  for
    }   //  while


    if (count != G.vexnum)
        return ERROR;       //有环
    else
    {
        cout<<"拓扑排序:    :";
        Printf_Stack(T);
        cout<<endl;         //这个不加就输出两个结果
    }

}


void CriticalPath(MGraph &G)
{
    if (! TopologicalOrder(G))
        cout<<"这是一个有环图！！"<<endl;

    int i, j;
    int v, dut, ee, el;
    for (i = 0; i < G.vexnum; i++)
    {
        vl[i] = ve[G.vexnum - 1];
    }

    while (! Empty_Stack(T))
    {
        Pop_Stack(T, v);

        for (j = 0; j < G.vexnum; j++)
        {
            if (G.arcs[v][j])
            {
                dut = G.arcs[v][j];
                if (vl[j] - dut < vl[v])
                    vl[v] = vl[j] - dut;
            }
        }
    }

    cout<<"ve数组    :";
    for (j = 0; j < G.vexnum; j++)
    {
        cout<<ve[j]<<" ";
    }
    cout<<endl;

    cout<<"vl数组    :";
    for (j = 0; j < G.vexnum; j++)
    {
        cout<<vl[j]<<" ";
    }
    cout<<endl;

    cout<<"j->k->权值->ee->el"<<endl;
    for (j = 0; j < G.vexnum; j++)
    {
        for (i = 0; i < G.vexnum; i++)
        {
            if (G.arcs[j][i])
            {
                dut = G.arcs[j][i];
                ee = ve[j];
                el = vl[i] - dut;
                if (ee == el)
                    cout<<j<<"->"<<i<<"->"<<dut<<"->"<<ee<<"->"<<el<<endl;
            }
        }
    }

}

//采用邻接矩阵构造有向图
void CreateUDG(MGraph &G)
{
    int i, j, k;		        //计数器
    int v1, v2;		            //顶点值

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
    MGraph M;
    CreateUDG(M);

    CriticalPath(M);
}








