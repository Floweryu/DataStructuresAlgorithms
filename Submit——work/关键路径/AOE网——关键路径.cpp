/**
* Author : ZhangJunFeng
* Date : 2018-12-06-19.49.54
* Function: ʵ��ͼ�Ĺؼ�·��
* Description :
* Algorithm description :
* The test data :
*/

#include "single_stack.h"
#include <iostream>
#include <stack>
using namespace std;

#define MAX_VERTEX_NUM  100
#define ERROR 0
#define OK 1
int ve[MAX_VERTEX_NUM];
int vl[MAX_VERTEX_NUM];
LinkStack T;

typedef struct MGraph                           //ͼ���ڽӾ���洢�ṹ
{
    int vexs[MAX_VERTEX_NUM];
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
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
            if (G.arcs[i][j])                   //��i���㵽j���������
            {
                indegree[j]++;                  //�ö����������һ
            }
        }
    }
}

//��������
int TopologicalOrder(MGraph G)
{
    LinkStack S;
    int count, i, j;             //k ��num[]�������
    int indegree[MAX_VERTEX_NUM];

    FindInDegree(G, indegree);

    Init_Stack(S);
    Init_Stack(T);

    for (i = 0; i < G.vexnum; ++i)
    {
        if (! indegree[i])              //���Ϊ 0 �Ľ�ջ����ʱ���ն����±��˳��
            Push_Stack(S, i);
    }

    for (i = 0; i < G.vexnum; i++)
    {
        ve[i] = 0;
    }

    count = 0;                          //ͳ������������

    while (! Empty_Stack(S))
    {
        Pop_Stack(S, i);                //���ջ��Ԫ��
        Push_Stack(T, i);               //�洢�����Ԫ��

        count++;

        for (j = 0; j < G.vexnum; ++j)  //���ڶ����������һ�����������Ϊ 0 ����ջ
        {
            if (G.arcs[i][j])
            {
                if (! (--indegree[j]))    //��ȼ�һ�����Ϊ 0 ����ջ
                    Push_Stack(S, j);

                if (ve[i] + G.arcs[i][j] > ve[j])
                {
                    ve[j] = ve[i] + G.arcs[i][j];
                }
            }
        }   //  for
    }   //  while


    if (count != G.vexnum)
        return ERROR;       //�л�
    else
    {
        cout<<"��������:    :";
        Printf_Stack(T);
        cout<<endl;         //������Ӿ�����������
    }

}


void CriticalPath(MGraph &G)
{
    if (! TopologicalOrder(G))
        cout<<"����һ���л�ͼ����"<<endl;

    int i, j;
    int v, dut, ee, el;
    for (i = 0; i < G.vexnum; i++)
    {
        vl[i] = ve[G.vexnum - 1];
    }

    while (! Empty_Stack(T))
    {
        Pop_Stack(T, v);

        for (j = 0; j < G.vexnum; j++)
        {
            if (G.arcs[v][j])
            {
                dut = G.arcs[v][j];
                if (vl[j] - dut < vl[v])
                    vl[v] = vl[j] - dut;
            }
        }
    }

    cout<<"ve����    :";
    for (j = 0; j < G.vexnum; j++)
    {
        cout<<ve[j]<<" ";
    }
    cout<<endl;

    cout<<"vl����    :";
    for (j = 0; j < G.vexnum; j++)
    {
        cout<<vl[j]<<" ";
    }
    cout<<endl;

    cout<<"j->k->Ȩֵ->ee->el"<<endl;
    for (j = 0; j < G.vexnum; j++)
    {
        for (i = 0; i < G.vexnum; i++)
        {
            if (G.arcs[j][i])
            {
                dut = G.arcs[j][i];
                ee = ve[j];
                el = vl[i] - dut;
                if (ee == el)
                    cout<<j<<"->"<<i<<"->"<<dut<<"->"<<ee<<"->"<<el<<endl;
            }
        }
    }

}

//�����ڽӾ���������ͼ
void CreateUDG(MGraph &G)
{
    int i, j, k;		        //������
    int v1, v2;		            //����ֵ

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
    MGraph M;
    CreateUDG(M);

    CriticalPath(M);
}








