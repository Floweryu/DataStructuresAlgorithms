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

int main()
{
	string s;
	cin>>s;
	int *p, i;
	p = new int[s.size()];
		
	get_next(s, p);							//�õ� next ���鲢��� 
	for(i = 0; i < s.size(); i++)
		cout<<*(p+i)+1<<" "; 
	cout<<endl;
 } 
