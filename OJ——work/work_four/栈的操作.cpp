#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

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

//�����ջ
Status Clear_Stack(LinkStack &S)
{

	LinkStack p,q;				//���� p q ָ�� 
	
	p = S->next;				// p ָ���һ���ڵ� 
	while(p != NULL)			//�� p ��ָ��յ�ʱ��ѭ�� 
	{
		q = p->next;			// q ָ�� p ����һ���ڵ� 
		free(p);				//�ͷ� p �ڵ� 
		p = q;					// p ����ָ�� q �ڵ� 
	}
	
	S->next = NULL;				//�ڵ��ͷ������ջͷ���ָ��NULL���ص���ʼ��״̬ 
	
	return OK;
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

int main()
{
	LinkStack S;
	Init_Stack(S);
	char str[1000];
	SElemType E;
	int back, j, len;
	
	while(scanf("%s",str) != EOF)
	{
		int i = 1;
		len = strlen(str);

		for (j = 0; j < len; j++)
		{
			if(str[j] == 'P')
			{
				Push_Stack(S, i);
				i++;
			}
			else if(str[j] == 'Q')
			{
				back = Pop_Stack(S, E);
				if(back)
					printf("%d ",E);
				else
				{
					printf("error");
					break;
				}
			}
		}
		printf("\n");
		Clear_Stack(S);
	}
}

