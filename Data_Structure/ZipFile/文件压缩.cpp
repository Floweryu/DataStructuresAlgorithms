/**
* Author : ZhangJunFeng
* Date : 2018-11-28-12.52.58
* Function: 实现文件压缩功能
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
    ifstream openfile;              //定义文件打开指针
    char ch;                        //临时存储变量
    int weight[128] = {0};          //定义权值存储数组并初始化为0
    int char_num = 0;               //定义文件中字符的个数

    openfile.open(name_txt, ios::in);       //为输入（读）而打开文件
    if (! openfile)
    {
        cerr<<"cannot open"<<name_txt<<"!!!"<<endl;
        return false;
    }

    while (openfile.get(ch))                //从文件中读取一个字符
    {
        weight[(int)ch]++;                  //统计该字符的权值，以该字符的ASCII码为下标
        char_num++;                         //统计文件中字符的个数
    //    cout<<(int)ch<<" ";
    }
   // cout<<char_num<<endl;
    HuffmanTree tree;
    HuffmanCode code;
    HuffmanCoding(tree, code, weight, 128);     //对以权值数组下标最大值为权值个数进行编码
    //openfile.close();                         //关闭文件
    openfile.clear();
    openfile.seekg(0, ios::beg);                //把打开文件指针指向文件开头
/*    //再次打开文件
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
        for(char *p = code[(int)ch + 1]; *p != '\0';p++)        //加一是因为赫夫曼编码从一开始计数
        {
            char temp;                  //temp的二进制为 0000 0000
            if (*p == '1')
            {
                temp = temp << 1;
                temp = temp | 00000001;
            }
            else
            {
                temp = temp << 1;
            }
            count++;                         //统计移位次数

            if (count == 8)                  //每移八位，写入文件一次
            {
                outfile.write(&temp, 1);     // 1 表示写入一个字符
                count = 0;
            }
        }   //end for
    }  // end while

    while (count > 0 && count < 8)      //如果最后一个八位字节没有满
    {
        ch = ch << 1;
        ch = ch | 00000001;             //不够的位置用 0 补
        count++;
    }
    outfile.write(&ch, 1);              //把最后一个字符写入

    outfile.close();
    openfile.close();

    //将配置文件输出到文件中
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
    //权值读入完成
    //下面构建赫夫曼树
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
    //配置数据读进来了
    //建立霍夫曼树
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
        //一次读8位
        for(int i = 0;i < 8;i++)
        {
            //一位一位检查
            if((temp & 10000000) == 10000000)
            {
                 radis[count] = '1';
            }
            else
            {
                radis[count] = '0';
            }
            //左移一位
            temp = temp << 1;

            radis[++count] = '\0';

            for(int j = 0 ; j < 128;j++)
            {
                //比较当前缓存区内的，和对应的码相同的有谁
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
    cout<<"请输入文件名.格式名:"<<endl;
    cout<<"请务必输入存在的文件，随后会自动生成，压缩文件."<<endl;
    cin>>name_txt;
    CompressFile(name_txt);
    //cout<<endl;
    DeCompressFile();
    getchar();
    return 0;
}
