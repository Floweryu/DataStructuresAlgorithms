此程序包含了顺序栈的基本操作：
	构造一个空栈 	InitStack()
	清空栈		ClearStack()
	销毁栈		DestroyStack()
	判断栈是否为空	EmptyStack()
	返回元素的个数	LengthStack()
	返回栈顶元素	GetTopStack()
	插入元素到栈顶	PushStack()
	向栈里输入数据	CreateStack()
	删除栈顶元素	PopStack()
	输出栈		PrintfStack()

个人觉得，顺序栈没有链式栈操作起来方便，由于栈的最大容量已经定义，所以当容量不够用时还要申请空间。另外，在实现操作时也很麻烦，有些函数调用还有问题：
比如：
	我自己写的一次性输出栈里元素的函数，他只能在程序末尾使用，在他使用之后，其他函数不能接着在使用，否则会出bug。因为该函数在调用完成后栈顶指针已经指向栈底，在调用其它函数时也是如此，若想调用这个函数后还能继续使用其他函数，则需要把栈顶指针指到栈顶元素上。

注意：栈顶指针top是指向栈顶元素的上面，而不是栈顶元素。		