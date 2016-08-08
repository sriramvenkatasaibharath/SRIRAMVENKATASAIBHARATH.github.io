import java.util.*;
import java.lang.*;
import java.io.*;
class Ideone
{
	public static void main (String[] args) throws java.lang.Exception
	{
      String day[] = {"sunday","monday","tuesday","wednesday","thursday","friday","saturday"};
      Scanner scan = new Scanner(System.in);
      String InputDay = scan.next();
      String LowerInputDay = InputDay.toLowerCase();
      System.out.println(LowerInputDay);
      if(LowerInputDay.equals("sunday")||LowerInputDay.equals("saturday"))
      {
      System.out.println("false");
      }
      else if(LowerInputDay.equals("monday")||LowerInputDay.equals("tuesday")||LowerInputDay.equals("wednesday")||LowerInputDay.equals("thursday")||LowerInputDay.equals("friday"))
      System.out.println("true");
else
System.out.println("please provide valid day.........");
	}


}
