/**
* Author : ZhangJunFeng
* Date : 2018-12-06-20.13.42
* Function: ʵ������ͼ����ͨ������������
* Description : �ڽӾ���ʵ��ͼ������Ҫ���OJ����seven.
* Algorithm description :   1������ͼ�����������ɭ�ֵ��������ֵ�����
                            2����ÿ��������ʼ��������ȱ���ͼ���Դ˶���Ϊ����������
* The test data :
6
0 0 0 1 0 0
0 0 1 1 0 0
0 1 0 1 0 0
1 1 1 0 0 0
0 0 0 0 0 1
0 0 0 0 1 0
*/
#include <iostream>

using namespace std;

typedef int TElemType;
#define MAX_VERTEX_NUM 100   	//������󶥵���
#define MAX_NUM 100
#define MAXCOST 10000

typedef struct CSNode
{
	TElemType data;
	CSNode *firstchild, *nextsibling;
}CSNode, *CSTree;

//�ڽӾ���
typedef struct MGraph
{
    int vexs[MAX_VERTEX_NUM];       		    //����ֵ�洢����
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   //�ڽӾ���
    int vexnum, arcnum;               		    //ͼ�ĵ�ǰ�������ͱ���
}MGraph;


bool visited[MAX_NUM];

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

//����ͼ��ĳλ�õĶ���ֵ
int  GetVex(MGraph G, int v)
{
    return G.vexs[v];
}

//������v��صĵ�һ���ڽӶ�������
int FirstAdjVex(MGraph G, int v)
{
    int j, t;
    t = MAXCOST;
    for (j = 0; j < G.vexnum; j++)
    {
        if (G.arcs[v][j] != t)
            return j;
    }
    return -1;
}

//������v��ص���һ���ڽӶ�������
int NextAdjVex(MGraph G, int v, int w)
{
    int j, t;
    t = MAXCOST;
    for (j = w + 1; j < G.vexnum; j++)
    {
        if (G.arcs[v][j] != MAXCOST)
            return j;
    }
    return -1;
}

//��ȱ���ͼ����������
void DFSTree(MGraph G, int v, CSTree &T)
{

    cout<<G.vexs[v]<<" ";
    int w;
    CSTree p, q;
    bool first = true;
    visited[v] = true;      //v�����ʹ�

    for (w = FirstAdjVex(G, v); w != -1; w = NextAdjVex(G, v, w))
    {
        if (! visited[w])
        {
            p = new CSNode;
            p->data = GetVex(G, w);
            p->firstchild = NULL;
            p->nextsibling = NULL;

            if (first)                      //w��v�ĵ�һ��δ�����ʵ��ڽӵ�
            {
                T->firstchild = p;          //�������ӽڵ�
                first = false;
            }
            else                            //w��v������δ�����ʵ��ڽӵ�
            {
                q->nextsibling = p;         //��һ���ڽӶ�������ֵܽڵ�
            }
            q = p;

            DFSTree(G, w, q);               //��w����������ȱ���ͼ����������q
        }  //if
    }   //DFSTree
}

//����ͼ�����������ɭ�ֵ��������ֵ�����
void DFSForest(MGraph G, CSTree &T)
{
    int v, j = 0;
    CSTree p, q;
    T = NULL;

    for (v = 0; v < G.vexnum; ++v)  //��ʼ��
    {
        visited[v] = false;
    }

    for (v = 0; v < G.vexnum; ++v)
    {
        if ( ! visited[v])           //v Ϊ�µ����������ڵ�
        {
            p = new CSNode;
            p->data = GetVex(G, v);
            p->firstchild = NULL;
            p->nextsibling = NULL;

            if (! T)                  //��һ���������ĸ�
            {
                T = p;
            }
            else
            {
                q->nextsibling = p;    //ǰһ���������ĸ����ֵ�
            }
            q = p;                    //ָ��ǰ

            DFSTree(G, v, p);
            cout<<endl;
        }   //if
    } //for
}   //DFSForest


//�����ڽӾ���������ͼ
void CreateUDG(MGraph &G)
{
    int i, j, k;		         //������
    int v1, v2;		             //����ֵ

    cout<<"���붥�����:    ";
    cin>>G.vexnum;
    for (i = 0; i < G.vexnum; i++)
    {
    	G.vexs[i] = i;
	}

	cout<<"�����ڽӾ���"<<endl;
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
    CSTree T;
    cout<<"���ɵ�����Ϊ��"<<endl;
    DFSForest(G, T);

}
