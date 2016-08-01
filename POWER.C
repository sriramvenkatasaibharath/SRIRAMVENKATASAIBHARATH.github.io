#include<stdio.h>
#include<math.h>
#include<conio.h>
void main()
{
 int num,power,res;
 clrscr();
 printf("enter the number:");
 scanf("%d",&num);
 printf("enter the power:");
 scanf("%d",&power);
 res=pow(num,power);
 printf("result:%d",res);
 getch();
}