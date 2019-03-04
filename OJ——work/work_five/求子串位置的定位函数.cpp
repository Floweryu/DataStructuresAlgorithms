#include<iostream>
#include<string>

using namespace std;


int Index_KMP(string S, string T)
{
	int i = 0, j = 0;								// pos ֵ����ΪӦ��ȷ������֪��ΪʲôҪ�������� 
	
	while(i < (int)S.size() && j < (int)T.size())	//�� i �� j �����������Ƕ�Ӧ���ַ�����ʱ 
	{	
		if(S[i] == T[j])
		{
			cout<<S[i];
			i++;
			j++;
		}	
		else 
		{	
			cout<<S[i];									//���� 
			i = i - j + 1;
			j = 0;
		}							//ģʽ�������ƶ� 
	}
	cout<<endl;
	if(j >= T.size())								//�� j ����ģʽ������ʱ��˵����ģʽ��������һ�� 
		return i - T.size() + 1;					/*��ʱ i ָ��ģʽ�����һ���ַ��������е�λ�ã�Ҫ��ȥģʽ�����ȡ�
													  ���ڴ� 0 ��ʼ���������Լ���һ����鿴  */ 
	else		
		return 0;
	 
}

int main()
{
	string s1, s2;
	int t = 3, i;
	while(t--)
	{
		cin>>s1;
		cin>>s2;
		
		i = Index_KMP(s1, s2);
		if(i)
			cout<<i<<endl;
		else
			cout<<"0"<<endl;
		
	}
 } 
