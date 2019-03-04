#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
using namespace std;

#define MAX_VERTEX_NUM 51   	//������󶥵���
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

bool visited[MAX_VERTEX_NUM] = {0};	//��¼�ѷ��ʹ��ö���

typedef struct MGraph       	//ͼ�Ľṹ
{
    char vexs[MAX_VERTEX_NUM];       				 //����ֵ�洢����
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];        //�ڽӾ���
    int vexnum, arcnum;               		         //ͼ�ĵ�ǰ�������ͱ���
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
	QueuePtr front,rear;		//��ͷ����βָ��
};

//��ʼ������һ���յĶ���
Status Init_Queue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr) malloc (sizeof(QNode));

	if( ! Q.front)				//�жϿռ��Ƿ�����ɹ�
		exit(OVERFLOW);

	Q.front->next = NULL;		//ͷ���� next ��Ϊ��

	return OK;
}

//�ж��������Ƿ�Ϊ��
Status Empty_Queue(LinkQueue &Q)
{
	if(Q.front->next == NULL)	//���ͷ���� next ��Ϊ��
		return TRUE;
	else
		return FALSE;
}

//����Ԫ�ص���β
Status Push_Queue(LinkQueue &Q, QElemType e)
{
	QueuePtr p;								//���������½ڵ��ָ��

	p = (QueuePtr) malloc (sizeof(QNode));	//�����µĴ洢�ռ�
	if( ! p)								//�жϿռ��Ƿ�����ɹ�
		exit(OVERFLOW);

	p->data = e;							//��Ҫ�����ֵ���� p ָ��

	p->next = NULL;							//�½ڵ�ĺ��ָ���
	Q.rear->next = p;						//��βָ��ĺ��ָ���½ڵ�
	Q.rear = p;								//��βָ��ָ���½ڵ�

	return OK;
}

//ɾ����ͷԪ��
Status Pop_Queue(LinkQueue &Q, QElemType &e)
{
	QueuePtr p;					//����ָ��

	if (Q.front == Q.rear)
		return ERROR;

	p = Q.front->next;			// p ָ���һ�����
	e = p->data;				//��Ҫɾ��Ԫ�ظ��� e

	Q.front->next = p->next;	//ͷָ��ĺ��ָ�� p ����һ���ڵ�

	if (Q.rear == p)			//��ɾ�����Ƕ�β�ڵ�
		Q.rear = Q.front;		//��βָ��ָ��ͷ���

	free(p);					//�ͷ� p �ڵ�

	return OK;
}

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

//ͼ�Ĺ�����ȷǵݹ����
void BFS(MGraph &G, int v0)
{
	memset (visited, 0, sizeof(visited)) ;      //�ѱ�־������ 0

	int v, w, i;                                //v ����λ�ã� w ��������ʱ��ʱ�洢���㣬 i ������
	QElemType u;                                // u ��ӡ�����Ԫ��

	LinkQueue Q;
	Init_Queue(Q);

	printf("%d ", v0);		                	//�������ʼ����
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
				printf("%d ", w);				//����ö���
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
    BFS(G, G.vexs[0]);
    cout<<endl;
}
