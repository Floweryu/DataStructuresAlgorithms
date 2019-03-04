#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
using namespace std;

#define MAX_VERTEX_NUM 26   	//������󶥵���

bool visited[MAX_VERTEX_NUM] = {0};	//��¼�ѷ��ʹ��ö���

typedef struct MGraph       	//ͼ�Ľṹ
{
    char vexs[MAX_VERTEX_NUM];       				 //����ֵ�洢����
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];        //�ڽӾ���
    int vexnum, arcnum;               		         //ͼ�ĵ�ǰ�������ͱ���
}MGraph;

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
			//G.arcs[i][j] = 0;
		}
	}

}

//ͼ��������ȵݹ����
void DFS(MGraph &G, int v)
{
	int w;

	printf("%d ", G.vexs[v]);                   //�������
	visited[v] = 1;                             //������ö����־λ��һ

	for (w = 0; w < G.vexnum; w++)              //�Դ洢�������
	{
		if (G.arcs[v][w] && visited[w] == 0)    //��������Ķ������Ѿ�����Ķ����й�ϵ�����ڽӾ���Ϊ1��
			DFS(G, w);                          //�ݹ����
	}
}

int main()
{
    MGraph G;
    CreateUDG(G);
    DFS(G, 0);
    cout<<endl;

}
