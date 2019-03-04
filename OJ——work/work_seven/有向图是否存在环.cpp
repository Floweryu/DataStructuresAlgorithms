#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

using namespace std;

#define MAX_VERTEX_NUM  101
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef struct MGraph       //ͼ���ڽӾ���洢�ṹ
{
    int vexs[MAX_VERTEX_NUM];       		    //����ֵ�洢����
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   //Ȩֵ
    int vexnum, arcnum;               		    //ͼ�ĵ�ǰ�������ͱ���
}MGraph;

typedef int Status;
typedef int SElemType;			//����ջ�е���������

typedef struct SqStack
{
	SElemType data;				//������
	struct SqStack *next;		//ָ����
}SqStack,*LinkStack;

//��ʼ����ջ
/* ����һ����ջ��������ջ��ͷ��㣬����NULL�ÿ�	*/
Status Init_Stack(LinkStack &S)
{
	S = (LinkStack)malloc(sizeof(SqStack));		//����ͷ���ռ�

	if(S == NULL)								//�ж��¿ռ��Ƿ����ɹ�
		exit(OVERFLOW);

	S->next = NULL;								//ͷ�����ָ���

	return OK;
}

//�ж���ջ�Ƿ�Ϊ��
Status Empty_Stack(LinkStack &S)
{
	if(S->next == NULL)	//���ͷ���ĺ��ָ��NULL����Ϊ�� ������
		return OK;
	else
		return FALSE; 	//���򣬲�Ϊ��
}

//��ջ������Ԫ��
Status Push_Stack(LinkStack &S,SElemType e)
{
	LinkStack p;			//����һ��ָ�룬����ָ��Ҫ����Ԫ��

	p = (LinkStack) malloc (sizeof(SqStack));	//Ϊָ�� p ����洢�ռ�
	if(p ==  NULL)			//�жϿռ��Ƿ�����ɹ�
		exit(OVERFLOW);

	p->data = e;			// ��Ҫ�����ֵ����p��������
	p->next = S->next;		// p �ĺ��ָ��ͷ���ĺ��
	S->next = p;			// p ��ǰ��ָ��ͷ���ĺ��

	return OK;				//����ɹ���������
}

//ɾ��ջ��Ԫ�أ����� e ������ֵ
Status  Pop_Stack(LinkStack &S, SElemType &e)
{
	if(S->next == NULL)		//�ж���ջ�Ƿ�Ϊ��ջ
		return ERROR;

	LinkStack p;

	p = S->next;			// p ָ��ջ��Ԫ��
	S->next = p->next;		//ͷ��� S �ĺ��ָ��ջ��Ԫ�ص���һ��Ԫ��

	e = p->data;			//��ջ���洢��ֵ���� e ����

	free(p);				//�ͷ�ջ���ڵ�

	return OK;
}


void FindInDegree(MGraph G, int indegree[])
{
    int i, j;
    for (i = 1; i <= G.vexnum; ++i)
    {
        indegree[i] = 0;
    }

    for (i = 1; i <= G.vexnum; i++)
    {
        for (j = 1; j <= G.vexnum; j++)
        {
            if (G.arcs[i][j])
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
    int count, i, j;

    int indegree[MAX_VERTEX_NUM];

    FindInDegree(G, indegree);

    Init_Stack(S);

    for (i = 1; i <= G.vexnum; ++i)
    {
        if (! indegree[i])          //���Ϊ 0 �Ľ�ջ
            Push_Stack(S, i);
    }

    count = 0;

    while (! Empty_Stack(S))
    {
        Pop_Stack(S, i);
        count++;
        for (j = 1; j <= G.vexnum; ++j)
        {
            if (G.arcs[i][j])
            {
                if (! (--indegree[j]))
                    Push_Stack(S, j);
            }
        }
    }

    if (count != G.vexnum)
    {
        cout<<"YES"<<endl;
    }
    else
    {
        cout<<"NO"<<endl;
    }

}

//��ȡ�ַ��ڴ洢�����е�λ��
int LocateVex(MGraph &G, int v)
{
    int i;
    for (i = 1; i <= G.vexnum; i++)
    {
        if (G.vexs[i] == v)
        	return i;
    }
    return -1;
}

int main()
{
    MGraph G;
    while (cin>>G.vexnum>>G.arcnum, G.vexnum!=0 || G.arcnum!=0)     //������Ϊ0 0 �� 0 1ʱû�������1 0�������������&&
    {
        int i, j, k;		        //������
        int v1, v2;		            //����ֵ
        for (i = 1; i <= G.vexnum; i++)
        {
            G.vexs[i] = i;
        }

        for (i = 1; i <= G.vexnum; i++)      //���ڽӾ���������Ϊ0
        {
            for (j = 1; j <= G.vexnum; j++)
            {
                G.arcs[i][j] = 0;
            }
        }

        for (k = 1; k <= G.arcnum; k++)
        {
            cin>>v1>>v2;

            i = LocateVex(G, v1);			//Ѱ�Ҷ���ֵ�ڴ洢�����е�λ��
            j = LocateVex(G, v2);

            G.arcs[i][j] = 1; 				//�����ڽӾ����й�ϵ�ĸ�ֵΪ1
        }
        TopologicalSort(G);
    }
    return 0;
}
