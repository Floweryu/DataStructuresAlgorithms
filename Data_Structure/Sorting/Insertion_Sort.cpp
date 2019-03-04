/**
* Author : ZhangJunFeng
* Date : 2018-12-18-20.59.01
* Function: 插入排序的若干算法————直接插入，折半插入，希尔插入
* Algorithm description :   1，程序输入数据用了随机数组，只需要输入数组中数据的个数即可。
                            2，数组下标为 0 的地址用来临时存储当前待插入值
                            3，希尔排序：每次排序以一确定间隔比较两个数值，直到该间隔为 1 。间隔个数就是排序次数。
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
using namespace std;

#define MAX_NUM 100
#define NUM_MODLE 100

typedef int ElemType;

struct SqList {
	ElemType list[MAX_NUM];
	int length;
};

//直接插入排序————从小到大
void Direct_InsertSort(SqList &L) {
	int i, j;
	for (i = 2; i <= L.length; i++) {                    //从第二个位置开始寻找
		if (L.list[i] < L.list[i-1]) {
			L.list[0] = L.list[i];                       //将该值存储
			L.list[i] = L.list[i-1];                     //把前一个值向后移动一位
			for (j = i - 2; L.list[j] > L.list[0]; --j) { //从待插入值的前两个值起(因为前一个值已经移动)，把比 L.list[i] 大的值向后移动一位
				L.list[j+1] = L.list[j];
			}  //跳出循环时 j 已经指到小于或等于L.list[0]的位置
			L.list[j+1] = L.list[0];
		}
	}
}

//折半插入排序
void Binary_InsertSort(SqList &L) {
	int low, high, half;
	int i, j;
	for (i = 2; i <= L.length; i++) {
		L.list[0] = L.list[i];
		low = 1;
		high = i-1;
		while(high >= low) {
			half = (high + low) / 2;
			if (L.list[0] < L.list[half])
				high = half - 1;
			else
				low = half + 1;
		}   //跳出循环时 high 已经指到小于或等于L.list[0]的位置
		for (j = i - 1; j > high; j--)      //向后移动
			L.list[j+1] = L.list[j];
		L.list[high+1] = L.list[0];
	}
}

//获得希尔排序的数组————折半
void Shell_Array(SqList &L, int dlta[], int len, int &k) {
	while(len >=2) {
		dlta[k] = len / 2;
		k++;
		len /= 2;
	}
}

//希尔插入
void Shell_Insert(SqList &L, int dk) {
	int i, j;

	for (i = dk + 1; i <= L.length; i++) {      //以确定间隔比较两数值，交换位置
		if (L.list[i] < L.list[i-dk])
			swap(L.list[i], L.list[i-dk]);
	}
}

//希尔排序
void Shell_InsertSort(SqList &L, int dlta[], int t) {
	int k;
	for (k = 0; k < t; k++)                     //更新间隔长度
		Shell_Insert(L, dlta[k]);
}


//随机产生数组
void CreateList(SqList &L) {
	int i;
	srand(time(0));
	for (i = 1; i <= L.length; i++) {
		L.list[i] = rand() % NUM_MODLE;
	}
}

void PrintfList(SqList &L) {
	int i;
	for (i = 1; i <= L.length; i++)
		cout<<L.list[i]<<" ";
	cout<<endl;
}


int main() {
	cout<<"*************************************************"<<endl;
	cout<<"*****Direct_InsertSort        enter   'a'  ******"<<endl;
	cout<<"*****Binary_InsertSort        enter   'b'  ******"<<endl;
	cout<<"*****Shell_InsertSort         enter   'c'  ******"<<endl;
	cout<<"*************************************************"<<endl;
	SqList Li;
	int lilong;
	char str;

	cout<<"输入数组长值:    ";
	cin>>lilong;
	Li.length = lilong;

	CreateList(Li);
	cout<<"输入的数组为:"<<endl;
	PrintfList(Li);

	do {
		cout<<endl;
		cout<<"Please enter a char :        ";
		cin>>str;
		switch(str) {
			case 'a': {
				Direct_InsertSort(Li);
				cout<<"排序后的数组为:"<<endl;
				PrintfList(Li);
				break;
			}
			case 'b': {
				Binary_InsertSort(Li);
				cout<<"排序后的数组为:"<<endl;
				PrintfList(Li);
				break;
			}
			case 'c': {
				int increase[lilong], leng;

				Shell_Array(Li, increase, lilong, leng);

				Shell_InsertSort(Li, increase, leng);

				cout<<"排序后的数组为:"<<endl;
				PrintfList(Li);
				break;
			}
			default:
				cout<<"Wrong!!!"<<endl;
		}
	} while (str != 'q');

	return 0;
}







