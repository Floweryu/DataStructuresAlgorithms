此程序包含了线性表的基本算法。

基本函数个数：14个。

函数名称及其功能：
	InitList()		构建一个空的线性表（线性表的初始化）
	CreateList()		给一个空的现行表赋值
	DestroyList（）		销毁线性表
	ClearList（）		清空线性表
	EmptyList（）		判断线性表是否为空
	LengthList（）		返回线性表长度
	iInsertList（）		在线性表第i个元素前插入e,表的长度加1
	eInsertList()		在线性表中值为e的元素前插入E
	iDeleteList（）		删除线性表中第i个元素,并用e返回被删数的值
	eDeleteList()		删除线性表中值为e的元素
	GetElemList（）		用e返回线性表第i个元素的值
	LocateElemList（）	反回顺序表中第一个与element相等的元素的位序
	DeleteReList（）	删除有序线性表中的重复元素
	PrintfList（）		输出线性表中的元素
	

	此程序使用C语言完成，在调用函数的时候没有使用“&”，因为C语言不支持引用。但在一开始写的时候我使用的是“&”，这在编译器上可以编译成功并且运行。但是到OJ上或者在用C语言制作头文件时编译不会通过。因此，函数的调用是通过地址来实现的。也正因为如此，我才对指针的理解更加深入一些。
	
	14个函数中，有些函数不需要在main（）中输入值，直接把线性表的头地址传过去即可。比如：
	InitList(SqList *L)
	DestroyList(SqList *L)
	ClearList(SqList *L)
	EmptyList(SqList *L)
	LengthList(SqList *L)
	DeleteReList(SqList *L)
	PrintfList(SqList *L)
这些函数在调用时没有另外需要定义或者输入的值。而其它函数：
	CreateList(SqList *L,int n)	需要传入一个数据的多少值
	iInsertList(SqList *L,int i,ElemType e)	需要输入插入位置和插入的值
	iDeleteList(SqList *L,int i,ElemType *e)	需要输入删除位置和定义一个						接受删除元素的变量
	GetElemList(SqList *L,int i,ElemType *e)需要输入位置和定义接受返回						元素的变量
	LocateElemList(SqList *L,ElemType e)	需要输入比较的元素
	eInsertList(SqList *L,ElemType e,ElemType E) 需要数出插入值和插入位置值
	eDeleteList(SqList *L,ElemType e)	需要输入删除元素值
使用者可以按照程序的提醒来进行赋值。

	在使用功能时，可能有些功能在返回时没有提示，这表明使用者输入的不正确，或者不满足条件。

	程序的使用范围目前还不知道；有些bug目前我还不知道，在以后使用过程中解决。

