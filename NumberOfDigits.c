#include<stdio.h>
#include<conio.h>
void main()
{
 int i=0,num;
 clrscr();
 printf("enter the number:");
scanf("%d",&num);
 while(num!=0)
 {
  num=num/10;
  i++;
 }
 printf("%d",i);
 getch();
}