#include<stdio.h>
#include<stdlib.h>

#define MAX 60
#define	OVERFLOW 0
#define OK 1

typedef struct
{
	char str[MAX];
	int length;
}SString;

typedef char AtomType;
typedef int ElemType;
typedef int Status;

typedef enum{ATOM, LIST} ElemTag;		//ATOM == 0:ԭ�ӣ�LIST == 1���ӱ�

typedef struct GLNode
{
	ElemType tag;					//�������֣���������ԭ�ӽڵ�ͱ�ڵ�
	union {							//ԭ�ӽڵ�ͱ�������ϲ��� 
		
		AtomType atom;
		struct{
			struct GLNode *hp, *tp;
		}ptr;						//ptr�Ǳ����ָ����ptr.hp��ptr.tp�ֱ�ָ���ͷ�ͱ�β
		 
	};
}  *GList, GLNode;					//���������


//����ֵ����ʵ��
void StrAssign(SString *S,const char str[])
{
	int i;
	for (i = 0; str[i] != '\0'; i++)
		S->str[i] = str[i];   //������cstr�е��ַ���ֵ����S  
	S->length = i;
}

//���ıȽϲ���
int StrCompare(SString S, SString T)
{   
	int i;
	for (i = 0; i<S.length&&i<T.length; i++)//�Ƚ��������е��ַ�  
	{
		if (S.str[i] != T.str[i])        //��������ַ���ͬ���򷵻������ַ��Ĳ�ֵ  
			return (S.str[i] - T.str[i]);
	}
	return (S.length - T.length); //����Ƚ���ϣ������������ĳ��ȵĲ�ֵ  
}

//�󴮵ĳ��Ȳ���  
int StrLength(SString S)
{
	return S.length;
}

//��ȡ�Ӵ�����  
int SubString(SString *Sub, SString S, int pos, int len)
{
	int i;
	if (pos<0 || len<0 || pos + len - 1>S.length)
	{
		return 0;
	}
	else
	{
		for (i = 0; i<len; i++)
			Sub->str[i] = S.str[i + pos - 1];
		Sub->length = len;
		return 1;
	}
}

//���ĸ��Ʋ���  
void StrCopy(SString *T, SString S){
	int i;
	for (i = 0; i<S.length; i++)  //����S���ַ���ֵ����T  
		T->str[i] = S.str[i];
	T->length = S.length;       //����S�ĳ��ȸ�ֵ����T  
}

//������ղ���  
void StrClear(SString *S)
{
	S->length = 0;
}

void DistributeString(SString *Str, SString *HeadStr)
//����Str������������֣�HeadStrΪ��һ������֮ǰ���Ӵ���StrΪ���ź���Ӵ�
{
	int len, i, k;
	SString Ch, Ch1, Ch2, Ch3;
	len = StrLength(*Str);                //lenΪStr�ĳ���
	StrAssign(&Ch1, ",");                //���ַ�','��'('��')'�ֱ𸳸�Ch1,Ch2��Ch3
	StrAssign(&Ch2, "(");
	StrAssign(&Ch3, ")");
	SubString(&Ch, *Str, 1, 1);            //Ch����Str�ĵ�һ���ַ�
	for (i = 1, k = 0; i <= len&&StrCompare(Ch, Ch1) || k != 0; i++) //����Str�����ĵ�һ������
	{
		SubString(&Ch, *Str, i, 1);        //ȡ��Str�ĵ�һ���ַ�
		if (!StrCompare(Ch, Ch2))         //�����һ���ַ���'('������k��1
			k++;
		else if (!StrCompare(Ch, Ch3))    //�����ǰ�ַ���')'������k��ȥ1
			k--;
	}
	if (i <= len)                           //��Str�д���','�����ǵ�i-1���ַ�
	{
		SubString(HeadStr, *Str, 1, i - 2);  //HeadStr���洮Str','ǰ���ַ�
		SubString(Str, *Str, i, len - i + 1);  //Str���洮Str','����ַ�
	}
	else                                //��Str�в�����','
	{
		StrCopy(HeadStr, *Str);          //����Str�����ݸ��Ƶ���HeadStr
		StrClear(Str);                  //��մ�Str
	}
}

//�жϴ��Ƿ�Ϊ�գ���Ϊ�շ���1�����򷵻�0  
int StrEmpty(SString S)
{
	if (S.length == 0)
		return 1;
	else
		return 0;
}

int GListDepth(GList L)
//���������Ȳ���
{
	int max, depth;
	GLNode *p;
	if (!L)                          //��������ǿգ��򷵻�1
		return 1;
	if (L->tag == ATOM)                 //����������ԭ�ӣ��򷵻�0
		return 0;
	for (max = 0, p = L; p; p = p->ptr.tp)         //��㴦������
	{
		depth = GListDepth(p->ptr.hp);
		if (max<depth)
			max = depth;
	}
	return (max + 1);
}

void CopyList(GList *T, GList L)
//�����ĸ��Ʋ������ɹ����L���Ƶõ������T
{
	if (!L)                          //��������Ϊ�գ���TΪ�ձ�
		*T = NULL;
	else
	{
		*T = (GList)malloc(sizeof(GLNode));   //��L���գ�ΪT����һ������


		(*T)->tag = L->tag;
		if (L->tag == ATOM)            //����ԭ��
			(*T)->atom = L->atom;
		else                        //�ݹ鸴���ӱ�
		{
			CopyList(&((*T)->ptr.hp), L->ptr.hp);
			CopyList(&((*T)->ptr.tp), L->ptr.tp);
		}
	}
}

void CreateList(GList *L, SString S)
//����ͷβ�����������
{
	SString Sub, HeadSub, Empty;
	GList p, q;
	StrAssign(&Empty, "()");
	if (!StrCompare(S, Empty))            //�������Ĵ��ǿմ��򴴽�һ���յĹ����
		*L = NULL;
	else
	{
		if (!(*L = (GList)malloc(sizeof(GLNode))))     //Ϊ���������һ�����
			exit(OVERFLOW);
		if (StrLength(S) == 1)                         //�������ԭ�ӣ���ԭ�ӵ�ֵ��ֵ���������
		{
			(*L)->tag = ATOM;
			(*L)->atom = S.str[0];
		}
		else                                        //������ӱ�
		{
			(*L)->tag = LIST;
			p = *L;
			SubString(&Sub, S, 2, StrLength(S) - 2);     //��Sȥ�����������ţ�Ȼ��ֵ��Sub
			do
			{
				DistributeString(&Sub, &HeadSub);    //��Sub�������ͷ�ͱ�β�ֱ�ֵ��HeadSub��Sub
				CreateList(&(p->ptr.hp), HeadSub);    //�ݹ�������ɹ����
				q = p;
				if (!StrEmpty(Sub))                  //�����β���գ������ɽ��p������βָ����ָ��p
				{
					if (!(p = (GLNode *)malloc(sizeof(GLNode))))
						exit(OVERFLOW);
					p->tag = LIST;
					q->ptr.tp = p;
				}
			} while (!StrEmpty(Sub));
			q->ptr.tp = NULL;
		}
	}
}

int main()
{
	GList L, T;
	SString S;
	int depth;
	char str[60];
	scanf("%s", str);
	StrAssign(&S, str);
	CreateList(&L, S);
	depth = GListDepth(L);
	printf("%d\n",depth);
}
