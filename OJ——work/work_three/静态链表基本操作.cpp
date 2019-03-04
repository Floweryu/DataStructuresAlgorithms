#include<stdio.h>
#include<string.h>

#define MAXSIZE 11		//��̬����ĳ���
typedef char ElemType[8];	//Ԫ�ص����ͣ��涨���ϲ�����7���ַ�

typedef struct{
	ElemType data;		//�ڵ��е�����
	int cur;			//��һ���ڵ���±� 
}NodeType;				//�ڵ�����

NodeType space[MAXSIZE];	//�����洢�ڵ�����飬�൱��һ�������е��ڴ�

typedef struct{
	int elem;		//��̬����洢�ռ��ַ����ʼԪ�ص��±꣩
	int length;		//��̬�����е�Ԫ����Ŀ
	int listsize;	//��̬����ǰԪ�صĳ��ȣ�������Ԫ�ص���Ŀ 
}SLinkList;			//��̬�������͵Ķ��壬��һ���������� 

//��һά����space�и���������һ����������space[0].curΪͷָ�� 
void InitSpace_SL() 
{
	memset(space,0,sizeof(space));
	for(int i=0;i<MAXSIZE-1;i++)
		space[i].cur=i+1;
	space[MAXSIZE-1].cur=0;
} 

//����������ǿգ��򷵻ط���Ľڵ��±꣨��������ĵ�һ���ڵ㣩�����򷵻�0
int Malloc_SL()
{
	int i=space[0].cur;
	if(i)		//��������ǿ� 
		space[0].cur=space[i].cur;/*���������ͷ���ָ��ԭ��������ĵڶ����ڵ�*/ 
 	return i; /*�����¿��ٽڵ������*/ 
} 

//������̬����
void CreateList_SL(SLinkList &S)
{
	S.elem=Malloc_SL();
	space[S.elem].cur=0;
	S.length=0;
	S.listsize=9;
 } 
 
//����̬�����е����нڵ���ʾ����
void Show_space()
{
	int i;
	for(i=0;i<MAXSIZE;i++)
	{
		printf("%-8s%2d\n",space[i].data,space[i].cur);
	}
 } 
 

//�ھ�̬������L�в��ҵ�һ��ֵΪe��Ԫ��
//���ҵ����򷵻�����L�е�λ�򣬷��򷵻�0.
int LocateElem_SL(SLinkList &S,ElemType e)
{
	int i;
	i=S.elem;	//iָʾ���е�һ���ڵ� 
	while(i&&strcmp(space[i].data,e))//strcmp����������ȷ���0�����ڷ���1��С�ڷ��ظ��� 
		i=space[i].cur;	//�ڱ���˳������,i������һ���ڵ��ַ�����Բ�����i++ 
	return i; 
 } 
 
//���±�Ϊk�Ŀ��нڵ���յ�����������Ϊ��������ĵ�һ���ڵ㣩*/
void Free_SL(int k)
{
	//�൱�ڲ���ڵ� 
	space[k].cur=space[0].cur;	//���ս��2���α�ָ��������ĵ�һ����� 
	space[0].cur=k;	//���������ͷ���ָ���»��յĽڵ� 
 } 
 
//����̬����S�еĵ�i��λ��ǰ����e
void Insert_SL(SLinkList &S,int i,ElemType e)
{
	int cur=S.elem;		//ָ��̬����ĵ�һ�����
	int j=0;
	int newNodeIndex;	//�洢�·���Ľڵ��±�
	while(j<i-1)	//Ѱ�ҵ�i-1���ڵ�
	{
		cur=space[cur].cur;
		j++;
	}
	newNodeIndex=Malloc_SL();
	strcpy(space[newNodeIndex].data,e);	//���µĽڵ��д�������
	space[newNodeIndex].cur=0;		//ָ��Ϊ��
	space[newNodeIndex].cur=space[cur].cur;		//���뾲̬������
	space[cur].cur=newNodeIndex;
	S.length++;		//�����̬�����ȼ�һ 
}

//ɾ����̬�����еĵ�i���ڵ�
void Delete_SL(SLinkList &S,int i)
{
	int cur=S.elem;		//ָ��̬�����еĵ�һ�����
	int j=0;
	int delCur;		//�洢��ɾ�������±�
	while(j<i-1)	//Ѱ�ҵ�i-1���ڵ�
	{
		cur=space[cur].cur;	//��̬����ڵ��ƶ���ʽ 
		j++;	//�������� 
	}
	delCur=space[cur].cur;	//�ҵ���ɾ���Ľڵ���±�
	space[cur].cur=space[delCur].cur;//����ɾ���ڵ����һ���ڵ��ַ���ӵ�i-1���ڵ���
	Free_SL(delCur);	//�ͷŽڵ�
	S.length--;		//ɾ����̬�����ȼ�һ 
 } 


int main()
{
	SLinkList S;	//���徲̬����
	char str[10];	//�������ָ��
	int a;		//�洢λ��
	ElemType e;	//�洢Ԫ��
	InitSpace_SL();	//��ʼ���������� 
	CreateList_SL(S);	//������̬���� 
	while(scanf("%s",str)!=EOF)
	{
		if(strcmp(str,"insert")==0)		//����Ԫ�� 
		{
			scanf("%d%s",&a,e);
			Insert_SL(S,a,e);
		}
		else if(strcmp(str,"delete")==0)	//ɾ��Ԫ��
		{
			scanf("%d",&a);
			Delete_SL(S,a);
		}
		else if(strcmp(str,"search")==0) 	//����Ԫ��
		{
			scanf("%s",e);
			printf("%2d\n********************\n",LocateElem_SL(S,e));
		}
		else if(strcmp(str,"show")==0)		//��ʾ��̬����
		{
			Show_space();
			puts("********************");
		 } 
	 } 
	return 0;
 } 
