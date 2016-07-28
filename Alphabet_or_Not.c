#include<stdio.h>
#include<conio.h>
void main()
{
char character;
scanf(%c,&character);
if(character>='0'&&character<='9')
{
  printf("%c is number",character);
else
  printf("%c is character",character);
}
}