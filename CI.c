#include<stdio.h>
#include<math.h>
int main()
{
int p,n,t,r,ci;
float a,b,c;
scanf("%d %d %d %d ",&p,&t,&n,&r);
a=r/n;
c=1+a/100;

b=n*t;

ci=(int)p*(pow(c,b));

printf("output is %d",ci);
return 0;
}