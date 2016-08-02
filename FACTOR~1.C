#include<stdio.h>
#include<conio.h>
int factorial(int n);
void main()
{
 int n,res=1;
 printf("enter the number");
 scanf("%d",&n);
 res=factorial(n);
 printf("factorial:%d",res);
 getch();
}
int factorial(int n)
{
 if(n>1)
 return n*factorial(n-1);
 else
 return 1;
}