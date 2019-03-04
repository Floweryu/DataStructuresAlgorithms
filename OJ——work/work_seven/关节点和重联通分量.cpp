#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <algorithm>

using namespace std;

#define MAX_VERTEX_NUM 100   	//������󶥵���

typedef struct MGraph       	//ͼ�Ľṹ
{
    char vexs[MAX_VERTEX_NUM];       				 //����ֵ�洢����
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];        //�ڽӾ���
    int vex, arc;               		         //ͼ�ĵ�ǰ�������ͱ���
}MGraph;


#define MAX_NUM 100
#define OK 1
#define ERROR 0

int visited[MAX_NUM];
int low[MAX_NUM], countt;
int num[MAX_NUM];
int num_countt = 0;


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


//�����ڽӾ���������ͼ
void CreateUDG(MGraph &M)
{
    int i, j;		        //������
    int count = 0;
    cin>>M.vex;     //������Ŀ

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
        G.vertices[i].firstedge = NULL;         //��ʼ��ͷָ��
    }

    for (i = 0; i < G.vexnum; i++)
    {
        for (j = G.vexnum - 1; j >= 0; j--)     //��β����ʼ����
        {
            if (M.arcs[i][j])
            {
                ArcNode *p1 = new ArcNode;
                p1->adjvex = j;
                p1->next = G.vertices[i].firstedge;     //��p1�ڵ���뵽������
                G.vertices[i].firstedge = p1;
            }
        }
    }

    return OK;
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
    sort(num, num + num_countt);        //�������������
    num_countt = unique(num, num + num_countt) - num;       //ɾ���������ظ�������

    cout<<num_countt<<endl;
    for (i = 0; i < num_countt; i++)
        cout<<num[i]<<" ";
    cout<<endl;
}
