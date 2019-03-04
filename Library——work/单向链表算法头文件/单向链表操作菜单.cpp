int main()
{
	printf("******************************************************************\n");
	printf("*****        正向创建一个单向链表，Please enter 'a'          *****\n");
	printf("*****         返回单向链表的长度，Please enter   'b'         *****\n");
	printf("*****         输出单向链表中的数据，Please enter 'c'         *****\n");
	printf("*****       判断链表是否为空，Please enter 'd'               *****\n");
	printf("*****       返回给定位置的节点元素值，Please enter 'e'       *****\n");
	printf("*****     返回给定元素值的节点位置，Please enter 'f'         *****\n");
	printf("*****   在链表中指定位置i在之前处插入数据，Please enter 'g'  *****\n");
	printf("*****   删除第i个元素，并由e返回其值，Please enter 'h'       *****\n");
	printf("*****        逆向创建一个单向链表，Please enter 'i'          *****\n");
	printf("*****       删除有序单向链表中的重复元素，Please enter 'j'   *****\n");
	printf("*****      对单链表进行逆序输出,  Please enter 'k'           *****\n");
	printf("******************************************************************\n");
	LNode L;
	char str;
	int N,I,k;
	ElemType E; 
	do
	{
		printf("\n");
		printf("Please enter a char:    ");
		str=getche();/*从键盘获取一个字符并显示，不按回车直接执行*/ 
		printf("\n");/*	getchar();	/*接收上条语句的回车键，否则回车键也会被认为是字符*/ 
		switch(str)
		{
			case 'a':/* 正向创建一个单向链表*/
					{
						InitList(&L);
						printf("请输入创建链表的长度：  ");
						scanf("%d",&N);
						Create_L(&L,N);
						break;
					} 
			case 'b':/* 返回单向链表的长度*/
					{
						k=Length_L(&L);
						printf("该链表的长度是：  %d",k);
						break;
					}
			case 'c':/* 输出单向链表中的数据*/
					{
						printf("此单向链表中的数据为：\n");
						Printf_L(&L);
						break;
					} 
			case 'd':/* 判断链表是否为空*/
					{
						k=Empty_L(&L);
						if(k)
						printf("这是一个空的链表。\n");
						else
						printf("这不是一个空的链表。\n");
						break;
					}
			case 'e':/* 返回给定位置的节点元素值*/
					{
						printf("你想知道第几个元素：   ");
						scanf("%d",&I);
						iGetElem_L(&L,I,&E);
						printf("第  %d  个元素的值为：  %d\n",I,E);
						break;
					}
			case 'f':/*返回给定元素值的节点位置*/
					{
						printf("输入你想知道是否在链表中的数值：  ");
						scanf("%d",&E);
						k=eGetElem_L(&L,E);
						if(k)
							printf("值为  %d  是表中的第  %d  个元素\n",E,k);
						else
							printf("此链表中没有值为%d的元素\n",E);
						break;
					 } 
			case 'g':/*在链表中指定位置i在之前处插入数据*/
					{
						printf("请输入插入元素的位置：  ");
						scanf("%d",&I);
						printf("请输入插入元素的值：  ");
						scanf("%d",&E);
						k=Insert_L(&L,I,&E);
						if(k)
						{
							printf("插入后链表的值为：\n");
							Printf_L(&L);
							printf("\n");
						 } 
						break; 
					 } 
			case 'h':/*删除第i个元素，并由e返回其值*/
					{
						printf("请输入删除元素的位置：  ");
						scanf("%d",&I);
						k=Delete_L(&L,I,&E);
						if(k)
						{
							printf("删除该位置的元素值为:  %d\n",E);
							printf("删除后线性表为:\n");
							Printf_L(&L);
							printf("\n");
						}
							break;
					}
			case 'i':/* 逆向创建一个单向链表*/
					{
						printf("请输入创建链表的长度：  ");
						scanf("%d",&N);
						reCreate_L(&L,N);
						break;
					} 
			case 'j':/*删除有序单向链表中的重复元素*/
					{
						reDelete_L(&L);
						break;
					}
			case 'k':/*对单链表进行逆序输出*/
					{
						k=Length_L(&L);
						rePrintf_L(&L,k);
						break;
					}
			default:printf("wrong!\n");
		}
	}while(str!='q');
}
