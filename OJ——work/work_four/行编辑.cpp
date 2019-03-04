#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define STACK_INIT_SIZE 200
#define STACK_INCREMENT 10

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef char SElemType;

typedef struct SqStack
{
	SElemType *base;	//��ջ����֮ǰ��֮��base��ֵΪNULL 
	SElemType *top;		//ջ��ָ��(�������ԣ���ջ��ָ��ָ��ջ��Ԫ�ص����棬������ջ���� 
	int stacksize;		//��ǰ�ѷ���Ŀռ䣬��ʵ��Ԫ��Ϊ׼ 
 } SqStack;

//����һ����ջ 
Status InitStack(SqStack &S)
{
	S.base = (SElemType*) malloc (STACK_INIT_SIZE*sizeof(SElemType));	//����ռ� 
	if(!S.base)							//�ж�����ռ��Ƿ�ɹ� 
		exit(OVERFLOW);	
			
	S.top = S.base;						//ջ��ָ��ָ��ջ�� 
	S.stacksize = STACK_INIT_SIZE;		// �洢�ռ�Ϊ��ʼ������
	 
	return OK;
}

//���ջ
Status ClearStack(SqStack &S)
{
	S.top = S.base;		//ջ��ָ��ָ��ջ�׼�Ϊ�� 
	return OK;
} 

//����ջ
void DestroyStack(SqStack &S)
{
	free(S.base);			//�ͷ�ջ�ռ� 
	S.top = S.base = NULL;	//ջ����ջ��ָ���Ϊ�� 
	S.stacksize = 0;		//��ǰ����洢�ռ�Ϊ0 
 } 
 
 //����Ԫ��e��ջS��ջ��
Status PushStack(SqStack &S,SElemType e)
{
	if(S.top-S.base == S.stacksize)		//�����ʱ�洢�ռ��Ѿ����� 
	{
		S.base = (SElemType*)realloc(S.base,(S.stacksize+STACK_INCREMENT)&sizeof(SElemType));//׷�Ӵ洢�ռ�
		if(!S.base)						//׷�Ӵ洢�ռ�ʧ��
			return(OVERFLOW);
		S.top = S.base + S.stacksize;	//ջ��ָ��ָ���¼Ӻ��ջ�� 
		S.stacksize += STACK_INCREMENT; //ջ�洢�ռ�ı� 
	}
	
	*S.top = e;							//��e��ջ����Ϊ�µ�ջ��Ԫ�أ�ջ����ָ������һ���洢��Ԫ 
	S.top++; 							//ջ��ָ��ָ��ջ��Ԫ�ص���һ�� 
	return OK;
 } 
 
 //ɾ��S��ջ��Ԫ�أ�����e������ֵ
Status PopStack(SqStack &S,SElemType &e)
{
	if(S.top == S.base)		//�ж��Ƿ�Ϊ��ջ 
		return ERROR;
		
	S.top--;				//�Ƚ�ָ��ָ��ջ��Ԫ�� 
	e = *S.top;				//�Ƚ�ջ��Ԫ�ظ���e���ٽ�ջ��ָ���Ƶ���һ����Ԫ 
	return OK; 
} 

Status rePrintfStack(SqStack &S)
{
	SElemType *p = S.base;
	
	while(S.top > p)
	{
		printf("%c",*p);
		p++;
	}
}


void LineEdit()
{
	char ch;
	SqStack s;
	InitStack(s);

	ch = getchar();
	
	while(ch != EOF)
	{
		while(ch != EOF && ch != '\n')
		{
			switch(ch)
			{
				case '#':
					PopStack(s, ch);	break;
					
				case '@':
					ClearStack(s);		break;
					
				default:
					PushStack(s, ch);	break;
			}
			ch = getchar();
		}
		
		rePrintfStack(s);
		
		ClearStack(s);
		printf("\n");
		
		if(ch != EOF)
		{
			ch = getchar();
		}
	}
	DestroyStack(s);
 } 
 
int main()
{
	LineEdit();
}
