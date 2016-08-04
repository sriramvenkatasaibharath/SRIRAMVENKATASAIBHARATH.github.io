#include <stdio.h>

int main(void) {
int num,rem,sum=0;
printf("enter the number:");
scanf("%d",&num);
while(num!=0)
{
 rem=num%10;
 sum=sum*10+rem;
 num=num/10;
}
printf("Reversed Number is:%d",sum);	// your code goes here
	return 0;
}
