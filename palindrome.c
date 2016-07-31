#include<stdio.h>
#include<conio.h>
void main()
{
int rem,n,rev=0,copy;
printf("enter the value of n");
scanf("%d",&n);
copy=n;
while(n>0)
{
rem=n%10;
n=n/10;
rev=rem*10+rev;
}
if(copy==rev)
{
 printf("palindrome");

}

getch();
}


