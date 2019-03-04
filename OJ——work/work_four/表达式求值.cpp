#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define N 1000+10

char str[N];
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

//����ջ��Ϊ�գ��ͷ���ջ��Ԫ��,����ɾ�� 
Status GetTop_Stack(LinkStack &S)
{
	if(S->next == NULL)			//�ж���ջ�Ƿ�Ϊ�� 
		return ERROR;	
	else
		return S->next->data;		//��Ϊ�գ��ͷ��ص�һ������Ԫ�� 
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

unsigned char Prior[7][7] =
{
	{'>','>','<','<','<','>','>'},
	{'>','>','<','<','<','>','>'},
	{'>','>','>','>','<','>','>'},
	{'>','>','>','>','<','>','>'},
	{'<','<','<','<','<','=',' '},
	{'<','<','<','<','<',' ','>'},
	{'<','<','<','<','<',' ','='}
};

char OPSET[7] = {'+', '-', '*', '/', '(', ')', '#' };

Status precede(int a, char b)//�ж����ȼ����� 
{
	int i = 0, j = 0;
	
	while(OPSET[i] != a)
	{
		i++;
	}

	while(OPSET[j] != b)
	{
		j++;
	}

	return Prior[i][j];
}

Status In(char c,char str[])//�ж��Ƿ�Ϊ����� 
{
	int i = 0;

	while(c != str[i])
	{
		i++;
	}

	if(i < 7)
		return OK;

	return ERROR;
}

Status Opereta(int a,int b,int c)//���㺯�� 
{
	switch(b)
	{
		case '+':	return a+c;
		case '-':	return a-c;
		case '*':	return a*c;
		case '/':	return a/c;
	} 
}

Status Atoi(char *c)//���ַ���תΪ���� 
{
	int data= 0, d = 0;
	int i = 0;
	
	while(c[i] != '\0')
	{
		data = data*10 + c[i]-'0';
		i++;
	}
	
	return data;
} 

int EvaluateExpression(char *MyExpression)//�㷨3.4 
{
	LinkStack OPTR;			//�����ջ���ַ�Ԫ�� 
	LinkStack OPND;			//������ջ��ʵ��Ԫ�� 
	char TempData[20];
	int Data, a, b;
	char *c, Dr[2];
	int theta, x;

	Init_Stack(OPTR);
	
	Push_Stack(OPTR, '#');
	
	Init_Stack(OPND);
	
	c = MyExpression;
	
	TempData[0] = '\0';
	
	while(*c != '#' || GetTop_Stack(OPTR) != '#')
	{
		if( ! In(*c, OPSET))//������������ջ 
		{
			Dr[0] = *c;
			Dr[1] = '\0';
			
			strcat(TempData, Dr);
			c++; 

			if(In(*c,OPSET))	//�������ʱ 
			{
				Data = Atoi(TempData);
				Push_Stack(OPND, Data);
				
				TempData[0] = '\0';
			}
		}
		else
		{
			switch(precede(GetTop_Stack(OPTR), *c))
			{
				case '<':
					Push_Stack(OPTR, *c);
					c++;
					break;

				case '=':
					Pop_Stack(OPTR, x);
					c++;
					break;

				case '>':
					Pop_Stack(OPND, a);
					Pop_Stack(OPND, b);
					Pop_Stack(OPTR, theta);
					Push_Stack(OPND,Opereta(b, theta, a));
					break;
			}
		}
	}
	
	return GetTop_Stack(OPND);
}

int main()
{
	while(scanf("%s", str) != EOF)
	{
		printf("%d\n",EvaluateExpression(str));
	}
	return 0;
}
