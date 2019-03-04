#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

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
//ʮ����ת���˽��� 
void Dec_OctConversion(LinkStack &S, unsigned n)	
{
	Init_Stack(S); 				//��ʼ��һ���յ���ջ 
	SElemType e;				//����һ�����ܷ���ֵ�ı���
	 
	while(n)					//��������ջ 
	{
		Push_Stack(S, n%8);		//�ѳ��� 8 ��������ջ 
		n = n / 8;				// n ���� 8 ȡ�� 
	}
	
	while( ! Empty_Stack(S))	//������ջ 
	{	
		Pop_Stack(S, e);		//�ڳ�ջ��ͬʱɾ��Ԫ�� 
		
		printf("%d", e);		//�����ջ��Ԫ�� 
	}
}

int main()
{
	unsigned n;
	LinkStack s;
	while(scanf("%d", &n) != EOF)
	{
		Dec_OctConversion(s, n);
		printf("\n");
	}
 } 
