#include<stdio.h>
#include<conio.h>
void main()
{
 int n,count=0,i;
clrscr();
printf("enter the number:");
scanf("%d",&n);
for(i=2;i<n/2;i++)
{
if(n%i==0)
{
count++;
}
}
if(count==0&&n!=1)
printf("Prime number");
else
printf("Non  Prime number");
getch();
}