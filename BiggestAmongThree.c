#include<stdio.h>
#include<conio.h>
void main()
{
 int a[3],biggest=0,i;
 printf("enter the values :");
 for(i=0;i<3;i++)
 scanf("%d",&a[i]);
 for(i=0;i<3;i++)
{
  if(biggest>a[i])
  biggest=a[i];
}
printf("Biggest values is:%d",biggest);
}