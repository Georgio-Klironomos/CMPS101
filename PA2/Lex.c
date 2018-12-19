//-----------------------------------------------------------------------------
// FileIO.c
// Illustrates file input-output commands and text processing using the
// string functions strtok and strcat.
//-----------------------------------------------------------------------------
//Works Cited
//https://www.tutorialspoint.com/c_standard_library/c_function_calloc.htm
//https://en.cppreference.com/w/cpp/language/operator_incdec
//https://www.tutorialspoint.com/c_standard_library/c_function_strcmp.htm
//https://classes.soe.ucsc.edu/cmps101/Fall18/Examples/C/FileIO/FileIO.c
//http://www.siafoo.net/snippet/75
//https://www.cs.bu.edu/teaching/c/file-io/intro/
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 1002 //just in case

int main(int argc, char * argv[]) {
  int count = 0;
  int size = 0;
  FILE *pre, *post;
  char line[MAX_LEN];
  char* preLex[MAX_LEN];
  List postLex = newList();
    
  if( argc != 3 ) {
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }
   
  pre = fopen(argv[1], "r");
  post = fopen(argv[2], "w");

  if( pre==NULL || post==NULL ) {
    printf("Unable to open file %s for reading and/or writing\n", argv[1]);
    exit(1);
  }
   
  while( fgets(line, MAX_LEN, pre) != NULL)  {
    size++; //count how many spaces for preLex are needed
  }

  rewind(pre);//this is so useful and kinda hilarious

  for(int i = 0; i<=size; i++) {preLex[i] = calloc(1, sizeof(char* [MAX_LEN]));}//allocate the spaces for preLex
    
  while(  fgets(line, MAX_LEN, pre) != NULL) {
    if(line[strlen(line) - 1] == '\n') {line[strlen(line) - 1] = 0;} //ensures no newline fuckups
    strcpy(preLex[count++], line);//copies the shaven lines into preLex
  }

  append(postLex, 0); //insert whatever the first word is so we have something to compare to.   
  //I'm amazed at how seamless my java algorithm translated
  for(int k = 1; k < size; k++) { //for the rest of the words in our string array.
    moveFront(postLex); //like a typewriter, we slide back to the front.
    while(index(postLex) >= 0) { //and compare until the back.
      if(strcmp(preLex[k], preLex[get(postLex)]) >= 0) {moveNext(postLex);} //checks to see if we even need to stop
      else{ //if we stop, then we know to put this current word before the cursor.
        insertBefore(postLex, k);
        break;//I geuss this worked, weird
      }
    }
    if(index(postLex) < 0) {append(postLex, k);}//if we reached the end of the list, then we'll place this in the back.
  }

  moveFront(postLex);//Like a typrewriter, set the cursor back to the front
	for (int i = 0; i < (length(postLex)); i++){ //increment through the entire list
		fprintf(post,"%s\n",preLex[get(postLex)]); //The most important line of code
    moveNext(postLex); // the next most important line of code (lol)
	}
  
   
  fclose(pre);
  fclose(post);
	freeList(&postLex);
	for(int i = 0; i<=size; i++) {free(preLex[i]);}
  //get rid of any troublesome leakage
  return(0);
}