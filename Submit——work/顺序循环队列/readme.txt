这是一个顺序队列的程序。
	结构体定义的名称：SqQueue
			typedef int Status;
			typedef int QElemType;
	函数名称按习惯。
	

	程序的不足：队列的最大容量在程序开头已经定义，如果在使用时所需要的容量比之大，则需要重新定义一个更大的容量。
	此程序用的是队尾指针指向最后一个元素的下一个位置的方法，这样可以判空，但在存储数据时要注意的是，实际的最大容量要比定义的MAX_SIZE小一，因为最后一个空间空出。
	按'q'退出程序。