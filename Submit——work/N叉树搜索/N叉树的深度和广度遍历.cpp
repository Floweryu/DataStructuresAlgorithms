/*
	Name: N叉树深度优先和广度优先递归遍历算法 
	Author: 张俊峰 
	Date: 17/11/18 16:25
	Description: 
*/

#include "link_queue_n.h"
#include <string.h> 

//构造树 
void CreateTree(CSTree &T)
{
	char c[20];				//临时存放孩子的节点
	CSTree p, pl;
	LinkQueue q;
	int i, m;
	
	Init_Queue(q);			//初始化队列q
	printf("请输入根节点（字符型，#为空）：");
	scanf("%c%*c",  &c[0]);
	if (c[0] != '#')
	{
		T = (CSTree) malloc (sizeof(CSNode));		//建立根节点
		T->data = c[0];								//给根节点赋值
		T->nextsibling = NULL;						//根节点没有下一个兄弟
		Insert_Queue(q, T);							//入队根节点的指针
		
		while ( ! Empty_Queue(q))
		{
			Delete_Queue(q, p);						//出队第一个结点的指针
			printf("请按长幼顺序输入节点 %c 的所有孩子：", p->data);	
			gets(c);								//将所有节点输入
			m = strlen(c);							//计算节点个数
			if (m > 0)
			{
				pl = p->firstchild = (CSTree) malloc (sizeof(CSNode));		//建立长子节点
				pl->data = c[0];
				Insert_Queue(q, pl);
				
				for (i = 1; i < m; i++)
				{
					pl->nextsibling = (CSTree) malloc (sizeof(CSNode));		//建立下一个兄弟节点
					pl = pl->nextsibling;									//pl 指向下一个兄弟节点
					pl->data = c[i];										//给 pl 节点赋值
					Insert_Queue(q, pl);									//入队 pl 所指的指针
		 
				}
				pl->nextsibling = NULL; 
			}
			else
				p->firstchild = NULL; 
		} 
		
	} 
	else
		T = NULL;		//空树 
}

//后根遍历 孩子-兄弟 二叉链表结构的树
void PostOrderTraverse(CSTree T)
{
	CSTree p;
	
	if (T == NULL)
		return;
		
	if (T->firstchild)
	{
		PostOrderTraverse(T->firstchild);
		p = T->firstchild->nextsibling;			// p 指向长子的下一个兄弟
		while (p)
		{
			PostOrderTraverse(p);				//后根遍历下一个兄弟子树 
			p = p->nextsibling;					// p 指向下下一个兄弟 
		} 
	}
	printf("%c ", T->data);
} 

//先根遍历 孩子-兄弟二叉链表结构
void PreOrderTraverse(CSTree T)
{
	if (T == NULL)
	 	return;
		
	printf("%c ", T->data);						//先访问根节点 
	PreOrderTraverse(T->firstchild);			//再先根遍历长子数 
	PreOrderTraverse(T->nextsibling);			//最后先根遍历下一个兄弟子树 
} 

//层序遍历 孩子-兄弟链表结构的树
void LeveOrderTraverse(CSTree T)
{
	CSTree p;
	LinkQueue q;
	Init_Queue(q);
	
	if (T == NULL)
		return;
		
	printf("%c ", T->data);
	Insert_Queue(q, T);
	
	while ( ! Empty_Queue(q))
	{
		Delete_Queue(q, p);
		
		if (p->firstchild)
		{
			p = p->firstchild;				// p 指向长子节点
			printf("%c ", p->data);			//访问长子节点
			Insert_Queue(q, p);				//入队长子节点的指针
			while(p->nextsibling)
			{
				p = p->nextsibling;			// p 指向下一个兄弟节点
				printf("%c ", p->data);		//访问下一个兄弟
				Insert_Queue(q, p);			//入队兄弟节点的指针 
			} 
		}
	}
	printf("\n"); 
} 

int main()
{
	printf("*****************************************************************\n");
	printf("*****   构造树                                 enter   'a' ******\n");
	printf("*****   先根遍历 孩子-兄弟 二叉链表结构，      enter   'b' ******\n");
	printf("*****   后根遍历 孩子-兄弟 二叉链表结构        enter   'c' ******\n");
	printf("*****   层序遍历 孩子-兄弟 链表结构的树，      enter   'd' ******\n");
	printf("*****************************************************************\n");
	
	CSTree T;
	char str;			//接收从键盘输入的符号 
	do
	{
		printf("\n");
		printf("Please enter a char:    ");
		str=getche();		/*从键盘获取一个字符并显示，不按回车直接执行*/ 
		printf("\n");
		switch(str)
		{
			case 'a':
				{
					CreateTree(T);
					break;
				}
			case 'b':
				{
					printf("先根遍历 孩子-兄弟 二叉链表结构:\n");
					PreOrderTraverse(T);
					break;
				}
			case 'c':
				{
					printf("后根遍历 孩子-兄弟 二叉链表结构：\n");
					PostOrderTraverse(T);
					break;
				}
			case 'd':
				{
					printf("层序遍历 孩子-兄弟 链表结构的树：\n");
					LeveOrderTraverse(T);
					break;
				}
			default: printf("Wrong!!!\n");	
		} 
	} while (str != 'q');
}
