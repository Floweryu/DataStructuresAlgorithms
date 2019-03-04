/**
* Author : ZhangJunFeng
* Date : 2018-11-28-12.52.58
* Function: ʵ���ļ�ѹ������
* Description :
*/
#include <iostream>
#include <fstream>
#include <set>
#include <cstring>
#include <cstdlib>
#include "huffmancode.h"

using namespace std;

bool CompressFile(const char* name_txt)
{
    ifstream openfile;              //�����ļ���ָ��
    char ch;                        //��ʱ�洢����
    int weight[128] = {0};          //����Ȩֵ�洢���鲢��ʼ��Ϊ0
    int char_num = 0;               //�����ļ����ַ��ĸ���

    openfile.open(name_txt, ios::in);       //Ϊ���루���������ļ�
    if (! openfile)
    {
        cerr<<"cannot open"<<name_txt<<"!!!"<<endl;
        return false;
    }

    while (openfile.get(ch))                //���ļ��ж�ȡһ���ַ�
    {
        weight[(int)ch]++;                  //ͳ�Ƹ��ַ���Ȩֵ���Ը��ַ���ASCII��Ϊ�±�
        char_num++;                         //ͳ���ļ����ַ��ĸ���
    //    cout<<(int)ch<<" ";
    }
   // cout<<char_num<<endl;
    HuffmanTree tree;
    HuffmanCode code;
    HuffmanCoding(tree, code, weight, 128);     //����Ȩֵ�����±����ֵΪȨֵ�������б���
    //openfile.close();                         //�ر��ļ�
    openfile.clear();
    openfile.seekg(0, ios::beg);                //�Ѵ��ļ�ָ��ָ���ļ���ͷ
/*    //�ٴδ��ļ�
    openfile.open(name_txt, ios::in);
    if (! openfile)
    {
        cout<<"cannot open"<<name_txt<<"!!!"<<endl;
        return false;
    }
*/
    ofstream outfile;
    outfile.open("zipfile.txt",ios::out|ios::binary);
    if (! outfile)
    {
        cerr<<"Open the zipfile.txt error!!!"<<endl;
        return false;
    }

    int count = 0;
    while (openfile.get(ch))
    {
        for(char *p = code[(int)ch + 1]; *p != '\0';p++)        //��һ����Ϊ�շ��������һ��ʼ����
        {
            char temp;                  //temp�Ķ�����Ϊ 0000 0000
            if (*p == '1')
            {
                temp = temp << 1;
                temp = temp | 00000001;
            }
            else
            {
                temp = temp << 1;
            }
            count++;                         //ͳ����λ����

            if (count == 8)                  //ÿ�ư�λ��д���ļ�һ��
            {
                outfile.write(&temp, 1);     // 1 ��ʾд��һ���ַ�
                count = 0;
            }
        }   //end for
    }  // end while

    while (count > 0 && count < 8)      //������һ����λ�ֽ�û����
    {
        ch = ch << 1;
        ch = ch | 00000001;             //������λ���� 0 ��
        count++;
    }
    outfile.write(&ch, 1);              //�����һ���ַ�д��

    outfile.close();
    openfile.close();

    //�������ļ�������ļ���
    outfile.open("zipconfig.txt",ios::out);
    if(!outfile)
    {
        cerr<<"Open zipconfig.txt error!"<<endl;
        return false;
    }
    outfile<<char_num<<" ";
    for(int i = 0;i < 128;i++)
        outfile<<weight[i]<<" ";
    outfile.close();

}

bool DeCompressFile()
{
    HuffmanTree tree;
    HuffmanCode code;

    ifstream infile;
    ofstream outfile;
    int char_num = 0;
    int weight[128];

    outfile.open("cao.txt", ios::out);
    outfile<<"fuck you11";
    outfile.close();
    infile.open("zipconfig.txt", ios::in);
    if (! infile)
    {
        cerr<<"open zipconfig.txt error!!!"<<endl;
        return false;
    }

    infile>>char_num;
    for (int i = 0; i < 128; i++)
    {
        infile>>weight[i];
    }
    //Ȩֵ�������
    //���湹���շ�����
    HuffmanCoding(tree, code, weight, 128);
    //for (int i = 0; i < 128; i++)
      //  puts(code[i]);
    infile.close();

    infile.open("zipfile.txt",ios::in|ios::binary);
    if(!infile)
    {
        cerr<<"Open zipfile.txt error"<<endl;
        return false;
    }


    outfile.open("dezipfile.txt",ios::out);
    if(!outfile)
    {
        cerr<<"Open dezipfile.txt error"<<endl;
        return false;
    }

    char ch;
    char decode[100];
    int count = 0;

    while(infile.read(&ch, 1))
    {
        for(int i = 0; i < 8; i++)
        {
            if ((ch & 10000000) == 10000000)
            {
                decode[count] = '1';
            }
            else
            {
                decode[count] = '0';
            }
            ch = ch << 1;

            decode[++count] = '\0';

            for (int j = 0; i < 128; j++)
            {
                if (strcmp(decode, code[j+1]) == 0)
                {
                    outfile<<char(j);
                    count = 0;
                    decode[count] = '\0';
                    char_num--;
                    if (char_num == 0)
                    {
                        infile.close();
                        outfile.close();
                    }
                } //end if
            } // end for
        }  //end for
    }  // end while
    infile.close();
    outfile.close();
}

bool DDeCompressFile()
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
    HuffmanCoding(tree,code,value,128);
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
	char name_txt[10000];
    cout<<"�������ļ���.��ʽ��:"<<endl;
    cout<<"�����������ڵ��ļ��������Զ����ɣ�ѹ���ļ�."<<endl;
    cin>>name_txt;
    CompressFile(name_txt);
    //cout<<endl;
    DeCompressFile();
    getchar();
    return 0;
}
