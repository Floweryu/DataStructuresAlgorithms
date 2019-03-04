/*	��ѭ��˳����в��ö�βָ��ָ��յķ�����ʵ��	*/ 
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
typedef int QElemType;

#define MAX_SIZE 5			//ѭ�����д洢���ֵ + 1 
 
typedef struct SqQueue
{
	QElemType	*base;		//��ʼ����̬����洢�ռ� 
	int front;				//ͷָ�룬�����в�Ϊ�գ�ָ�����ͷԪ�� 
	int rear;				//βָ�룬�����в�Ϊ�գ�ָ��βԪ�ص���һ��λ�� 
}SqQueue;

//����һ���ն��� 
Status InitQueue(SqQueue &Q)
{
	Q.base = (QElemType*) malloc (MAX_SIZE*sizeof(QElemType));	//����ڵ�Ĵ洢�ռ�
	if( ! Q.base)			//�洢�ռ����ʧ��
		exit(OVERFLOW);
		
	Q.front = Q.rear = 0;	//��ͷָ��Ͷ�βָ�붼ָ��� 
	
	return OK;
}

//�ж϶����Ƿ�Ϊ��
Status EmptyQueue(SqQueue &Q)
{
	if(Q.front == Q.rear)					//��ͷָ����ڶ�βָ�� 
		return TRUE;	
	else
		return FALSE;
} 

//�ж϶����Ƿ�����
Status FullQueue(SqQueue &Q)
{
	if((Q.rear+1) % MAX_SIZE == Q.front)	//�ж϶�βָ���һȡģ�Ƿ����ͷָ�� 
		return TRUE;
	else
		return FALSE;
} 
 
//���������
Status ClearQueue(SqQueue &Q)
{
	Q.front = Q.rear = 0;	//��ͷָ����ڶ�βָ�뼴Ϊ�� 
	
	return OK;
} 

//���ٶ���
Status DestroyQueue(SqQueue &Q)
{
	if(Q.base)				//������д���
		free(Q.base);		//�ͷ� Q.base ��ָ�Ŀռ�
		
	Q.base = NULL;			// Q.base ָ��� 
	Q.front = Q.rear = 0; 	//ָ�붼ָ��� 
	
	return OK; 
} 

//����е�ʵ�ʳ���
int LengthQueue(SqQueue &Q)
{
	return (Q.rear - Q.front + MAX_SIZE) % MAX_SIZE;	//��Ϊȡģ������Ҫ���� MAX_SIZE 
} 

//���ض�ͷԪ��
Status GetHeadQueue(SqQueue &Q, QElemType &e)
{
	if(Q.front == Q.rear)	//������Ϊ�� 
		return ERROR;
		
	e = Q.base[Q.front];	//���ض�ͷԪ�� 
	
	return OK;
} 

//����Ԫ�ص���β
Status InsertQueue(SqQueue &Q, QElemType e)
{
	if((Q.rear+1) % MAX_SIZE == Q.front)	//������
		return ERROR;
		
	Q.base[Q.rear] = e;						//�� e ���ڶ�β
	Q.rear = (Q.rear+1) % MAX_SIZE;			//����βָ������һ 
	
	return OK; 
}

//ɾ����ͷԪ��
Status DeleteQueue(SqQueue &Q, QElemType &e)
{
	if(Q.front == Q.rear)					//�ж϶����Ƿ�Ϊ�� 
		return ERROR;
	
	e = Q.base[Q.front];					//��Ҫɾ����Ԫ�ظ�ֵ�� e ���� 
	Q.front = (Q.front + 1)%MAX_SIZE;		//�ƶ���ͷָ�룬��ͷָ������� 
	
	return OK; 
} 

//���������������
Status CreateQueue(SqQueue &Q, int n)
{
	int i = Q.rear;							// i ���ڶ�βָ�� 
	
	while(i < n)							//�� i С�� n ��ʱ��ѭ�� 
	{
		scanf("%d",&Q.base[i]);				//�������� 
		i = (i + 1) % MAX_SIZE;				// i ��ֵ��һ��ȡģ 
	} 
	Q.rear = i;
	 
	return OK; 
}

//��������е�����
Status PrintfQueue(SqQueue &Q)
{
	int i = Q.front;						// i ���ڶ�ͷָ�� 
	
	while(i != Q.rear)						//�� i �����ڶ�βָ��ʱѭ�� 
	{
		printf("%d ", Q.base[i]);			//���Ԫ�� 
		i = (i + 1) % MAX_SIZE;				// i ��ֵ��һ��ȡģ 
	}
	printf("\n");
	
	return OK;
} 
 
 
int main()
{
	printf("******************�밴��ʾ���в���************************\n");
	printf("***** ��ʼ������,                       enter    'a' *****\n");
	printf("***** ��������������ݣ�                enter    'b' *****\n");
	printf("***** �ж϶����Ƿ�Ϊ�գ�                enter    'c' *****\n");
	printf("***** �ж϶����Ƿ�������                enter    'd' *****\n");
	printf("***** ��ն��У�                        enter    'e' *****\n");
	printf("***** ���ٶ��� ��                       enter    'f' *****\n");
	printf("***** ���ض���Ԫ�صĸ�����              enter    'g' *****\n");
	printf("***** ���ض�ͷԪ��,����ɾ����           enter    'h' *****\n");
	printf("***** �ڶ�β����Ԫ�أ�                  enter    'i' *****\n");
	printf("***** ɾ����ͷԪ�أ����÷�����ֵ��      enter    'j' *****\n");
	printf("***** ����������ȫ��Ԫ�أ�            enter    'k' *****\n");
	printf("**********************************************************\n");
	
	SqQueue Q;		//���������
	int N, back;	// N ��������ݳ��� ��back ���ܷ��� bool ֵ 
	QElemType E;	//����ֵ �� ���ܷ���ֵ
	char str; 		//�Ӽ��̽����ַ�
	
	do
	{
		printf("\n");
		printf("Please enter a char:    ");
		str=getche();		/*�Ӽ��̻�ȡһ���ַ�����ʾ�������س�ֱ��ִ��*/ 
		printf("\n");
		switch(str)
		{
			case 'a'://��ʼ��������
			{
				back = InitQueue(Q);
				if(back)
					printf("��Ϊ����ʼ�����һ���������С�\n");
				else 
					printf("��ʼ��ʧ�ܣ���\n");	
				break;
			}
			case 'b':// ������������������
			{
				printf("���������ݵĸ�����  ");
				scanf("%d",&N);
				if(N < MAX_SIZE)
					CreateQueue(Q, N);
				else
					printf("���ݸ��������Ѷ�����������������\n");
				break;
			}
			case 'c'://�ж϶����Ƿ�Ϊ��
			{
				back = EmptyQueue(Q);
				if(back)
					printf("This is an empty stack. \n");
				else
					printf("This is not an empty stack.  \n");
				break;
			}
			case 'd'://�ж϶����Ƿ�����
			{
				back = FullQueue(Q);
				if(back)
					printf("The queue is FULL.\n");
				else
					printf("The queue is unFULL. \n");
				break;
			} 
			case 'e'://��ն���
			{
				back = ClearQueue(Q);
				if(back)
					printf("�������ѱ���գ�����\n");
				else
					printf("�˶������ǿյģ�����Ҫ��գ�����\n");
				break;
			}
			case 'f'://���ٶ���
			{
				back = DestroyQueue(Q);
				if(back)
					printf("�������ѱ����٣�����\n");
				else
					printf("����ʧ�ܣ�����\n");
				break;
			}
			case 'g'://���ض���Ԫ�صĸ���
			{
				back = LengthQueue(Q);
				printf("�����еĳ����� :     %d\n",back);
				break;
			}
			case 'h'://���ض�ͷԪ��,����ɾ��
			{
				GetHeadQueue(Q, E);
				printf("��ͷԪ��Ϊ :   %d\n",E);
				break;
			}
			case 'i'://�ڶ�β����Ԫ��
			{
				printf("������Ҫ����Ԫ�ص�ֵ��    ");
				scanf("%d",&E);
				back = InsertQueue(Q,E);
				if(back)
				{
					printf("�����ջ��Ԫ��ֵ��Ϊ��  ");
					PrintfQueue(Q);
					printf("\n");
				}
				else
					printf("����Ԫ��ʧ�ܣ�����\n");
				break;
			}
			case 'j'://ɾ����ͷԪ�أ����� e ������ֵ
			{
				back=DeleteQueue(Q,E);
				if(back)
					printf("ɾ���Ķ�ͷԪ���ǣ�   %d\n",E);
				else
					printf("����Ϊ�գ�û��Ԫ�أ�����\n");
				break;
			}
			case 'k'://����������ȫ��Ԫ��
			{
				PrintfQueue(Q);
				break;
			} 
			default:printf("wrong!\n");
		}	//end switch
	}while(str != 'q');
	return 0;
}
	
