#include<stdio.h>
#include<stdlib.h>

#define ERROR -1
#define OK 0

typedef int Status;
typedef int ElemType;

typedef struct OLNode
{
	int i, j;						//����Ԫ���к��е��±�
	ElemType e;						//����Ԫ�ص�ֵ
	struct OLNode *right, *down;	//����Ԫ�����к��еĺ���� 
}OLNode, *OLink;

typedef struct
{
	OLink *rhead, *chead;			//�к�������ͷָ��������ַ
	int mu, nu, tu;					//ϵ������������������ͷ���Ԫ���� 
}CrossList;

//ʮ��������ϡ�����
Status Create_Matrix(CrossList &M)
{
/*	if(M)
		free(M);
		*/
	int m, n, t = 0;
	OLNode *p, *q;
	int i, j, e;
	
	scanf("%d %d", &m, &n);	//����M������������
	
	M.mu = m;
	M.nu = n;
	
	if(! (M.rhead = (OLink *)malloc((m + 1) * sizeof(OLink)))) 
		return ERROR;
	if(! (M.chead = (OLink *)malloc((n + 1) * sizeof(OLink))))
		return ERROR;
	
	int a, b, c;
	for (b = 1; b <= n; b++)
	{
		M.chead[b] = NULL;
	}
	for (a = 1; a <= m; a++)
	{
		M.rhead[a] = NULL;
	}
	
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= n; j++)
		{
			scanf("%d", &e);
			if(e != 0)
			{
				t++;
				if(! (p = (OLNode *)malloc(sizeof(OLNode))))
					return ERROR;
		
				p->i = i;
				p->j = j;
				p->e = e;
				p->down = NULL;
				p->right = NULL;		//�½ڵ�
		
				if(M.rhead[i] == NULL || M.rhead[i]->j > j)
				{
					p->right = M.rhead[i];
					M.rhead[i] = p;
				}
				else
				{
					for (q = M.rhead[i]; (q->right) && (q->right->j <j); q = q->right);
						p->right = q->right;
						q->right = p;
				}
		
				if(M.chead[j] == NULL || M.chead[j]->i > i)
				{
					p->down = M.chead[j];
					M.chead[j] = p;
				}
				else
				{
					for (q = M.chead[j]; (q->down) && q->down->i < i; q = q->down);
						p->down = q->down;
					q->down = p;
				}
			}
		}
	}
	M.tu = t;
	return OK;
} 

void Printf_Matrix(CrossList M)
{
	int p, q;
	OLNode *temp;
	
	for (p = 1; p <= M.mu; p++)
	{
		temp = M.rhead[p];
		for (q = 1; q <= M.nu; q++)
		{
			if(temp != NULL && temp->j == q)
			{
				printf("%d ",temp->e);
				temp = temp->right;
			}
			else
				printf("0 ");
		}
		printf("\n");
	}
	
}

int main()
{
	CrossList M;
	Create_Matrix(M);
	Printf_Matrix(M);
}
