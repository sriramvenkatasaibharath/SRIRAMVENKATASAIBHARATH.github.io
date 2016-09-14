/* package whatever; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Ideone
{
	public static void main (String[] args) throws java.lang.Exception
	{
    Scanner scan = new Scanner(System.in);
    String reverse ="";
    String s = scan.nextLine();
    //String reverseString = s.reverse(); 
    String replaceString=s.replaceAll("[aeiouAEIOU]", "");
    int length = replaceString.length();
     for ( int i = length - 1 ; i >= 0 ; i-- )
         reverse = reverse + replaceString.charAt(i);
    System.out.println(reverse);
    }
}