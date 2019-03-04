#include<stdio.h>
#include<string.h>

#define MAXSIZE 11		//静态链表的长度
typedef char ElemType[8];	//元素的类型，规定姓氏不超过7个字符

typedef struct{
	ElemType data;		//节点中的数据
	int cur;			//下一个节点的下标 
}NodeType;				//节点类型

NodeType space[MAXSIZE];	//用来存储节点的数组，相当于一般链表中的内存

typedef struct{
	int elem;		//静态链表存储空间基址（起始元素的下标）
	int length;		//静态链表中的元素数目
	int listsize;	//静态链表当前元素的长度，可容纳元素的数目 
}SLinkList;			//静态链表类型的定义，和一般链表类似 

//将一维数组space中各分量连成一个备用链表，space[0].cur为头指针 
void InitSpace_SL() 
{
	memset(space,0,sizeof(space));
	for(int i=0;i<MAXSIZE-1;i++)
		space[i].cur=i+1;
	space[MAXSIZE-1].cur=0;
} 

//若备用链表非空，则返回分配的节点下标（备用链表的第一个节点），否则返回0
int Malloc_SL()
{
	int i=space[0].cur;
	if(i)		//备用链表非空 
		space[0].cur=space[i].cur;/*备用链表的头结点指向原备用链表的第二个节点*/ 
 	return i; /*返回新开辟节点的坐标*/ 
} 

//创建静态链表
void CreateList_SL(SLinkList &S)
{
	S.elem=Malloc_SL();
	space[S.elem].cur=0;
	S.length=0;
	S.listsize=9;
 } 
 
//将静态链表中的所有节点显示出来
void Show_space()
{
	int i;
	for(i=0;i<MAXSIZE;i++)
	{
		printf("%-8s%2d\n",space[i].data,space[i].cur);
	}
 } 
 

//在静态单链表L中查找第一个值为e的元素
//若找到，则返回它在L中的位序，否则返回0.
int LocateElem_SL(SLinkList &S,ElemType e)
{
	int i;
	i=S.elem;	//i指示表中第一个节点 
	while(i&&strcmp(space[i].data,e))//strcmp（）函数相等返回0，大于返回1，小于返回负数 
		i=space[i].cur;	//在表中顺链查找,i等于下一个节点地址，所以不用再i++ 
	return i; 
 } 
 
//将下标为k的空闲节点回收到备用链表（成为备用链表的第一个节点）*/
void Free_SL(int k)
{
	//相当于插入节点 
	space[k].cur=space[0].cur;	//回收结点2的游标指向备用链表的第一个结点 
	space[0].cur=k;	//备用链表的头结点指向新回收的节点 
 } 
 
//往静态链表S中的第i个位置前插入e
void Insert_SL(SLinkList &S,int i,ElemType e)
{
	int cur=S.elem;		//指向静态链表的第一个结点
	int j=0;
	int newNodeIndex;	//存储新分配的节点下标
	while(j<i-1)	//寻找第i-1个节点
	{
		cur=space[cur].cur;
		j++;
	}
	newNodeIndex=Malloc_SL();
	strcpy(space[newNodeIndex].data,e);	//在新的节点中存入数据
	space[newNodeIndex].cur=0;		//指针为空
	space[newNodeIndex].cur=space[cur].cur;		//插入静态链表中
	space[cur].cur=newNodeIndex;
	S.length++;		//插入后静态链表长度加一 
}

//删除静态链表中的第i个节点
void Delete_SL(SLinkList &S,int i)
{
	int cur=S.elem;		//指向静态链表中的第一个结点
	int j=0;
	int delCur;		//存储待删除结点的下标
	while(j<i-1)	//寻找第i-1个节点
	{
		cur=space[cur].cur;	//静态链表节点移动公式 
		j++;	//计数器； 
	}
	delCur=space[cur].cur;	//找到待删除的节点的下标
	space[cur].cur=space[delCur].cur;//将待删除节点的下一个节点地址连接到i-1个节点上
	Free_SL(delCur);	//释放节点
	S.length--;		//删除后静态链表长度减一 
 } 


int main()
{
	SLinkList S;	//定义静态链表
	char str[10];	//用来获得指令
	int a;		//存储位置
	ElemType e;	//存储元素
	InitSpace_SL();	//初始化备用链表 
	CreateList_SL(S);	//创建静态链表 
	while(scanf("%s",str)!=EOF)
	{
		if(strcmp(str,"insert")==0)		//插入元素 
		{
			scanf("%d%s",&a,e);
			Insert_SL(S,a,e);
		}
		else if(strcmp(str,"delete")==0)	//删除元素
		{
			scanf("%d",&a);
			Delete_SL(S,a);
		}
		else if(strcmp(str,"search")==0) 	//搜索元素
		{
			scanf("%s",e);
			printf("%2d\n********************\n",LocateElem_SL(S,e));
		}
		else if(strcmp(str,"show")==0)		//显示静态链表
		{
			Show_space();
			puts("********************");
		 } 
	 } 
	return 0;
 } 
