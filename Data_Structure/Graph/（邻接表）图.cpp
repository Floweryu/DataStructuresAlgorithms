/**
* Author : ZhangJunFeng
* Date : 2018-11-27-15.24.41
* Function: （邻接表）实现的图，包含其深度和广度优先遍历、建立
* Description :
*/
#include "link_queue.h"
#include <iostream>
#include <string.h>

using namespace std;

#define MAX_NUM 100
#define OK 1
#define ERROR 0

bool visited[MAX_NUM] = {0};

typedef char VertexType;         //顶点类型
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

//获取顶点在存储数组中的位置
int LocateVex(ALGraph G, VertexType v)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data == v)
            return i;
    }
    return ERROR;
}

//采用邻接表表示法创建无向图G(输入两两顶点值关系）
int vvCreateUDC(ALGraph &G)
{
    int i, k;

    cout << "请输入总顶点数，总变数：   ";
    cin >> G.vexnum >> G.arcnum;
    cout << endl;

    cout << "请输入顶点的值：" << endl;
    for (i = 0; i < G.vexnum; i++)
    {
        cin >> G.vertices[i].data;
        G.vertices[i].firstedge = NULL;         //初始化头指针
    }
    cout << endl;

    cout << "请输入" << G.arcnum << "条边的顶点关系:" << endl;

    for (k = 0; k < G.arcnum; k++)
    {
        VertexType v1, v2;
        int i, j;
        cin >> v1 >> v2;

        i = LocateVex(G, v1);
        j = LocateVex(G, v2);

        ArcNode *p1 = new ArcNode;
        p1->adjvex = j;
        p1->next = G.vertices[i].firstedge;     //把p1节点插入到链表中
        G.vertices[i].firstedge = p1;

        ArcNode *p2 = new ArcNode;              //把p2节点插入到链表中
        p2->adjvex = i;
        p2->next = G.vertices[j].firstedge;
        G.vertices[j].firstedge = p2;
    }

    return OK;
}


//采用邻接表表示法创建无向图G(输入两两顶点的坐标值关系）
int ijCreateUDC(ALGraph &G)
{
    int i, k;

    cout << "请输入总顶点数，总变数：   ";
    cin >> G.vexnum >> G.arcnum;
    cout << endl;

    cout << "请输入顶点的值：" << endl;
    for (i = 0; i < G.vexnum; i++)
    {
        cin >> G.vertices[i].data;
        G.vertices[i].firstedge = NULL;         //初始化头指针
    }
    cout << endl;

    cout << "请输入" << G.arcnum << "条边的顶点 下标 关系:" << endl;

    for (k = 0; k < G.arcnum; k++)
    {
        int i, j;
        cin >> i >> j;

        ArcNode *p1 = new ArcNode;
        p1->adjvex = j;
        p1->next = G.vertices[i].firstedge;     //把p1节点插入到链表中
        G.vertices[i].firstedge = p1;

        ArcNode *p2 = new ArcNode;              //把p2节点插入到链表中
        p2->adjvex = i;
        p2->next = G.vertices[j].firstedge;
        G.vertices[j].firstedge = p2;
    }

    return OK;
}

//深度优先遍历
void DFS(ALGraph G, int v)
{
    ArcNode *p;
    if (v < 0 || v >= G.vexnum)
        return;
    else
    {
        cout << G.vertices[v].data << " ";
        visited[v] = true;

        p = G.vertices[v].firstedge;        //p 指向顶点 v 的第一条边
        while (p != NULL)
        {
            if (visited[p->adjvex] != 1)
            {
                DFS(G, p->adjvex);
            }
            p = p->next;
        }
    }
}

//广度优先遍历
void BFS(ALGraph G, int v)
{
    memset(visited, 0, sizeof(visited));
    VertexType w;
    int u;

    LinkQueue Q;
    Init_Queue(Q);

    w = G.vertices[v].data;
    cout << w <<" ";
    visited[v] = true;
    Push_Queue(Q, v);

    while (! Empty_Queue(Q))
    {
        Pop_Queue(Q, u);
        ArcNode *p;
        p = G.vertices[u].firstedge;
        while (p)
        {
            if (! visited[p->adjvex])
            {
                cout << G.vertices[p->adjvex].data << " ";
                visited[p->adjvex] = true;
                Push_Queue(Q, p->adjvex);
            }
            p = p->next;
        }

    }
}







//输出邻接表
void PrintfAdjList(ALGraph G)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        ArcNode *p = G.vertices[i].firstedge;

        while (p)
        {
            cout << G.vertices[i].data << "->" << G.vertices[p->adjvex].data << "  ";
            p = p->next;
        }
        cout << endl;
    }
}

int main()
{
    ALGraph G;

    ijCreateUDC(G);
    PrintfAdjList(G);
    cout << "深度优先搜索遍历：\n";
    DFS(G, 0);
    cout << endl;
    cout << "广度优先搜素遍历：\n";
    BFS(G, 0);
}
