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

typedef struct QNode
{
	QElemType	data;
	QNode 		*next;
}*QueuePtr;

struct LinkQueue
{
	QueuePtr front,rear;		//��ͷ����βָ�� 
};

//��ʼ������һ���յĶ���
Status Init_Queue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr) malloc (sizeof(QNode));
	
	if( ! Q.front)				//�жϿռ��Ƿ�����ɹ� 
		exit(OVERFLOW);
		
	Q.front->next = NULL;		//ͷ���� next ��Ϊ�� 
	
	return OK;
}
 
//�ж��������Ƿ�Ϊ��
Status Empty_Queue(LinkQueue &Q)
{
	if(Q.front->next == NULL)	//���ͷ���� next ��Ϊ�� 
		return TRUE;
	else
		return FALSE;
} 

//����ָ�����ȵ�������
void Create_Queue(LinkQueue &Q, int n)
{
	QueuePtr p;										//���� p ָ�룬�����½ڵ�ռ� 
	int i;											//������ 
	
	for(i = 0; i < n; i++)
	{
		p = (QueuePtr) malloc (sizeof(QNode));		//�����½ڵ�ռ� 
		if( ! p)									//�жϿռ��Ƿ�����ɹ� 
			exit(OVERFLOW);
		
		scanf("%d", &p->data);						//���½ڵ���д������ 
			
		p->next = NULL;								// p �ĺ��ָ��� 
		Q.rear->next = p;							//ԭ����β�ڵ��ָ��ָ���½ڵ� 
		Q.rear = p;									//��βָ��ָ���½ڵ� 
	}
 } 

//�����������
Status Clear_Queue(LinkQueue &Q)
{
	QueuePtr p, q;				//��������ָ�� 
			
	p = Q.front->next;			// p ָ���һ����� 
	while( ! p)					//�ͷŴ洢�ڵ� 
	{		
		q = p;					// q ָ��ָ�� p 
		p = p->next;			// p ָ����һ���ڵ� 
		free(q);				//�ͷ� q �ڵ� 
	}
		
	Q.front = Q.rear;			//�ص���ʼ��״̬ 
	Q.front->next = NULL;
		
	return OK;
} 

//����������
Status Destroy_Queue(LinkQueue &Q)
{
	while(Q.front)				//Q.front��Ϊ�� 
	{
		Q.rear = Q.front->next;	//Q.rear ָ�� Q.front ����һ���ڵ� 
		free(Q.front);			//�ͷ� Q.front 
		Q.front = Q.rear;		// Q.front ָ�� Q.rear 
	}
	return OK;
}

//����еĳ���
int Length_Queue(LinkQueue &Q)
{
	int i = 0;				//������
	QueuePtr p = Q.front;	// p ָ��ͷ��� 
	
	while(p != Q.rear)
	{
		i++;
		p = p->next;		// p ָ����һ���ڵ� 
	} 
	
	return i;
}

//���ض�ͷԪ��
Status GetHead_Queue(LinkQueue &Q, QElemType &e)
{
	QueuePtr p;				//����ָ�� 
	
	if(Q.front == Q.rear)	//�ж϶����Ƿ�Ϊ�� 
		return ERROR;
	
	p = Q.front->next;		// p ָ���һ����� 
	e = p->data;			//����ͷԪ�ظ�ֵ�� e 
	
	return OK;
} 

//����Ԫ�ص���β
Status Insert_Queue(LinkQueue &Q, QElemType e)
{
	QueuePtr p;								//���������½ڵ��ָ�� 
	
	p = (QueuePtr) malloc (sizeof(QNode));	//�����µĴ洢�ռ� 
	if( ! p)								//�жϿռ��Ƿ�����ɹ� 
		exit(OVERFLOW);
		
	p->data = e;							//��Ҫ�����ֵ���� p ָ�� 
	
	p->next = NULL;							//�½ڵ�ĺ��ָ��� 
	Q.rear->next = p;						//��βָ��ĺ��ָ���½ڵ� 
	Q.rear = p;								//��βָ��ָ���½ڵ� 
				
	return OK;
}

//ɾ����ͷԪ��
Status Delete_Queue(LinkQueue &Q, QElemType &e)
{
	QueuePtr p;					//����ָ�� 
	
	if (Q.front == Q.rear)
		return ERROR;
		
	p = Q.front->next;			// p ָ���һ����� 
	e = p->data;				//��Ҫɾ��Ԫ�ظ��� e 
	
	Q.front->next = p->next;	//ͷָ��ĺ��ָ�� p ����һ���ڵ� 
	
	if (Q.rear == p)			//��ɾ�����Ƕ�β�ڵ� 
		Q.rear = Q.front;		//��βָ��ָ��ͷ��� 
		
	free(p);					//�ͷ� p �ڵ� 
			
	return OK;
} 

//�������Ԫ��
void Printf_Queue(LinkQueue &Q)
{
	QueuePtr p;					//�������ָ�� 
	
	p = Q.front->next;			// p ָ���һ����� 
	while(p)			//�� p δָ��δ�ڵ�ʱ 
	{
		printf("%d ",p->data);	//���Ԫ�� 
		p = p->next;
	}
	printf("\n"); 
} 

int main()
{
	printf("******************�밴��ʾ���в���************************\n");
	printf("***** ��ʼ��������,                     enter    'a' *****\n");
	printf("***** ��������������ݣ�                enter    'b' *****\n");
	printf("***** �ж��������Ƿ�Ϊ�գ�              enter    'c' *****\n");
	printf("***** ��������У�                      enter    'd' *****\n");
	printf("***** ���������� ��                     enter    'e' *****\n");
	printf("***** ����������Ԫ�صĸ�����            enter    'f' *****\n");
	printf("***** ���ض�ͷԪ��,����ɾ����           enter    'g' *****\n");
	printf("***** �ڶ�β����Ԫ�أ�                  enter    'h' *****\n");
	printf("***** ɾ����ͷԪ�أ����÷�����ֵ��      enter    'i' *****\n");
	printf("***** ������������ȫ��Ԫ�أ�          enter    'j' *****\n");
	printf("**********************************************************\n");
	
	LinkQueue Q;		//������е�ͷ 
	QElemType E;		//��������ֵ
	int N;				//������� 
	int back;			//���պ�������ֵ 
	char str; 			//�Ӽ��̽����ַ�
	
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
				back = Init_Queue(Q);
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
				Create_Queue(Q, N);
				break;
			}
			case 'c'://�ж��������Ƿ�Ϊ��
			{
				back = Empty_Queue(Q);
				if(back)
					printf("This is an empty stack. \n");
				else
					printf("This is not an empty stack.  \n");
				break;
			}
			case 'd'://���������
			{
				back = Clear_Queue(Q);
				if(back)
					printf("�������ѱ���գ�����\n");
				else
					printf("�˶������ǿյģ�����Ҫ��գ�����\n");
				break;
			}
			case 'e'://����������
			{
				back = Destroy_Queue(Q);
				if(back)
					printf("�������ѱ����٣�����\n");
				else
					printf("����ʧ�ܣ�����\n");
				break;
			}
			case 'f'://����������Ԫ�صĸ���
			{
				back=Length_Queue(Q);
				printf("�����еĳ����� :     %d\n",back);
				break;
			}
			case 'g'://���ض�ͷԪ��,����ɾ��
			{
				GetHead_Queue(Q, E);
				printf("��ͷԪ��Ϊ :   %d\n",E);
				break;
			}
			case 'h'://�ڶ�β����Ԫ��
			{
				printf("������Ҫ����Ԫ�ص�ֵ��    ");
				scanf("%d",&E);
				back=Insert_Queue(Q,E);
				if(back)
				{
					printf("�����ջ��Ԫ��ֵ��Ϊ��  ");
					Printf_Queue(Q);
					printf("\n");
				}
				else
					printf("����Ԫ��ʧ�ܣ�����\n");
				break;
			}
			case 'i'://ɾ����ͷԪ�أ����� e ������ֵ
			{
				back=Delete_Queue(Q,E);
				if(back)
					printf("ɾ����ջ��Ԫ���ǣ�   %d\n",E);
				else
					printf("ջΪ�գ�û��Ԫ�أ�����\n");
				break;
			}
			case 'j'://������������ȫ��Ԫ��
			{
				Printf_Queue(Q);
				break;
			} 
			default:printf("wrong!\n");
		}
	}while(str!='q');
	return 0;
}
