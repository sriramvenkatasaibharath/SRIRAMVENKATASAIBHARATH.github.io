#include<stdio.h>
#include<conio.h>
void main()
{
int upper,lower,i;
printf("enter the value upperand lower");
scanf("%d%d",&upper,&lower);
for(i=lower;i<upper;i++)
{
if(i%2!=0)
{
printf("%d",i);
}
}
getch();
} 