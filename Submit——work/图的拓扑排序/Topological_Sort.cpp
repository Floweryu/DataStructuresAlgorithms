/**
* Author : ZhangJunFeng
* Date : 2018-12-03-20.33.25
* Function: ��������
* Description :     ʹ���ڽӾ�������ʾͼ��������ջ��ʵ��
*/
#include "single_stack.h"
#include <iostream>
using namespace std;


#define MAX_VERTEX_NUM  100
typedef struct MGraph       //ͼ���ڽӾ���洢�ṹ
{
    int vexs[MAX_VERTEX_NUM];       		    //����ֵ�洢����
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   //Ȩֵ
    int vexnum, arcnum;               		    //ͼ�ĵ�ǰ�������ͱ���
}MGraph;


void FindInDegree(MGraph G, int indegree[])     //����ÿ����������
{
    int i, j;
    for (i = 0; i < G.vexnum; ++i)              //��ʼ��
    {
        indegree[i] = 0;
    }

    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
        {
            if (G.arcs[i][j])           //��i���㵽j���������
            {
                indegree[j]++;
            }
        }
    }
}


//��������
void TopologicalSort(MGraph G)
{
    LinkStack S;
    int count, k = 0, i, j;
    int num[MAX_VERTEX_NUM];            //��¼�洢�������
    int indegree[MAX_VERTEX_NUM];

    FindInDegree(G, indegree);

    Init_Stack(S);

    for (i = 0; i < G.vexnum; ++i)
    {
        if (! indegree[i])          //���Ϊ 0 �Ľ�ջ����ʱ���ն����±��˳��
            Push_Stack(S, i);
    }

    count = 0;          //ͳ������������

    while (! Empty_Stack(S))
    {
        Pop_Stack(S, i);
        num[k] = G.vexs[i];
        k++;
        count++;

        for (j = 0; j < G.vexnum; ++j)
        {
            if (G.arcs[i][j])
            {
                if (! (--indegree[j]))      //��ȼ�һ�����Ϊ 0 ����ջ
                    Push_Stack(S, j);
            }
        }
    }

    if (count < G.vexnum)
    {
        cout<<"����һ���л�ͼ����"<<endl;
    }
    else
    {
        cout<<"��������Ϊ��   ";
        for (i = 0; i < G.vexnum; i++)
            cout<<num[i]<<" ";
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
		}
	}

}

int main()
{
    MGraph G;
    CreateUDG(G);
    TopologicalSort(G);
}
