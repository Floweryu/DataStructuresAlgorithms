int main()
{
	printf("******************************************************************\n");
	printf("*****        ���򴴽�һ����������Please enter 'a'          *****\n");
	printf("*****         ���ص�������ĳ��ȣ�Please enter   'b'         *****\n");
	printf("*****         ������������е����ݣ�Please enter 'c'         *****\n");
	printf("*****       �ж������Ƿ�Ϊ�գ�Please enter 'd'               *****\n");
	printf("*****       ���ظ���λ�õĽڵ�Ԫ��ֵ��Please enter 'e'       *****\n");
	printf("*****     ���ظ���Ԫ��ֵ�Ľڵ�λ�ã�Please enter 'f'         *****\n");
	printf("*****   ��������ָ��λ��i��֮ǰ���������ݣ�Please enter 'g'  *****\n");
	printf("*****   ɾ����i��Ԫ�أ�����e������ֵ��Please enter 'h'       *****\n");
	printf("*****        ���򴴽�һ����������Please enter 'i'          *****\n");
	printf("*****       ɾ�������������е��ظ�Ԫ�أ�Please enter 'j'   *****\n");
	printf("*****      �Ե���������������,  Please enter 'k'           *****\n");
	printf("******************************************************************\n");
	LNode L;
	char str;
	int N,I,k;
	ElemType E; 
	do
	{
		printf("\n");
		printf("Please enter a char:    ");
		str=getche();/*�Ӽ��̻�ȡһ���ַ�����ʾ�������س�ֱ��ִ��*/ 
		printf("\n");/*	getchar();	/*�����������Ļس���������س���Ҳ�ᱻ��Ϊ���ַ�*/ 
		switch(str)
		{
			case 'a':/* ���򴴽�һ����������*/
					{
						InitList(&L);
						printf("�����봴������ĳ��ȣ�  ");
						scanf("%d",&N);
						Create_L(&L,N);
						break;
					} 
			case 'b':/* ���ص�������ĳ���*/
					{
						k=Length_L(&L);
						printf("������ĳ����ǣ�  %d",k);
						break;
					}
			case 'c':/* ������������е�����*/
					{
						printf("�˵��������е�����Ϊ��\n");
						Printf_L(&L);
						break;
					} 
			case 'd':/* �ж������Ƿ�Ϊ��*/
					{
						k=Empty_L(&L);
						if(k)
						printf("����һ���յ�����\n");
						else
						printf("�ⲻ��һ���յ�����\n");
						break;
					}
			case 'e':/* ���ظ���λ�õĽڵ�Ԫ��ֵ*/
					{
						printf("����֪���ڼ���Ԫ�أ�   ");
						scanf("%d",&I);
						iGetElem_L(&L,I,&E);
						printf("��  %d  ��Ԫ�ص�ֵΪ��  %d\n",I,E);
						break;
					}
			case 'f':/*���ظ���Ԫ��ֵ�Ľڵ�λ��*/
					{
						printf("��������֪���Ƿ��������е���ֵ��  ");
						scanf("%d",&E);
						k=eGetElem_L(&L,E);
						if(k)
							printf("ֵΪ  %d  �Ǳ��еĵ�  %d  ��Ԫ��\n",E,k);
						else
							printf("��������û��ֵΪ%d��Ԫ��\n",E);
						break;
					 } 
			case 'g':/*��������ָ��λ��i��֮ǰ����������*/
					{
						printf("���������Ԫ�ص�λ�ã�  ");
						scanf("%d",&I);
						printf("���������Ԫ�ص�ֵ��  ");
						scanf("%d",&E);
						k=Insert_L(&L,I,&E);
						if(k)
						{
							printf("����������ֵΪ��\n");
							Printf_L(&L);
							printf("\n");
						 } 
						break; 
					 } 
			case 'h':/*ɾ����i��Ԫ�أ�����e������ֵ*/
					{
						printf("������ɾ��Ԫ�ص�λ�ã�  ");
						scanf("%d",&I);
						k=Delete_L(&L,I,&E);
						if(k)
						{
							printf("ɾ����λ�õ�Ԫ��ֵΪ:  %d\n",E);
							printf("ɾ�������Ա�Ϊ:\n");
							Printf_L(&L);
							printf("\n");
						}
							break;
					}
			case 'i':/* ���򴴽�һ����������*/
					{
						printf("�����봴������ĳ��ȣ�  ");
						scanf("%d",&N);
						reCreate_L(&L,N);
						break;
					} 
			case 'j':/*ɾ�������������е��ظ�Ԫ��*/
					{
						reDelete_L(&L);
						break;
					}
			case 'k':/*�Ե���������������*/
					{
						k=Length_L(&L);
						rePrintf_L(&L,k);
						break;
					}
			default:printf("wrong!\n");
		}
	}while(str!='q');
}
