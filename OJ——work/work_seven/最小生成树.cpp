#include <iostream>
using namespace std;

#define MAX_VERTEX_NUM  100
#define MAXCOST 10000
int count = 0;
typedef struct
{
    int adjvex;
    int lowcost;
} Edge;         //PRIM �㷨�еĸ�����Ϣ

typedef struct MGraph
{
    int vexs[MAX_VERTEX_NUM];       		    //����ֵ�洢����
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   //�ڽӾ���
    int vexnum, arcnum;               		    //ͼ�ĵ�ǰ�������ͱ���
}MGraph;

//��ȡ�ַ��ڴ洢�����е�λ��
int LocateVex(MGraph &G, int v)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vexs[i] == v)
        	return i;
    }
    return -1;
}


//����С��ֱ���������
int minimum(Edge closedge[], MGraph G)
{
    int i= 0, j, k, min;
    while (!closedge[i].lowcost)
    {
        i++;
    }
    min = closedge[i].lowcost;
    k = i;
    for (j = i + 1; j < G.vexnum; j++)
    {
        if (closedge[j].lowcost > 0 && closedge[j].lowcost < min)
        {
            min = closedge[j].lowcost;
            k = j;
        }
    }
    count = count + min;
    return k;
}

//����ķ�㷨������С������
void MiniSpanTree_PRIM(MGraph &G, int u)
{
    int i, j, k;
    Edge closedge[MAX_VERTEX_NUM];

    k = LocateVex(G, u);

    for (j = 0; j < G.vexnum; ++j)
    {
        if (j != k)
        {
            closedge[j].adjvex = u;
            closedge[j].lowcost = G.arcs[k][j];
        }
    }
    closedge[k].lowcost = 0;        //��ʼֵ

    for (i = 1; i < G.vexnum; i++)
    {
        k = minimum(closedge, G);

        //cout<<G.vexs[closedge[k].adjvex]<<"->"<<G.vexs[k]<<"  ";
        closedge[k].lowcost = 0;        //�� k �����㲢��U��

        for(j = 1; j < G.vexnum; j++)
        {
            if (G.arcs[k][j] < closedge[j].lowcost)     //����ѡȡ��С��
            {
                closedge[j].adjvex = G.vexs[k];
                closedge[j].lowcost = G.arcs[k][j];
            }
        }
    }
}

//�����ڽӾ���������ͼ
void CreateUDG(MGraph &G)
{
    int i, j, k;		        //������
    int v1, v2;		        //����ֵ

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
		    if(G.arcs[i][j] == 0)
                G.arcs[i][j] = MAXCOST;
		}
	}

}




int main()
{
    MGraph G;
    CreateUDG(G);
    MiniSpanTree_PRIM(G, G.vexs[0]);
    cout<<count;
}

















