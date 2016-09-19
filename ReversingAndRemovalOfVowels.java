

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Ideone
{
	public static void main (String[] args) throws java.lang.Exception
	{
      String original, reverse = "";
      Scanner in = new Scanner(System.in);
      System.out.println("Enter a string to reverse");
      original = in.nextLine();
      int length = original.length();
      for ( int i = length - 1 ; i >= 0 ; i-- )
      {
         reverse = reverse + original.charAt(i);
      }   
 
      System.out.println(reverse);
      System.out.println(reverse.replaceAll( "[aeiou]", "" ));
	}
}