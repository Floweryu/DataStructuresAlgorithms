#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <algorithm>

using namespace std;

#define MAX_VERTEX_NUM 100   	//定义最大顶点数

typedef struct MGraph       	//图的结构
{
    char vexs[MAX_VERTEX_NUM];       				 //顶点值存储数组
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];        //邻接矩阵
    int vex, arc;               		         //图的当前顶点数和边数
}MGraph;


#define MAX_NUM 100
#define OK 1
#define ERROR 0

int visited[MAX_NUM];
int low[MAX_NUM], countt;
int num[MAX_NUM];
int num_countt = 0;


typedef int VertexType;         //顶点类型
typedef int InfoType;           //边上的权值类型

typedef struct ArcNode
{
    int adjvex;         //存储顶点对应的下标
    InfoType weight;    //存储权值，对于非网图不需要
    struct ArcNode *next;  //指向下一个邻接点
} ArcNode;

typedef struct VNode
{
    VertexType data;          //存储顶点信息
    ArcNode *firstedge;       //边表头指针

} VNode, AdjList[MAX_NUM];

typedef struct
{
    AdjList vertices;       //存储顶点的数组
    int vexnum, arcnum;     //图的当前顶点数和弧数
}ALGraph;


//采用邻接矩阵构造无向图
void CreateUDG(MGraph &M)
{
    int i, j;		        //计数器
    int count = 0;
    cin>>M.vex;     //顶点数目

	for (i = 0; i < M.vex; i++)
	{
		for (j = 0; j < M.vex; j++)
		{
		    cin>>M.arcs[i][j];
		    if (M.arcs[i][j])
                count++;
		}
	}
    M.arc = count / 2;

}


int TransMA(MGraph &M, ALGraph &G)
{
    int i, j, k;

    G.vexnum = M.vex;
    G.arcnum = M.arc;

    for (i = 0; i < G.vexnum; i++)
    {
        G.vertices[i].data = i;
        G.vertices[i].firstedge = NULL;         //初始化头指针
    }

    for (i = 0; i < G.vexnum; i++)
    {
        for (j = G.vexnum - 1; j >= 0; j--)     //从尾部开始插入
        {
            if (M.arcs[i][j])
            {
                ArcNode *p1 = new ArcNode;
                p1->adjvex = j;
                p1->next = G.vertices[i].firstedge;     //把p1节点插入到链表中
                G.vertices[i].firstedge = p1;
            }
        }
    }

    return OK;
}

//深度优先遍历
void DFSArticul(ALGraph G, int v0)
{
    ArcNode *p;
    int w, minn;
    visited[v0] = minn = ++countt;

    for (p = G.vertices[v0].firstedge; p; p = p->next)
    {
        w = p->adjvex;
        if (visited[w] == 0)
        {
            DFSArticul(G, w);
            if (low[w] < minn)
                minn = low[w];
            if (low[w] >= visited[v0])
            {
                //cout << v0 << " " <<G.vertices[v0].data << endl;
                num[num_countt] = v0;
                num_countt++;
            }
        }
        else if (visited[w] < minn)
                minn = visited[w];
    }

    low[v0] = minn;
}

void FindArticul(ALGraph G)
{
    int i, v;
    countt = 1;
    visited[0] = 1;
    low[0] = 1;

    for (i = 1; i < G.vexnum; i++)
        visited[i] = 0;
    ArcNode *p;
    p = G.vertices[0].firstedge;
    v = p->adjvex;
    DFSArticul(G, v);
    if (countt < G.vexnum)
    {
        //cout << 0 <<" "<< G.vertices[0].data <<endl;
        num[num_countt] = 0;
        num_countt++;
        while (p->next)
        {
            p = p->next;
            v = p->adjvex;
            if (visited[v] == 0)
                DFSArticul(G, v);
        }
    }
}

int main()
{
    ALGraph G;
    MGraph M;
    int i, j, temp;
    CreateUDG(M);
    TransMA(M, G);
    FindArticul(G);
    sort(num, num + num_countt);        //对数组进行排序
    num_countt = unique(num, num + num_countt) - num;       //删除数组中重复的数字

    cout<<num_countt<<endl;
    for (i = 0; i < num_countt; i++)
        cout<<num[i]<<" ";
    cout<<endl;
}
