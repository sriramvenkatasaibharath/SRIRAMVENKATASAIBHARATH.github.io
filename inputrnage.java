public class range{

public static void main(Stirng args[]){
int num;
System.out.println("enter the input vlaue");
Scanner scan = new Scanner(System.in);
num = scan.nextInt();
if(num>1&&num<9)
System.out.println(num);
else
System.out.println("Your Entered Number is Not in Range");
}
}