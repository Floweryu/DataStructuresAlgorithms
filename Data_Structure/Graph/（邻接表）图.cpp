/**
* Author : ZhangJunFeng
* Date : 2018-11-27-15.24.41
* Function: ���ڽӱ�ʵ�ֵ�ͼ����������Ⱥ͹�����ȱ���������
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

typedef char VertexType;         //��������
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

//������ȱ���
void DFS(ALGraph G, int v)
{
    ArcNode *p;
    if (v < 0 || v >= G.vexnum)
        return;
    else
    {
        cout << G.vertices[v].data << " ";
        visited[v] = true;

        p = G.vertices[v].firstedge;        //p ָ�򶥵� v �ĵ�һ����
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

//������ȱ���
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

int main()
{
    ALGraph G;

    ijCreateUDC(G);
    PrintfAdjList(G);
    cout << "�����������������\n";
    DFS(G, 0);
    cout << endl;
    cout << "����������ر�����\n";
    BFS(G, 0);
}
