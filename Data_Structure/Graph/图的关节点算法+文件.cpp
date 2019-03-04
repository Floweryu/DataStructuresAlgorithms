/**
* Author : ZhangJunFeng
* Date : 2018-11-27-17.10.11
* Function: 邻接表表示的图的求关节点算法
* Description :程序使用了文件输入，需要注意的是：
                                    在输入类型是整形时，不需要考虑文件中的换行符、空格符。
                                    在输入类型是字符型时，需要注意接收文件中的空格符与换行符，他们会影响数据的读入。
                                    当然，也可以在写文件时不输入空格符，但必须注意换行符。
                                    可用 fgetc(fp) 来消除空格符和换行符的影响。
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define MAX_NUM 100
#define OK 1
#define ERROR 0

int visited[MAX_NUM];
int low[MAX_NUM], countt;

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

	FILE *f;
	f = fopen("data.txt","r");
	if (f == NULL)
    {
        cout <<"Cannot open the file!!" <<endl;
        exit(-1);
    }

	fscanf(f,"%d",&G.vexnum);
	fscanf(f,"%d",&G.arcnum);
	fgetc(f);       //读取文件中的换行符

    for (i = 0; i < G.vexnum; i++)
    {
        G.vertices[i].data = fgetc(f);
        fgetc(f);        //读取文件中的空格和最后一个字符的换行符
        //fscanf(f,"%c",&G.vertices[i].data);
       // cout  << i << "~" <<G.vertices[i].data <<" ";     //测试
        G.vertices[i].firstedge = NULL;         //初始化头指针
    }
    //fgetc(f);       //读取文件中的换行符

    for (k = 0; k < G.arcnum; k++)
    {
        VertexType v1, v2;
        int i, j;
        v1 = fgetc(f);
        fgetc(f);       //读取文件中的空格符
        v2 = fgetc(f);
        fgetc(f);       //读取文件中的换行符
        //fscanf(f,"%c",&v1);
        //fgetc(f);       //读取文件中的空格符
        //fscanf(f,"%c",&v2);
        //fgetc(f);       //读取文件中的换行符
       // cout << v1 << "~~" <<v2<<endl;  //测试
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

    cout << "请输入总顶点数，总边数：   ";
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
                cout << v0 << " " <<G.vertices[v0].data << endl;
        }
        else if (visited[w] < minn)
                minn = visited[w];
    }

    low[v0] = minn;
/*
    p = G.vertices[v0].firstedge;        //p 指向顶点 v 的第一条边
    while (p != NULL)
    {
        w = p->adjvex;
        if (visited[w] == 0)
        {
            DFSArticul(G, w);
            if (low[w] < minn)
                minn = low[w];
            if (low[w] >= visited[v0])
                cout << v0 << " " <<G.vertices[v0].data << endl;
        }
        else if (visited[w] < minn)
                minn = visited[w];
        p = p->next;
    }
*/
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
        cout << 0 <<" "<< G.vertices[0].data <<endl;
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
    vvCreateUDC(G);
    cout <<"邻接表图为：\n";
    PrintfAdjList(G);
    cout << "关节点为：\n";
    FindArticul(G);
}
