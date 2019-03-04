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

typedef struct MGraph       //图的邻接矩阵存储结构
{
    int vexs[MAX_VERTEX_NUM];       		    //顶点值存储数组
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   //权值
    int vexnum, arcnum;               		    //图的当前顶点数和边数
}MGraph;

typedef int Status;
typedef int SElemType;			//定义栈中的数据类型

typedef struct SqStack
{
	SElemType data;				//数据域
	struct SqStack *next;		//指针域
}SqStack,*LinkStack;

//初始化链栈
/* 建立一个空栈，创建链栈的头结点，将其NULL置空	*/
Status Init_Stack(LinkStack &S)
{
	S = (LinkStack)malloc(sizeof(SqStack));		//申请头结点空间

	if(S == NULL)								//判断新空间是否分配成功
		exit(OVERFLOW);

	S->next = NULL;								//头结点后继指向空

	return OK;
}

//判断链栈是否为空
Status Empty_Stack(LinkStack &S)
{
	if(S->next == NULL)	//如果头结点的后继指向NULL，即为空 返回真
		return OK;
	else
		return FALSE; 	//否则，不为空
}

//在栈顶插入元素
Status Push_Stack(LinkStack &S,SElemType e)
{
	LinkStack p;			//定义一个指针，用来指向要插入元素

	p = (LinkStack) malloc (sizeof(SqStack));	//为指针 p 申请存储空间
	if(p ==  NULL)			//判断空间是否申请成功
		exit(OVERFLOW);

	p->data = e;			// 把要插入的值赋给p的数据域
	p->next = S->next;		// p 的后继指向头结点的后继
	S->next = p;			// p 的前驱指向头结点的后继

	return OK;				//插入成功，返回真
}

//删除栈顶元素，并用 e 返回其值
Status  Pop_Stack(LinkStack &S, SElemType &e)
{
	if(S->next == NULL)		//判断链栈是否为空栈
		return ERROR;

	LinkStack p;

	p = S->next;			// p 指向栈顶元素
	S->next = p->next;		//头结点 S 的后继指向栈顶元素的下一个元素

	e = p->data;			//把栈顶存储的值赋给 e 返回

	free(p);				//释放栈顶节点

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


//拓扑排序
void TopologicalSort(MGraph G)
{
    LinkStack S;
    int count, i, j;

    int indegree[MAX_VERTEX_NUM];

    FindInDegree(G, indegree);

    Init_Stack(S);

    for (i = 1; i <= G.vexnum; ++i)
    {
        if (! indegree[i])          //入度为 0 的进栈
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

//获取字符在存储数组中的位置
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
    while (cin>>G.vexnum>>G.arcnum, G.vexnum!=0 || G.arcnum!=0)     //当输入为0 0 或 0 1时没有输出，1 0有输出，不能用&&
    {
        int i, j, k;		        //计数器
        int v1, v2;		            //顶点值
        for (i = 1; i <= G.vexnum; i++)
        {
            G.vexs[i] = i;
        }

        for (i = 1; i <= G.vexnum; i++)      //把邻接矩阵数组置为0
        {
            for (j = 1; j <= G.vexnum; j++)
            {
                G.arcs[i][j] = 0;
            }
        }

        for (k = 1; k <= G.arcnum; k++)
        {
            cin>>v1>>v2;

            i = LocateVex(G, v1);			//寻找顶点值在存储数组中的位置
            j = LocateVex(G, v2);

            G.arcs[i][j] = 1; 				//构建邻接矩阵，有关系的赋值为1
        }
        TopologicalSort(G);
    }
    return 0;
}
