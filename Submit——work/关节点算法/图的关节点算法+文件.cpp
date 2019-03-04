/**
* Author : ZhangJunFeng
* Date : 2018-11-27-17.10.11
* Function: �ڽӱ��ʾ��ͼ����ؽڵ��㷨
* Description :������õ����ļ����룬���Ϊ�ڽӱ�ͼ�͹ؽڵ㡣
                    13 17
                    0 1 2 3 4 5 6 7 8 9 10 11 12
                    11 0
                    1 0
                    2 0
                    5 0
                    12 11
                    9 12
                    1 12
                    9 11
                    7 1
                    6 1
                    3 1
                    2 1
                    4 3
                    10 7
                    6 10
                    6 7
                    8 6
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

typedef int VertexType;         //��������
typedef int InfoType;           //���ϵ�Ȩֵ����

typedef struct ArcNode
{
    int adjvex;         //�洢�����Ӧ���±�
    InfoType weight;    //�洢Ȩֵ�����ڷ���ͼ����Ҫ
    struct ArcNode *next;  //ָ����һ���ڽӵ�
} ArcNode;

typedef struct VNode
{
    VertexType data;          //�洢������Ϣ
    ArcNode *firstedge;       //�߱�ͷָ��

} VNode, AdjList[MAX_NUM];

typedef struct
{
    AdjList vertices;       //�洢���������
    int vexnum, arcnum;     //ͼ�ĵ�ǰ�������ͻ���
}ALGraph;

//��ȡ�����ڴ洢�����е�λ��
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

//�����ڽӱ��ʾ����������ͼG(������������ֵ��ϵ��
int vvCreateUDC(ALGraph &G)
{
    int i, k;

	FILE *f;
	f = fopen("data1.txt","r");
	if (f == NULL)
    {
        cout <<"Cannot open the file!!" <<endl;
        exit(-1);
    }

	fscanf(f,"%d",&G.vexnum);
	fscanf(f,"%d",&G.arcnum);
    //cout <<G.vexnum<<" "<<G.arcnum<<endl;

    //cout << "�������ܶ��������ܱ�����   ";
    //cin >> G.vexnum >> G.arcnum;
    //cout << endl;

    //cout << "�����붥���ֵ��" << endl;
    for (i = 0; i < G.vexnum; i++)
    {
        fscanf(f,"%d",&G.vertices[i].data);
        //cin >> G.vertices[i].data;
        G.vertices[i].firstedge = NULL;         //��ʼ��ͷָ��
    }
   // cout << endl;

   // cout << "������" << G.arcnum << "���ߵĶ����ϵ:" << endl;

    for (k = 0; k < G.arcnum; k++)
    {
        VertexType v1, v2;
        int i, j;
        //cin >> v1 >> v2;
        fscanf(f,"%d",&v1);
        fscanf(f,"%d",&v2);

        i = LocateVex(G, v1);
        j = LocateVex(G, v2);

        ArcNode *p1 = new ArcNode;
        p1->adjvex = j;
        p1->next = G.vertices[i].firstedge;     //��p1�ڵ���뵽������
        G.vertices[i].firstedge = p1;

        ArcNode *p2 = new ArcNode;              //��p2�ڵ���뵽������
        p2->adjvex = i;
        p2->next = G.vertices[j].firstedge;
        G.vertices[j].firstedge = p2;
    }

    return OK;
}

//�����ڽӱ��ʾ����������ͼG(�����������������ֵ��ϵ��
int ijCreateUDC(ALGraph &G)
{
    int i, k;

    cout << "�������ܶ��������ܱ�����   ";
    cin >> G.vexnum >> G.arcnum;
    cout << endl;

    cout << "�����붥���ֵ��" << endl;
    for (i = 0; i < G.vexnum; i++)
    {
        cin >> G.vertices[i].data;
        G.vertices[i].firstedge = NULL;         //��ʼ��ͷָ��
    }
    cout << endl;

    cout << "������" << G.arcnum << "���ߵĶ��� �±� ��ϵ:" << endl;

    for (k = 0; k < G.arcnum; k++)
    {
        int i, j;
        cin >> i >> j;

        ArcNode *p1 = new ArcNode;
        p1->adjvex = j;
        p1->next = G.vertices[i].firstedge;     //��p1�ڵ���뵽������
        G.vertices[i].firstedge = p1;

        ArcNode *p2 = new ArcNode;              //��p2�ڵ���뵽������
        p2->adjvex = i;
        p2->next = G.vertices[j].firstedge;
        G.vertices[j].firstedge = p2;
    }

    return OK;
}

//����ڽӱ�
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

//������ȱ���
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
    p = G.vertices[v0].firstedge;        //p ָ�򶥵� v �ĵ�һ����
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
    cout <<"�ڽӱ�ͼΪ��\n";
    PrintfAdjList(G);
    cout << "�ؽڵ�Ϊ��\n";
    FindArticul(G);
}
