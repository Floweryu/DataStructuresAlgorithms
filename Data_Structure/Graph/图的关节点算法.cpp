/**
* Author : ZhangJunFeng
* Date : 2018-12-04-21.05.13
* Function: ͼ�Ĺؽڵ��㷨
* Description :   ����Ϊ�ڽӱ�������Ϊ�ڽӾ��󣬿��Ը���OJ����ת��Ϊ�ڽӱ�������ַ�� 0 ��ʼ��
* Algorithm description :       1�����������ĸ������Ż��������ϵ���������˸������Ϊ�ؽڵ㡣
                                2������������ĳ����Ҷ�Ӷ���v����ĳ�������ĸ������������������ û�� ָ��v�����ȵĻرߣ���vΪ�ؽڵ㡣
                                3���ж�ĳ�������low[]ֵ��
                                ���ö��㵽�����Ƚڵ��лرߣ��� low[] = min{  visited(�Լ�������㡢���Ƚڵ�)��low(����)  };
                                ���ö��㵽�����Ƚڵ�û�лرߣ���low[] = min{ visited(�Լ��������)��          low(����)    };
                                4��Ҫ֪���ڽӱ�ı�����ʽ��

  ����������data.txt�С�
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

typedef char VertexType;         //��������
typedef int InfoType;            //���ϵ�Ȩֵ����

//ͼ���ڽӱ�洢�ṹ
typedef struct ArcNode
{
    int adjvex;                  //�洢�����Ӧ���±�
    InfoType weight;             //�洢Ȩֵ�����ڷ���ͼ����Ҫ
    struct ArcNode *next;        //ָ����һ���ڽӵ�
} ArcNode;

typedef struct VNode
{
    VertexType data;              //�洢������Ϣ
    ArcNode *firstedge;           //�߱�ͷָ��

} VNode, AdjList[MAX_NUM];

typedef struct
{
    AdjList vertices;           //�洢���������
    int vexnum, arcnum;          //ͼ�ĵ�ǰ�������ͻ���
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

    cout << "������" << G.arcnum << "���ߵĶ����ϵ:" << endl;

    for (k = 0; k < G.arcnum; k++)
    {
        VertexType v1, v2;
        int i, j;
        cin >> v1 >> v2;

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
void DFSArticul(ALGraph G, int v0)      //v0�Ǳ�������ʼ����
{
    ArcNode *p;
    int w, minn;
    visited[v0] = minn = ++countt;      //min ���ڸ���㡢�Լ������Ƚڵ��visited[]ֵ

    for (p = G.vertices[v0].firstedge; p; p = p->next)
    {
        w = p->adjvex;
        if (visited[w] == 0)
        {
            DFSArticul(G, w);
            if (low[w] < minn)
                minn = low[w];
            if (low[w] >= visited[v0])
                cout << v0 << " " <<G.vertices[v0].data << endl;        //����ؽڵ�
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
    countt = 1;         //��ʼֵΪ1
    visited[0] = 1;
    low[0] = 1;

    for (i = 1; i < G.vexnum; i++)
        visited[i] = 0;

    ArcNode *p;
    p = G.vertices[0].firstedge;
    v = p->adjvex;

    DFSArticul(G, v);
    if (countt < G.vexnum)      //���ڵ㵥���ж�
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
    PrintfAdjList(G);
    cout << "�ؽڵ�Ϊ��\n";
    FindArticul(G);
}
