//-----------------------------------------------------------------------------
// Georgio Klironomos
// gklirono
// Programming Assignment 1
// Alphabetizes an input file creating a List of their sorted array indices
//-----------------------------------------------------------------------------
//WORKS CITED
//https://classes.soe.ucsc.edu/cmps101/Fall18/Examples/Java/FileIO/FileIO.java
//https://docs.oracle.com/javase/7/docs/api/java/util/Scanner.html
//https://stackoverflow.com/questions/1277880/how-can-i-get-the-count-of-line-in-a-file-in-an-efficient-way

import java.io.*;
import java.util.Scanner;
   
public class Lex{
  public static void main(String[] args) throws IOException{
    if(args.length < 2){ //ensures there are at least 2 arguments.
      System.err.println("stderr");
      System.exit(1);
    }
    Scanner in1 = null; //one for counting,
    Scanner in2 = null; //one for reading,
    PrintWriter out = null; //and one last one for writing.
    int i = 0; //general use counter.
  
    try{ // making sure there's stuff in the files.
      in1 = new Scanner(new File(args[0]));
      in2 = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));
      }catch(Exception e){
        System.out.println(e);
        System.exit(1);
    }
    while( in1.hasNextLine() ){ //counts the # of lines in the input file.
        i++;
        in1.nextLine();
    }
    in1.close(); //a good habit to get into.
    String[] preLex = new String[i]; //create a string array w/ a re-specified size to place the words in.
    for(int j = 0; j < preLex.length; j++){ //filling the tring array, word by word.
      preLex[j] = in2.nextLine();
    }
    in2.close(); //I think this prevents hacking, or data loss, or something.
    List postLex = new List(); //The premiere of my beuautiful, handcrafted ADT    postLex.append(0);//prepend, maybe
    postLex.append(0); //insert whatever the first word is so we have something to compare to.   
    for(int k = 1; k < preLex.length; k++){ //for the rest of the words in our string array.
      postLex.moveFront(); //like a typewriter, we slide back to the front.
      while(postLex.index() >= 0) { //and compare until the back.
        if(preLex[k].compareTo(preLex[postLex.get()]) >= 0) { //checks to see if we even need to stop.
          postLex.moveNext();
        }
        else{ //if we stop, then we know to put this current word before the cursor.
        postLex.insertBefore(k);
        break;//I geuss this worked, weird
        }
      }
      if(postLex.index() < 0){ //if we reached the end of the list, then we'll place this in the back.
        postLex.append(k);
      }
    }
    postLex.moveFront(); //we slide the cursor back to the front and prepare to spit it all out.
    for(int m = 0; m < i; m++) {
      out.print(preLex[postLex.get()]); //this is where the magic happens.
      postLex.moveNext();
      if(postLex.index()>=0){ //this ensures an extra blank line isn't written.
        out.println();
      }
    }
    out.close(); // that's all folks.
  }
}
