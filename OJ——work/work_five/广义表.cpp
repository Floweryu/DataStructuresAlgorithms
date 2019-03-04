#include<stdio.h>
#include<stdlib.h>

#define MAX 60
#define	OVERFLOW 0
#define OK 1

typedef struct
{
	char str[MAX];
	int length;
}SString;

typedef char AtomType;
typedef int ElemType;
typedef int Status;

typedef enum{ATOM, LIST} ElemTag;		//ATOM == 0:原子，LIST == 1：子表

typedef struct GLNode
{
	ElemType tag;					//公共部分，用于区分原子节点和表节点
	union {							//原子节点和表结点的联合部分 
		
		AtomType atom;
		struct{
			struct GLNode *hp, *tp;
		}ptr;						//ptr是表结点的指针域，ptr.hp和ptr.tp分别指向表头和表尾
		 
	};
}  *GList, GLNode;					//广义表类型


//串赋值函数实现
void StrAssign(SString *S,const char str[])
{
	int i;
	for (i = 0; str[i] != '\0'; i++)
		S->str[i] = str[i];   //将常量cstr中的字符赋值给串S  
	S->length = i;
}

//串的比较操作
int StrCompare(SString S, SString T)
{   
	int i;
	for (i = 0; i<S.length&&i<T.length; i++)//比较两个串中的字符  
	{
		if (S.str[i] != T.str[i])        //如果出现字符不同，则返回两个字符的差值  
			return (S.str[i] - T.str[i]);
	}
	return (S.length - T.length); //如果比较完毕，返回两个串的长度的差值  
}

//求串的长度操作  
int StrLength(SString S)
{
	return S.length;
}

//截取子串操作  
int SubString(SString *Sub, SString S, int pos, int len)
{
	int i;
	if (pos<0 || len<0 || pos + len - 1>S.length)
	{
		return 0;
	}
	else
	{
		for (i = 0; i<len; i++)
			Sub->str[i] = S.str[i + pos - 1];
		Sub->length = len;
		return 1;
	}
}

//串的复制操作  
void StrCopy(SString *T, SString S){
	int i;
	for (i = 0; i<S.length; i++)  //将串S的字符赋值给串T  
		T->str[i] = S.str[i];
	T->length = S.length;       //将串S的长度赋值给串T  
}

//串的清空操作  
void StrClear(SString *S)
{
	S->length = 0;
}

void DistributeString(SString *Str, SString *HeadStr)
//将串Str分离成两个部分，HeadStr为第一个逗号之前的子串，Str为逗号后的子串
{
	int len, i, k;
	SString Ch, Ch1, Ch2, Ch3;
	len = StrLength(*Str);                //len为Str的长度
	StrAssign(&Ch1, ",");                //将字符','、'('和')'分别赋给Ch1,Ch2和Ch3
	StrAssign(&Ch2, "(");
	StrAssign(&Ch3, ")");
	SubString(&Ch, *Str, 1, 1);            //Ch保存Str的第一个字符
	for (i = 1, k = 0; i <= len&&StrCompare(Ch, Ch1) || k != 0; i++) //搜索Str最外层的第一个括号
	{
		SubString(&Ch, *Str, i, 1);        //取出Str的第一个字符
		if (!StrCompare(Ch, Ch2))         //如果第一个字符是'('，则令k加1
			k++;
		else if (!StrCompare(Ch, Ch3))    //如果当前字符是')'，则令k减去1
			k--;
	}
	if (i <= len)                           //串Str中存在','，它是第i-1个字符
	{
		SubString(HeadStr, *Str, 1, i - 2);  //HeadStr保存串Str','前的字符
		SubString(Str, *Str, i, len - i + 1);  //Str保存串Str','后的字符
	}
	else                                //串Str中不存在','
	{
		StrCopy(HeadStr, *Str);          //将串Str的内容复制到串HeadStr
		StrClear(Str);                  //清空串Str
	}
}

//判断串是否为空，串为空返回1，否则返回0  
int StrEmpty(SString S)
{
	if (S.length == 0)
		return 1;
	else
		return 0;
}

int GListDepth(GList L)
//求广义表的深度操作
{
	int max, depth;
	GLNode *p;
	if (!L)                          //如果广义表非空，则返回1
		return 1;
	if (L->tag == ATOM)                 //如果广义表是原子，则返回0
		return 0;
	for (max = 0, p = L; p; p = p->ptr.tp)         //逐层处理广义表
	{
		depth = GListDepth(p->ptr.hp);
		if (max<depth)
			max = depth;
	}
	return (max + 1);
}

void CopyList(GList *T, GList L)
//广义表的复制操作。由广义表L复制得到广义表T
{
	if (!L)                          //如果广义表为空，则T为空表
		*T = NULL;
	else
	{
		*T = (GList)malloc(sizeof(GLNode));   //表L不空，为T建立一个表结点


		(*T)->tag = L->tag;
		if (L->tag == ATOM)            //复制原子
			(*T)->atom = L->atom;
		else                        //递归复制子表
		{
			CopyList(&((*T)->ptr.hp), L->ptr.hp);
			CopyList(&((*T)->ptr.tp), L->ptr.tp);
		}
	}
}

void CreateList(GList *L, SString S)
//采用头尾链表创建广义表
{
	SString Sub, HeadSub, Empty;
	GList p, q;
	StrAssign(&Empty, "()");
	if (!StrCompare(S, Empty))            //如果输入的串是空串则创建一个空的广义表
		*L = NULL;
	else
	{
		if (!(*L = (GList)malloc(sizeof(GLNode))))     //为广义表生成一个结点
			exit(OVERFLOW);
		if (StrLength(S) == 1)                         //广义表是原子，则将原子的值赋值给广义表结点
		{
			(*L)->tag = ATOM;
			(*L)->atom = S.str[0];
		}
		else                                        //如果是子表
		{
			(*L)->tag = LIST;
			p = *L;
			SubString(&Sub, S, 2, StrLength(S) - 2);     //将S去除最外层的括号，然后赋值给Sub
			do
			{
				DistributeString(&Sub, &HeadSub);    //将Sub分离出表头和表尾分别赋值给HeadSub和Sub
				CreateList(&(p->ptr.hp), HeadSub);    //递归调用生成广义表
				q = p;
				if (!StrEmpty(Sub))                  //如果表尾不空，则生成结点p，并将尾指针域指向p
				{
					if (!(p = (GLNode *)malloc(sizeof(GLNode))))
						exit(OVERFLOW);
					p->tag = LIST;
					q->ptr.tp = p;
				}
			} while (!StrEmpty(Sub));
			q->ptr.tp = NULL;
		}
	}
}

int main()
{
	GList L, T;
	SString S;
	int depth;
	char str[60];
	scanf("%s", str);
	StrAssign(&S, str);
	CreateList(&L, S);
	depth = GListDepth(L);
	printf("%d\n",depth);
}
