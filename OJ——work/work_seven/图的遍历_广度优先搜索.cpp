#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
using namespace std;

#define MAX_VERTEX_NUM 51   	//定义最大顶点数
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

bool visited[MAX_VERTEX_NUM] = {0};	//记录已访问过得顶点

typedef struct MGraph       	//图的结构
{
    char vexs[MAX_VERTEX_NUM];       				 //顶点值存储数组
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];        //邻接矩阵
    int vexnum, arcnum;               		         //图的当前顶点数和边数
}MGraph;

typedef int Status;
typedef int QElemType;

typedef struct QNode
{
	QElemType	data;
	QNode 		*next;
}*QueuePtr;

struct LinkQueue
{
	QueuePtr front,rear;		//队头，队尾指针
};

//初始化定义一个空的队列
Status Init_Queue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr) malloc (sizeof(QNode));

	if( ! Q.front)				//判断空间是否申请成功
		exit(OVERFLOW);

	Q.front->next = NULL;		//头结点的 next 域为空

	return OK;
}

//判断链队列是否为空
Status Empty_Queue(LinkQueue &Q)
{
	if(Q.front->next == NULL)	//如果头结点的 next 域为空
		return TRUE;
	else
		return FALSE;
}

//插入元素到队尾
Status Push_Queue(LinkQueue &Q, QElemType e)
{
	QueuePtr p;								//定义申请新节点的指针

	p = (QueuePtr) malloc (sizeof(QNode));	//申请新的存储空间
	if( ! p)								//判断空间是否申请成功
		exit(OVERFLOW);

	p->data = e;							//将要插入的值赋给 p 指针

	p->next = NULL;							//新节点的后继指向空
	Q.rear->next = p;						//队尾指针的后继指向新节点
	Q.rear = p;								//队尾指针指向新节点

	return OK;
}

//删除队头元素
Status Pop_Queue(LinkQueue &Q, QElemType &e)
{
	QueuePtr p;					//定义指针

	if (Q.front == Q.rear)
		return ERROR;

	p = Q.front->next;			// p 指向第一个结点
	e = p->data;				//将要删除元素赋给 e

	Q.front->next = p->next;	//头指针的后继指向 p 的下一个节点

	if (Q.rear == p)			//若删除的是队尾节点
		Q.rear = Q.front;		//队尾指针指向头结点

	free(p);					//释放 p 节点

	return OK;
}

//获取字符在存储数组中的位置
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


//采用邻接矩阵构造无向图
void CreateUDG(MGraph &G)
{
    int i, j, k;		        //计数器
    int v1, v2;		        //顶点值

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

//图的广度优先非递归遍历
void BFS(MGraph &G, int v0)
{
	memset (visited, 0, sizeof(visited)) ;      //把标志数组置 0

	int v, w, i;                                //v 返回位置， w 遍历数组时临时存储顶点， i 计数器
	QElemType u;                                // u 入队、出队元素

	LinkQueue Q;
	Init_Queue(Q);

	printf("%d ", v0);		                	//先输出起始顶点
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
				printf("%d ", w);				//输出该顶点
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
    BFS(G, G.vexs[0]);
    cout<<endl;
}
