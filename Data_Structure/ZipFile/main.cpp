#include <iostream>
#include <fstream>
#include <set>
#include <cstring>
#include <cstdlib>
#include "HuffumanTree.h"

using namespace std;

bool CompressFile(const char* name)
{
    char temp;  //��ʱ����
    int value[128] = {0};
    int numchar = 0;
    ifstream infile;
    infile.open(name,ios::in);
    if(!infile)
    {
        cerr<<"Open "<<name<<" error!"<<endl;
        return false;
    }
    while(infile.get(temp))
    {
        value[(int)temp]++;
        numchar++;
    }

    HuffmanTree tree;
    HuffmanCode code;
    huffmanCoding(tree,code,value,128);
    infile.close();


    //��Ϊ����ʹ���ļ�ָ��������ٴ�һ�κ���
    infile.open(name,ios::in);
    if(!infile)
    {
        cerr<<"Open "<<name<<" error!"<<endl;
        return false;
    }
    //ѹ�����ݵ�����ļ�
    ofstream outfile;
    outfile.open("cmpfile.txt",ios::out|ios::binary);
    if(!outfile)
    {
        cerr<<"Open cmpfile.txt error!"<<endl;
        return false;
    }

    int count = 0;
    while(infile.get(temp))
    {
        //���+1����Ϊ���������ĳ����ı����һλΪ�յ�
        for(char *p = code[(int)temp + 1]; *p != '\0';p++)
        {
            char tmp;
            if(*p == '1')
            {
                tmp = tmp << 1;
                tmp = tmp | 00000001;
            }
            else
            {
                tmp = tmp << 1;
            }
            count++;
            //ÿ����8λ�ʹ���һ���ַ�
            if(count == 8)
            {
                outfile.write(&tmp,1);
                count = 0;
            }
        }//for
    }//while
    while(count > 0 && count < 8)
    {
        temp = temp << 1;
        temp = temp | 00000001;
        count++;
    }
    outfile.write(&temp,1);

    outfile.close();
    infile.close();

    //�������ļ����
    outfile.open("cmpconfig.txt",ios::out);
    if(!outfile)
    {
        cerr<<"Open cmpconfig.txt error!"<<endl;
        return false;
    }
    outfile<<numchar<<" ";
    for(int i = 0;i < 128;i++)
        outfile<<value[i]<<" ";
    outfile.close();
}



bool DeCompressFile()
{
    ifstream infile;
    ofstream outfile;

    int charnum = 0;
    int value[128];
    HuffmanCode code;
    HuffmanTree tree;

    infile.open("cmpconfig.txt",ios::in);
    if(!infile)
    {
        cerr<<"Open cmpconfig.txt error"<<endl;
        return false;
    }
    infile>>charnum;
    for(int i = 0;i < 128;i++)
    {
        infile>>value[i];
    }
    //�������ݶ�������
    //������������
    huffmanCoding(tree,code,value,128);
    infile.close();

    infile.open("cmpfile.txt",ios::in|ios::binary);
    if(!infile)
    {
        cerr<<"Open cmpfile.txt error"<<endl;
        return false;
    }


    outfile.open("dezipfile.txt",ios::out);
    if(!outfile)
    {
        cerr<<"Open dezipfile.txt error"<<endl;
        return false;
    }

    char temp;
    char radis[100];
    int count = 0;

    while(infile.read(&temp,1))
    {
        //һ�ζ�8λ
        for(int i = 0;i < 8;i++)
        {
            //һλһλ���
            if((temp & 10000000) == 10000000)
            {
                 radis[count] = '1';
            }
            else
            {
                radis[count] = '0';
            }
            //����һλ
            temp = temp << 1;

            radis[++count] = '\0';

            for(int j = 0 ; j < 128;j++)
            {
                //�Ƚϵ�ǰ�������ڵģ��Ͷ�Ӧ������ͬ����˭
                if(strcmp(radis,code[j+1]) == 0)
                {

                    outfile<<char(j);
                    count = 0;
                    radis[count] = '\0';
                    charnum--;
                    if(charnum == 0)
                    {
                        infile.close();
                        outfile.close();
                    }

                }//if
            }//for
        }//for
    }//while
    infile.close();
    outfile.close();

}

int main()
{
    char name[10000];
    cout<<"�������ļ���.��ʽ��:"<<endl;
    cout<<"�����������ڵ��ļ��������Զ����ɣ�ѹ���ļ�."<<endl;
    cin>>name;
    CompressFile(name);
    cout<<endl;
    DeCompressFile();
    getchar();
    return 0;
}
