#include <stdio.h>
int count7(int n);
int main(void) {
	// your code goes here;
	int count=0,digit;
  printf("Enter the Digit:");
  scanf("%d",&digit);
  count = count7(digit);
  printf("7's ocuurances in %d is:%d",digit,count);
	return 0;
}
int count7(int n) {
int count = 0;
  if(n==7){
  count++;
 return count;
  }
 else if(n>7 && n<100)
  return count7(n/10)+count7(n%10);
  else if( n>100)
  return count7(n/10)+count7(n%10);
  else return 0;
}
