/**
* Author : ZhangJunFeng
* Date : 2018-11-24-12.10.57
* Function: 无向图的建立和深度遍历与广度遍历
* Description : 采用邻接矩阵构造无向图，深度遍历采用了递归，广度遍历借用了数组
*/
#include "link_queue.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX_VERTEX_NUM 26   	//定义最大顶点数

bool visited[MAX_VERTEX_NUM] = {0};	//记录已访问过得顶点

typedef struct MGraph       	//图的结构
{
    char vexs[MAX_VERTEX_NUM];       				 //顶点值存储数组
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];        //邻接矩阵
    int vexnum, arcnum;               		         //图的当前顶点数和边数
}MGraph;

//获取字符在存储数组中的位置
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

//采用邻接矩阵构造无向图
void CreateUDG(MGraph &G)
{
    int i, j, k;		        //计数器
    char v1, v2;		        //顶点值

    printf("请输入无向图G的顶点数，边数：  ");
    scanf("%d %d", &G.vexnum, &G.arcnum);

    getchar();                  //消去回车键

    printf("请输入%d个顶点的值:\n", G.vexnum);
    for (i = 0; i < G.vexnum; i++)
    {
    	scanf ("%c", &G.vexs[i]);
	}

	for (i = 0; i < G.vexnum; i++)      //把邻接矩阵数组置为0
	{
		for (j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = 0;
		}
	}

	printf("请输入%d条边的顶点1，顶点2：\n", G.arcnum);
	for (k = 0; k < G.arcnum; k++)
	{
		getchar();                      //消去回车符
		scanf ("%c %c", &v1, &v2);

		i = LocateVex(G, v1);			//寻找顶点值在存储数组中的位置
		j = LocateVex(G, v2);

		G.arcs[i][j] = 1; 				//构建邻接矩阵，有关系的赋值为1
		G.arcs[j][i] = G.arcs[i][j];	//无向图，两个单元信息相同
	}
}

//图的深度优先递归遍历
void DFS(MGraph &G, int v)
{
	int w;

	printf("%c ", G.vexs[v]);                   //输出顶点
	visited[v] = 1;                             //输出过得顶点标志位置一

	for (w = 0; w < G.vexnum; w++)              //对存储数组遍历
	{
		if (G.arcs[v][w] && visited[w] == 0)    //如果遍历的顶点与已经输出的顶点有关系（即邻接矩阵为1）
			DFS(G, w);                          //递归输出
	}
}

//图的广度优先非递归遍历
void BFS(MGraph &G, char v0)
{
	memset (visited, 0, sizeof(visited)) ;      //把标志数组置 0

	int v, w, i;                                //v 返回位置， w 遍历数组时临时存储顶点， i 计数器
	QElemType u;                                // u 入队、出队元素

	LinkQueue Q;
	Init_Queue(Q);

	printf("%c ", v0);		                	//先输出起始顶点
	v = LocateVex(G, v0);	                	//找到在存储数组中的位置
	visited[v] = 1;			                	//标志位置一

	Push_Queue(Q, v0);			                //将起始节点入队

	while ( ! Empty_Queue(Q))	                //当队列不为空时
	{
		Pop_Queue(Q, u);		                //队头出队赋值给 u
		v = LocateVex(G, u);	                //找到 u 顶点在存储数组中的位置
		for ( i = 0; i < G.vexnum; i++)	        //遍历存储数组
		{
			w = G.vexs[i];						//将顶点值赋给 w

			if (G.arcs[v][i] && ! visited[i])	//如果该顶点与队头元素的邻接矩阵值为一（说明有关系）并且该顶点没有被访问
			{
				printf("%c ", w);				//输出该顶点
				Push_Queue(Q, w);				//把这个顶点入队
				visited[i] = 1;					//此输出顶点标志位置一
			}
		}
	}

}


int main()
{
	MGraph G;
	CreateUDG(G);
	printf("深度优先遍历：   ");
	DFS(G, 0);
	printf("\n");
	printf("广度优先遍历：   ");
	BFS(G, G.vexs[0]);
}
