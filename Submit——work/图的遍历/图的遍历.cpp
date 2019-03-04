/**
* Author : ZhangJunFeng
* Date : 2018-11-24-12.10.57
* Function: ����ͼ�Ľ�������ȱ������ȱ���
* Description : �����ڽӾ���������ͼ����ȱ��������˵ݹ飬��ȱ�������������
*/
#include "link_queue.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX_VERTEX_NUM 26   	//������󶥵���

bool visited[MAX_VERTEX_NUM] = {0};	//��¼�ѷ��ʹ��ö���

typedef struct MGraph       	//ͼ�Ľṹ
{
    char vexs[MAX_VERTEX_NUM];       				 //����ֵ�洢����
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];        //�ڽӾ���
    int vexnum, arcnum;               		         //ͼ�ĵ�ǰ�������ͱ���
}MGraph;

//��ȡ�ַ��ڴ洢�����е�λ��
int LocateVex(MGraph &G, char v)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vexs[i] == v)
        	return i;
    }
    return -1;
}

//�����ڽӾ���������ͼ
void CreateUDG(MGraph &G)
{
    int i, j, k;		        //������
    char v1, v2;		        //����ֵ

    printf("����������ͼG�Ķ�������������  ");
    scanf("%d %d", &G.vexnum, &G.arcnum);

    getchar();                  //��ȥ�س���

    printf("������%d�������ֵ:\n", G.vexnum);
    for (i = 0; i < G.vexnum; i++)
    {
    	scanf ("%c", &G.vexs[i]);
	}

	for (i = 0; i < G.vexnum; i++)      //���ڽӾ���������Ϊ0
	{
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = 0;
		}
	}

	printf("������%d���ߵĶ���1������2��\n", G.arcnum);
	for (k = 0; k < G.arcnum; k++)
	{
		getchar();                      //��ȥ�س���
		scanf ("%c %c", &v1, &v2);

		i = LocateVex(G, v1);			//Ѱ�Ҷ���ֵ�ڴ洢�����е�λ��
		j = LocateVex(G, v2);

		G.arcs[i][j] = 1; 				//�����ڽӾ����й�ϵ�ĸ�ֵΪ1
		G.arcs[j][i] = G.arcs[i][j];	//����ͼ��������Ԫ��Ϣ��ͬ
	}
}

//ͼ��������ȵݹ����
void DFS(MGraph &G, int v)
{
	int w;

	printf("%c ", G.vexs[v]);                   //�������
	visited[v] = 1;                             //������ö����־λ��һ

	for (w = 0; w < G.vexnum; w++)              //�Դ洢�������
	{
		if (G.arcs[v][w] && visited[w] == 0)    //��������Ķ������Ѿ�����Ķ����й�ϵ�����ڽӾ���Ϊ1��
			DFS(G, w);                          //�ݹ����
	}
}

//ͼ�Ĺ�����ȷǵݹ����
void BFS(MGraph &G, char v0)
{
	memset (visited, 0, sizeof(visited)) ;      //�ѱ�־������ 0

	int v, w, i;                                //v ����λ�ã� w ��������ʱ��ʱ�洢���㣬 i ������
	QElemType u;                                // u ��ӡ�����Ԫ��

	LinkQueue Q;
	Init_Queue(Q);

	printf("%c ", v0);		                	//�������ʼ����
	v = LocateVex(G, v0);	                	//�ҵ��ڴ洢�����е�λ��
	visited[v] = 1;			                	//��־λ��һ

	Push_Queue(Q, v0);			                //����ʼ�ڵ����

	while ( ! Empty_Queue(Q))	                //�����в�Ϊ��ʱ
	{
		Pop_Queue(Q, u);		                //��ͷ���Ӹ�ֵ�� u
		v = LocateVex(G, u);	                //�ҵ� u �����ڴ洢�����е�λ��
		for ( i = 0; i < G.vexnum; i++)	        //�����洢����
		{
			w = G.vexs[i];						//������ֵ���� w

			if (G.arcs[v][i] && ! visited[i])	//����ö������ͷԪ�ص��ڽӾ���ֵΪһ��˵���й�ϵ�����Ҹö���û�б�����
			{
				printf("%c ", w);				//����ö���
				Push_Queue(Q, w);				//������������
				visited[i] = 1;					//����������־λ��һ
			}
		}
	}

}


int main()
{
	MGraph G;
	CreateUDG(G);
	printf("������ȱ�����   ");
	DFS(G, 0);
	printf("\n");
	printf("������ȱ�����   ");
	BFS(G, G.vexs[0]);
}
