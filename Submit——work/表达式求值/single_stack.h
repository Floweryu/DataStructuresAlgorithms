#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<conio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef char SElemType;			//����ջ�е��������� 

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

//��ջ����������
Status Create_Stack(LinkStack &S, int n)
{
	LinkStack q;									// q ָ�����������µĽڵ� 
	int i;											//������ 
	
	for(i = 0; i < n; i++)							//��ջ��λ�����β���Ԫ�� 
	{
		q = (LinkStack) malloc (sizeof (SqStack));	//����ռ� 
		if(q == NULL)								//�жϿռ��Ƿ�����ɹ� 
			exit(OVERFLOW);	
			
		scanf("%d", &q->data);						//���¿ռ����������� 
		
		q->next = S->next;							// q �ĺ��ָ��ͷ��� S �ĺ�� 
		S->next = q;								//ͷ��� S �ĺ��ָ�� q  
	}
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

//������ջ
Status Destroy_Stack(LinkStack &S)
{
	LinkStack p,q;		//���� p q ָ�� 
	
	p = S->next;		// p ָ���һ���ڵ� 
	while(p != NULL)	//�� p ��ָ��յ�ʱ��ѭ�� 
	{
		q = p->next;	// q ָ�� p ����һ���ڵ� 
		free(p);		//�ͷ� p �ڵ� 
		p = q;			// p ����ָ�� q �ڵ� 
	}
	
	free(S);			//�ٰ�ͷ����ͷ� 
	
	return OK;
} 

//������ջԪ�صĸ���
Status Length_Stack(LinkStack &S)
{
	LinkStack p;		//����һ��ָ���������� 
	int len =  0;		//����һ�����α�����������������ͳ��ջ�ĳ��� ,��ʼֵΪ 0 . 
	
	p = S->next;		// p ָ��ָ���һ�����
	while(p != NULL)	//�� p ��δ�� NULL ��ʱ����� 
	{
		len++; 			//��������һ 
		p = p->next; 	// p ָ����һ���ڵ� 
	} 
	
	return len;			//���ؼ�������ֵ������ջ�ĳ��� 
} 

//����ջ��Ϊ�գ��ͷ���ջ��Ԫ��,����ɾ�� 
Status GetTop_Stack(LinkStack &S, SElemType &e)
{
	if(S->next == NULL)			//�ж���ջ�Ƿ�Ϊ�� 
		return ERROR;	
	else
		e = S->next->data;		//��Ϊ�գ��ͷ��ص�һ������Ԫ�� 
		
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

//�����ջ���ȫ��Ԫ��
Status Printf_Stack(LinkStack &S)
{
	if(S->next == NULL)			//�ж���ջ�Ƿ�Ϊ�� 
		return ERROR;
		 
	LinkStack p;
	p = S->next;				// p ָ��ջ���ڵ� 
	
	while(p != NULL)			//�� p û��ָ��յ�ʱ��ѭ�� 
	{
		printf("%d ",p->data);	//��� p ��ָ��Ԫ�� 
		p = p->next;			//�ƶ� p ָ�� 
	}	
} 
