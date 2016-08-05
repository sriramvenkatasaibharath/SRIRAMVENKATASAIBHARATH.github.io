import java.util.*;
import java.lang.*;
import java.io.*;
class Ideone
{
	 public static void main(String[] args) {
	   String result = "";
       Scanner scan = new Scanner(System.in);
       String inString = scan.nextLine();
       //if (inString.length() == 0) {
           //return result;
       //}
       char firstChar = inString.charAt(0);
       char firstCharToUpperCase = Character.toUpperCase(firstChar);
       result = result + firstCharToUpperCase;
       for (int i = 1; i < inString.length(); i++) {
           char currentChar = inString.charAt(i);
           char previousChar = inString.charAt(i - 1);
           if (previousChar == ' ') {
               char currentCharToUpperCase = Character.toUpperCase(currentChar);
               result = result + currentCharToUpperCase;
           } else {
               char currentCharToLowerCase = Character.toLowerCase(currentChar);
               result = result + currentCharToLowerCase;
           }
       }
       System.out.println("Camel Case: " + result);
   }
}