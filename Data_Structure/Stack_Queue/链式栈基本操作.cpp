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
typedef int SElemType;		//����ջ�е��������� 

typedef struct SqStack
{
	SElemType data;	  		//������ 
	struct SqStack *next;	//ָ���� 
}SqStack,*LinkStack;

//��ʼ����ջ
/* ����һ����ջ��������ջ��ͷ��㣬����NULL�ÿ�	*/
Status Init_Stack(LinkStack *S)
{
	*S = (LinkStack) malloc (sizeof(SqStack));	//����ͷ���ռ�
	
	if(*S == NULL)								//�ж��¿ռ��Ƿ����ɹ� 
		exit(OVERFLOW);
		
	(*S)->next = NULL;							//ͷ�����ָ��� 
	
	return OK;
} 

//��ջ����������
Status Create_Stack(LinkStack *S,int n)
{
	LinkStack q;			// q ָ�����������µĽڵ� 
	int i;					//������ 
	
	for(i = 0; i < n; i++)	//��ջ��λ�����β���Ԫ�� 
	{
		q = (LinkStack) malloc (sizeof (SqStack));	//����ռ� 
		if(q == NULL)				//�жϿռ��Ƿ�����ɹ� 
			exit(OVERFLOW);	
			
		scanf("%d", &q->data);		//���¿ռ����������� 
		
		q->next = (*S)->next;		// q �ĺ��ָ��ͷ��� S �ĺ�� 
		(*S)->next = q;				//ͷ��� S �ĺ��ָ�� q  
	}
	return OK; 
} 

//�ж���ջ�Ƿ�Ϊ�� 
Status Empty_Stack(LinkStack *S)
{
	LinkStack p;
	
	p = (*S)->next;
	if(!p)				//���ͷ���ĺ��ָ��NULL����Ϊ�� ������ 
		return OK;
	else
		return FALSE; 	//���򣬲�Ϊ�� 
}

//�����ջ
Status Clear_Stack(LinkStack *S)
{
	LinkStack p,q;
	
	p = (*S)->next;			// p ָ���һ���ڵ� 
	while(p != NULL)		//�� p ��ָ��յ�ʱ��ѭ�� 
	{
		q = p->next;		// q ָ�� p ����һ���ڵ� 
		free(p);			//�ͷ� p �ڵ� 
		p = q;				// p ����ָ�� q �ڵ� 
	}
	
	(*S)->next = NULL;		//�ڵ��ͷ������ջͷ���ָ��NULL���ص���ʼ��״̬ 
	return OK;
	
} 

//������ջ
Status Destroy_Stack(LinkStack *S)
{
	LinkStack p,q;
	
	p = (*S)->next;		// p ָ���һ���ڵ� 
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
Status Length_Stack(LinkStack *S)
{
	if((*S)->next == NULL)	//���ͷ���ĺ��ָ��NULL����Ϊ�� ������ 
		return ERROR;
		
	LinkStack p;			//����һ��ָ���������� 
	int len = 0;			//����һ�����α�����������������ͳ��ջ�ĳ��� ,��ʼֵΪ0. 
	
	p = (*S)->next;			//pָ��ָ���һ�����
	while(p != NULL)		//��p��δ��NULL��ʱ����� 
	{
		len++; 				//��������һ 
		p = p->next; 		//pָ����һ���ڵ� 
	} 
	
	return len;				//���ؼ�������ֵ������ջ�ĳ��� 
} 

//����ջ��Ϊ�գ��ͷ���ջ��Ԫ��,����ɾ�� 
Status GetTop_Stack(LinkStack *S)
{
	if((*S)->next == NULL)			//�ж���ջ�Ƿ�Ϊ�� 
		return ERROR;	
	else
	{
		return (*S)->next->data;	//��Ϊ�գ��ͷ��ص�һ������Ԫ�� 
	}
} 

//��ջ������Ԫ��
Status Push_Stack(LinkStack *S,SElemType e)
{
	LinkStack p;			//����һ��ָ�룬����ָ��Ҫ����Ԫ�� 
	
	p = (LinkStack)malloc(sizeof(SqStack));	//Ϊָ�� p ����洢�ռ�
	if(p == NULL)			//�жϿռ��Ƿ�����ɹ� 
		exit(OVERFLOW); 
		
	p->data = e;			// ��Ҫ�����ֵ����p�������� 
	p->next = (*S)->next;	// p �ĺ��ָ��ͷ���ĺ�� 
	(*S)->next = p;			// p ��ǰ��ָ��ͷ���ĺ��
	
	return OK;				//����ɹ��������� 
} 
 
//ɾ��ջ��Ԫ�أ����� e ������ֵ 
Status  Pop_Stack(LinkStack *S, SElemType *e)
{
	if((*S)->next == NULL)	//�ж���ջ�Ƿ�Ϊ��ջ 
		return ERROR; 
	
	LinkStack p;
	
	p = (*S)->next;			// p ָ��ջ��Ԫ�� 
	(*S)->next = p->next;	//ͷ��� S �ĺ��ָ��ջ��Ԫ�ص���һ��Ԫ�� 
	*e = p->data;			//��ջ���洢��ֵ���� e ���� 
	
	free(p);				//�ͷ�ջ���ڵ� 
	
	return OK;
}

//�����ջ���ȫ��Ԫ��
Status Printf_Stack(LinkStack *S)
{
	if((*S)->next == NULL)		//�ж���ջ�Ƿ�Ϊ�� 
		return ERROR;
		 
	LinkStack p;
	p = (*S)->next;				// p ָ��ջ���ڵ� 
	
	while(p != NULL)			//�� p û��ָ��յ�ʱ��ѭ�� 
	{
		printf("%d ",p->data);	//��� p ��ָ��Ԫ�� 
		p = p->next;			//�ƶ� p ָ�� 
	}	
} 

int main()
{
	printf("******************�밴��ʾ���в���**********************\n");
	printf("***** ��ʼ����ջ,                     enter    'a' *****\n");
	printf("***** ��ջ���������ݣ�                enter    'b' *****\n");
	printf("***** �ж���ջ�Ƿ�Ϊ�գ�              enter    'c' *****\n");
	printf("***** �����ջ��                      enter    'd' *****\n");
	printf("***** ������ջ ��                     enter    'e' *****\n");
	printf("***** ������ջԪ�صĸ�����            enter    'f' *****\n");
	printf("***** ����ջ��Ԫ��,����ɾ����         enter    'g' *****\n");
	printf("***** ��ջ������Ԫ�أ�                enter    'h' *****\n");
	printf("***** ɾ��ջ��Ԫ�أ����� e ������ֵ�� enter    'i' *****\n");
	printf("***** �����ջ���ȫ��Ԫ�أ�           enter   'j' *****\n");
	printf("********************************************************\n");
	
	LinkStack S;	//����ջ��ͷ 
	SElemType E;	//��������ֵ
	int N;
	int back;	//���պ�������ֵ 
	char str; 	//�Ӽ��̽����ַ�
	do
	{
		printf("\n");
		printf("Please enter a char:    ");
		str=getche();	/*�Ӽ��̻�ȡһ���ַ�����ʾ�������س�ֱ��ִ��*/ 
		printf("\n");	/*�����������Ļس���������س���Ҳ�ᱻ��Ϊ���ַ�*/
		switch(str)
		{
			case 'a'://��ʼ����ջ
			{
				back = Init_Stack(&S);
				if(back)
					printf("��Ϊ����ʼ�����һ������ջ��\n");
				else 
					printf("��ʼ��ʧ�ܣ���\n");	
				break;
			}
			case 'b':// ��ջ����������
			{
				printf("���������ݵĸ�����  ");
				scanf("%d",&N);
				Create_Stack(&S,N);
				break;
			}
			case 'c'://�ж���ջ�Ƿ�Ϊ��
			{
				back = Empty_Stack(&S);
				if(back)
					printf("This is an empty stack. \n");
				else
					printf("This is not an empty stack.  \n");
				break;
			}
			case 'd'://�����ջ
			{
				back = Clear_Stack(&S);
				if(back)
					printf("��ջ�ѱ���գ�����\n");
				break;
			}
			case 'e'://������ջ
			{
				back=Destroy_Stack(&S);
				if(back)
					printf("��ջ�ѱ����٣�����\n");
				break;
			}
			case 'f'://������ջԪ�صĸ���
			{
				back=Length_Stack(&S);
				printf("��ջ�ĳ����� :     %d\n",back);
				break;
			}
			case 'g'://����ջ��Ԫ��,����ɾ��
			{
				E=GetTop_Stack(&S);
				printf("ջ��Ԫ��Ϊ :   %d\n",E);
				break;
			}
			case 'h'://��ջ������Ԫ��
			{
				printf("������Ҫ����Ԫ�ص�ֵ��    ");
				scanf("%d",&E);
				back=Push_Stack(&S,E);
				if(back)
				{
					printf("�����ջ��Ԫ��ֵ��Ϊ��  ");
					Printf_Stack(&S);
					printf("\n");
				}
				else
					printf("����Ԫ��ʧ�ܣ�����\n");
				break;
			}
			case 'i'://ɾ��ջ��Ԫ�أ����� e ������ֵ
			{
				back=Pop_Stack(&S,&E);
				if(back)
					printf("ɾ����ջ��Ԫ���ǣ�   %d\n",E);
				else
					printf("ɾ��ʧ�ܣ�����\n");
				break;
			}
			case 'j'://�����ջ���ȫ��Ԫ��
			{
				Printf_Stack(&S);
				break;
			} 
			default:printf("wrong!\n");
		}
	}while(str!='q');
	return 0;
}
