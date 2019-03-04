/**
* Author : ZhangJunFeng
* Date : 2018-12-06-16.52.52
* Function: FLOYD���·��
* Description : ����ͼ���ڽӾ�������Զ���֮������·����
* Algorithm description :   �ڽӾ�������ΪȨֵ���Ѹ��Զ���֮������·�����µ��ڽӾ����Ӧλ�á�
* The test data :
input:
4
0 3 0 1
0 0 4 0
2 0 0 0
0 0 1 0
output:
0 3 2 1
6 0 4 7
2 5 0 3
3 6 1 0
*/

#include <iostream>
using namespace std;

#define MAX_VERTEX_NUM  100
#define MAXCOST 65535

typedef struct MGraph
{
    int vexs[MAX_VERTEX_NUM];
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcsnum;
}MGraph;

typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];         //�洢·������
typedef int DistancMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];      //����Ȩֵ

void ShortesPath_FLOYD(MGraph G, PathMatrix &P, DistancMatrix &D)
{
    int u, v, w;
    for (v = 0; v < G.vexnum; v++)
    {
        for (w = 0; w < G.vexnum; w++)
        {
            D[v][w] = G.arcs[v][w];
            P[v][w] = w;
        }
    }

    for (u = 0; u < G.vexnum; u++)      //u ����ת��
    {
        for (v = 0; v < G.vexnum; v++)
        {
            for (w = 0; w < G.vexnum; w++)
            {
                if (D[v][w] > D[v][u] + D[u][w])
                {
                    D[v][w] = D[v][u] + D[u][w];
                    P[v][w] = P[v][u];
                }
            }
        }
    }
}

//�����ڽӾ���������ͼ
void CreateUDG(MGraph &G)
{
    int i, j, k;
    int v1, v2;
    cout<<"���붥������  ";
    cin>>G.vexnum;
    for (i = 0; i < G.vexnum; i++)
    {
    	G.vexs[i] = i;
	}

	cout<<"�����ڽӾ���:  "<<endl;
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
		{
		    cin>>G.arcs[i][j];
            if(G.arcs[i][j] == 0)
                G.arcs[i][j] = MAXCOST;     //Ϊ0 �ĳ�ʼֵҪ��Ϊ���
		}
	}

}

void PrintfDD(MGraph &G, DistancMatrix &D)
{
    int i, j;
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
        {
            if (i == j)     //�Խ������Ϊ0
                cout<<"0 ";
            else
                cout<<D[i][j]<<" ";
        }
        cout<<endl;
    }
}

void PrintfPP(MGraph &G, PathMatrix &P)
{
    int i, j;
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
        {
            cout<<P[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main()
{
    MGraph G;
    PathMatrix p;
    DistancMatrix d;
    CreateUDG(G);
    cout<<endl;
    ShortesPath_FLOYD(G, p, d);
    cout<<"���·������Ϊ��"<<endl;
    PrintfDD(G, d);
    cout<<endl;
    cout<<"·���������Ϊ��"<<endl;
    PrintfPP(G, p);

}
