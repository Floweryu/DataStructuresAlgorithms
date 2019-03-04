#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<conio.h>

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int SElemType;

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
 
//�ж�ջ�Ƿ�Ϊ��
//��ջ����1�����򷵻�0 
Status EmptyStack(SqStack &S)
{
	if(S.top == S.base)		//�п�������ջ��ָ���Ƿ�ָ��ջ�� 
		return TRUE;
	else
		return FALSE;
} 

//����ջԪ�صĸ���
Status LengthStack(SqStack &S)
{
	return S.top-S.base;	//ջ��ָ���ȥջ��ָ�루���Կ���ջ��ָ��ָ��գ���0�� 
}

//��ջ��Ϊ�գ�����ջ��Ԫ�أ�������OK�����򣬷���FALSE
Status GetTopStack(SqStack &S,SElemType &e)
{
	if(S.top == S.base)	//�ж�ջ�Ƿ�Ϊ�� 
		return ERROR;
	else
	{
		S.top--;		//ָ��ջ��Ԫ�� 
		e = *(S.top);	//��ֵ���ظ�e 
		S.top++;
		return OK;
	}
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
 
//��ջ����������
Status CreateStack(SqStack &S,int n)
{
	int m, i;
	for(i = 0; i < n; i++)
	{
		scanf("%d",&m);		//�������� 
		PushStack(S, m);	//�����ݲ��뵽ջ���� 
	}
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

//����ջ�����
Status PrintfStack(SqStack &S)
{
	if(S.base == S.top)		//�ж��Ƿ�Ϊ��ջ 
		return ERROR;
	while(S.top != S.base)	//��ջ��ָ��δָ��ջ��ʱ 
	{
		S.top--;			//ջ��ָ��ָ��ջ��Ԫ�� 
		printf("%d ",*S.top);
	}
	return OK;
 } 
 
//��ջ�׵�ջ�����Ԫ�أ��൱��������� 
Status rePrintfStack(SqStack &S)
{
	SElemType *p = S.base;	//���� p ָ��ָ��ջ�� 
		
	while(S.top > p)		//�� p ָ��δָ��ջ��ʱ 
	{
		printf("%d ",*p);	//���Ԫ��ֵ 
		p++;				//ָ���һ�����ƶ� 
	}
	printf("\n");
}
int main()
{
	printf("****** ����һ����ջ��enter               'a'    ******\n");
	printf("****** ����ջ��enter                     'b'    ******\n");
	printf("****** ����ջ�ĳ��ȣ�enter               'c'    ******\n");
	printf("****** �ж�ջ�Ƿ�Ϊ�գ�enter             'd'    ******\n");
	printf("****** ����ջ��Ԫ�أ�enter               'e'    ******\n");
	printf("****** ��ջ������һ��Ԫ�أ�enter         'f'    ******\n");
	printf("****** ɾ��ջ��Ԫ�أ�enter               'g'    ******\n");
	printf("****** ��ջ���������ݣ�enter             'h'    ******\n");
	printf("****** ���ջ������ݣ�enter             'i'    ******\n");
	printf("****** ���ջ��enter                     'j'    ******\n");
	printf("****** ��ջ�׵�ջ�����Ԫ�أ� enter      'k'    ******\n"); 
	SqStack S;
	int back;	//���ڿ���ǿյ��ж�
	int k;	//���ڽ��ܷ���ֵ
	SElemType E,N; 
	char str;
	do
	{
		printf("\n");
		printf("Please enter a char:    ");
		str=getche();/*�Ӽ��̻�ȡһ���ַ�����ʾ�������س�ֱ��ִ��*/ 
		printf("\n");/*	getchar();	/*�����������Ļس���������س���Ҳ�ᱻ��Ϊ���ַ�*/
		switch(str)
		{
			case 'a':{
						back=InitStack(S);
						if(back)
						printf("��Ϊ��������һ����ջ\n");
						else
						printf("ERROR\n");
				break;
			}
			case 'b':{
						DestroyStack(S);
				break;
			}
			case 'c':{
						k=LengthStack(S);
						printf("ջ�ĳ���Ϊ��   %d\n",k);
				break;
			}
			case 'd':{
						back=EmptyStack(S);
						if(back)
							printf("����һ����ջ��\n");
						else
							printf("�ⲻ��һ����ջ��\n");
				break;
			}
			case 'e':{
						back=GetTopStack(S,E);
						if(back)
							printf("ջ��Ԫ���ǣ�   %d\n",E);
						else
							printf("����һ����ջ\n");
				break;
			}
			case 'f':{
						printf("�����뽫Ҫ��ջ�������Ԫ�أ�   ");
						scanf("%d",&E);
						back=PushStack(S,E);
						if(back)
							printf("����ɹ�\n");
						else
							printf("����ʧ��\n");
				break;
			}
			case 'g':{
						back=PopStack(S,E);
						if(back)
						{
							printf("ɾ���ɹ���ɾ��Ԫ��Ϊ:    %d\n",E);
						}
						else
							printf("ɾ��ʧ��\n");
				break;
			}
			case 'h':{
						printf("���������ݵĸ�����  ");
						scanf("%d",&N);
						CreateStack(S,N);
				break;
			}
			case 'i':{
						PrintfStack(S);
				break;
			}
			case 'j':{
						back = ClearStack(S);
						if(back)
							printf("���ջ�ɹ�����\n");
				break;
			}
			case 'k':{
				rePrintfStack(S);
				break;
			}
			default:printf("wrong!\n");
		 } 

	}while(str!='q');
	return 0;
}
 
