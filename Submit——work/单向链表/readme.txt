此程序包含了单向链表的基本操作

基本函数：12个

函数名称及其功能：
	Init_List()	初始化链表
	Create_List()	链表的正向创建
	reCreate_List()	逆序创建一个链表
	Printf_List()	打印输出链表中的数据
	Length_List()	返回链表的长度
	Empty_List()	判断链表是否为空
	iGetElem_List()	当第i个元素存在时将其值赋给e	
	eGetElem_List()	按值查找元素e
	Insert_List()	在指定位置前插入数据
	Delete_List()	删除第i个元素，并由e返回其值
	reDelete_List()	删除有序单向链表中重复的元素
	rePrintf_List()	对单向链表进行逆序输出

	此程序使用C语言完成，在调用函数的时候没有使用“&”，因为C语言不支持引用。但在一开始写的时候我使用的是“&”，这在编译器上可以编译成功并且运行。但是到OJ上或者在用C语言制作头文件时编译不会通过。因此，函数的调用是通过地址来实现的。也正因为如此，我才对指针的理解更加深入一些。

	12个函数中,有六个函数不需要在main()中输入数值，只需要传递链表的头地址即可。如下：
		Init_List(LNode *L)
		Printf_List(LNode *L)
		Length_List(LNode *L)
		Empty_List(LNode *L)
		reDelete_List(LNode *L)
		rePrintf_List(LNode *L)
	其他的需要在main（）中提供另外的值，才能调用函数，会在程序中有提示
		Create_List(LNode *L,int n)	需要输入创建数据的个数
		reCreate_List(LNode *L,int n)	需要输入创建数据的个数
		iGetElem_List(LNode *L,int i,ElemType &e)	需要输入得					到哪个位置的值和定义一个接受e值的变量
		eGetElem_L(LNode *L,ElemType &e)需要定义一个接受返回值得变						量
		Insert_List(LNode *L,int i,ElemType e)	需要输入插入值的位							置和插入的数值
		Delete_List(LNode *L,int i,ElemType &e)	需要输入删除值得位					置和定义一个接受返回中的变量

	在使用功能时，可能有些功能在返回时没有提示，这表明使用者输入的不正确，或者不满足条件。

	程序的使用范围目前还不知道；有些bug目前我还不知道，在以后使用过程中解决。


		