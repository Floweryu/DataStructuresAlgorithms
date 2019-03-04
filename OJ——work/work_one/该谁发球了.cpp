#include<stdio.h>
#include<math.h>
int main()
{
    int A,B;
    while(scanf("%d %d",&A,&B)!=EOF)
	{
        if(A<=9&&B<=9)
		{
            if((A+B)%2==0)
			{
                if(((A+B)/2)%2==0)
                    printf("A\n");
                else
                    printf("B\n");
            }
            else
			{
                if(((A+B-1)/2)%2==0)
                    printf("A\n");
                else
                    printf("B\n");
            }
        }
        else
		{
            if((A==11&&B<=9)||(A<=9&&B==11))
                printf("Game Over\n");
            else if(A>=10&&B>=10)
            	{
            		if(abs(A-B)==2)
            		printf("Game Over\n");
           			else
					{
            		    if(((A+B)%20)%2==0)
          			 	    {
             				   	if((((A+B)%20)/2)%2==0)
             				   	printf("A\n");
              				  	else
                 				  printf("B\n");
							}
          			    else
						{
             				if((((A+B)%20-1)/2)%2==0)
          			        printf("A\n");
            			    else
             		       printf("B\n");
           				}
           			 }
     			}
   		 }
	}
}

