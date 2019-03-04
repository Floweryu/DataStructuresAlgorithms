/**
* Author : ZhangJunFeng
* Date : 2018-12-06-15.24.20
* Function: �Ͻ�˹�����㷨�����·��
* Description : �����ڽӾ���Ĵ洢��ʽ������������OJҪ��
* Algorithm description :   1���㷨��������κζ��㵽�����������·����
                            2����һ��v������ѡ��һ����v���������·���ıߡ��޸���һ�οɴ�����·���ĳ��ȡ�
* The test data :  out: 6 4 7
4 1
0 3 0 1
0 0 4 0
2 0 0 0
0 0 1 0
*/
#include <iostream>
using namespace std;

#define MAX_VERTEX_NUM  100
#define MAXCOST 65535

typedef struct MGraph
{
    int vexs[MAX_VERTEX_NUM];       		    //����ֵ�洢����
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   //�ڽӾ���
    int vexnum, arcnum;               		    //ͼ�ĵ�ǰ�������ͱ���
}MGraph;

typedef bool PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];    //��P[v][w]Ϊtrue����w��v0��v��ǰ��õ����·���Ķ��㡣
typedef int ShortPathTable[MAX_VERTEX_NUM];                 //D[]��ʾ����ʼ��v0���յ�v�����·���ĳ��ȡ�
int start;      //��ʼ����

//Dijkstra �㷨�����·��
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &P, ShortPathTable &D)   //v0����ʼ��
{
    int v, w, i, j;
    int min;
    bool final[MAX_VERTEX_NUM];             //final[v]Ϊtrue���������v0��v�����·����

    for (v = 0; v < G.vexnum; v++)
    {
        final[v] = false;                   //��ʼ��
        D[v] = G.arcs[v0][v];               //v0��v���·���ĳ���

        for (w = 0; w < G.vexnum; w++)
        {
            P[v][w] = false;                //��ʼ��û��·��
        }
        if (D[v] < MAXCOST)                 //��v0 ��v ��·��
        {
            P[v][v0] = P[v][v] = true;      //v0��v��  v0��v��ǰ������·������
        }
    }   //for

    D[v0] = 0;               //v0��v0���·��Ϊ0
    final[v0] = true;        //v0�ѱ�������·��

    for (i = 1; i < G.vexnum; i++)          //��ȥv0�����������
    {
        min = MAXCOST;                      //��ʼ��

        //��v0����������·����̵�һ�����㣬��ֵ��v
        for (w = 0; w < G.vexnum; w++)
        {
            if (! final[w] && D[w] < min)   //w���㻹û�����ʣ���w������v0�������
            {
                v = w;                      //��¼w����
                min = D[w];                 //��¼w��v0�����·��
            }
        }
        final[v] = true;                    //v�����ʣ���w�����ѱ����ʣ�

        for (w = 0; w < G.vexnum; w++)      //���µ�ǰ���·��������
        {
            //��ʱv��ʾ����w����wΪ��ǰ�����Ķ��㡣
            if (! final[w] && (min + G.arcs[v][w] < D[w]))  //����w����δ�����ʣ��Ƚ�·��(v0,v,w)��·��(v0,w)
            {
                D[w] = min + G.arcs[v][w];                  //����v0��w�����·��

                for (j = 0; j < G.vexnum; j++)              //��v�и�ֵ�ڵ�w��
                {
                    P[w][j] = P[v][j];
                }
                P[w][w] = true;                  //��ʱwΪv0��w�����·���Ķ��㡣
            }   // if
        } // for
    }  // for

}


//�����ڽӾ���������ͼ
void CreateUDG(MGraph &G)
{
    int i, j, k;		        //������
    int v1, v2;		        //����ֵ
    cout<<"���붥������   ";
    cin>>G.vexnum;
    cout<<"������ʼ��:    ";
    cin>>start;
    for (i = 0; i < G.vexnum; i++)
    {
    	G.vexs[i] = i;
	}
    cout<<"�����ڽӾ���:   "<<endl;
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
		{
		    cin>>G.arcs[i][j];
		    if(G.arcs[i][j] == 0)
                G.arcs[i][j] = MAXCOST;
		}
	}

}

int main()
{
    MGraph G;
    PathMatrix p;
    ShortPathTable d;
    CreateUDG(G);
    ShortestPath_DIJ(G, start, p, d);
    int i;
    cout<<"����ʼ�㵽�յ�����·��Ϊ��"<<endl;
    for (i = 0; i < G.vexnum; i++)
    {
        if (i == start)
            continue;
        if (d[i] == 0)
            cout<<"-1 ";
        if (d[i] != 0)
            cout<<d[i]<<" ";
    }
}
