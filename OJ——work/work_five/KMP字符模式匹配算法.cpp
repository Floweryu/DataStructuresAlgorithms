#include<iostream>
#include<string>

using namespace std;

void get_next(string T, int next[])			//�õ� next ���麯�� 
{
	int i = 0, j = -1;						//�ӵ�һ���ַ���ʼ�Ƚϣ�i = 0 �� j �ĳ�ʼֵӦ�ú� next ����ĵ�һ���洢ֵһ�� 
	
	next[0] = -1;							// next �����һ����ַ�� -1 ��û�д� next[1] ���� 
	
	while(i < T.size() - 1)					//��� T.size()�� 5 ���� i ѭ���� 3 ʱ next �����Ѿ����� 4 ��ַ��5������ 
	{
		if(j == -1 || T[i] == T[j])
		{
			i++;
			j++;
			next[i] = j;					//�����ȣ� next + 1;
		}
		else
			j = next[j];					//����j ����ʧ�䴦�� next ֵ�� 
	}
	
}

void get_nextval(string T, int nextval[])
{
	int i = 0, j = -1;
	nextval[0] = -1;
	while(i < T.size() - 1)
	{
		if(j == -1 || T[i] == T[j])
		{
			i++;
			j++;
			if(T[i] != T[j])
			{
				nextval[i] = j;
			}
			else
			nextval[i] = nextval[j];
		}
		else
			j = nextval[j];
	}
}

int Index_KMP(string S, string T, int pos, int next[])
{
	int i = pos, j = 0;								// pos ֵ����ΪӦ��ȷ������֪��ΪʲôҪ�������� 
	
	while(i < (int)S.size() && j < (int)T.size())	//�� i �� j �����������Ƕ�Ӧ���ַ�����ʱ 
	{
		if(j == -1 || S[i] == T[j])					//�����ȣ��ͱ��� 
		{
			i++;
			j++;
		}		
		else										//���� 
			j = next[j];							//ģʽ�������ƶ� 
	}

	if(j >= T.size())								//�� j ����ģʽ������ʱ��˵����ģʽ��������һ�� 
		return i - T.size() + 1;					/*��ʱ i ָ��ģʽ�����һ���ַ��������е�λ�ã�Ҫ��ȥģʽ�����ȡ�
													  ���ڴ� 0 ��ʼ���������Լ���һ����鿴  */ 
	else		
		return 0;
	 
}

int main()
{
	string s1, s2;
	int *p, i;
	while(cin>>s1>>s2)
	{
		p = new int[s2.size()];	
		
		get_nextval(s2, p);
		i = Index_KMP(s1, s2, 0, p);
		if(i)
			cout<<i<<endl;
		else
			cout<<"0"<<endl;
		
		delete [] p;
	}
 } 
