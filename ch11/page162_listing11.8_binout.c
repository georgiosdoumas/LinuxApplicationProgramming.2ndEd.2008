#include <stdio.h>
#include <stdlib.h>
#define FILENAME "myobjects.bin"
#include "page158_listing11.6_7struct.h"
#define MAX_OBJECTS 3

int main()
{
  MY_TYPE_T objects[MAX_OBJECTS]={
    { 0, 1.5, 8.4, "First-object" },
    { 1, 9.2, 7.4, "Second-object" },
    { 2, 4.1, 5.6, "Final-object" }
  };
  FILE *fout;
  fout = fopen( FILENAME, "w" );      /* Open the output file */
  if (fout == (FILE *)0) exit(-1);
/* Write out the entire object’s structure, and do it for all objects */
  fwrite( (void *)objects, sizeof(MY_TYPE_T), MAX_OBJECTS, fout );
  fclose( fout );
  printf("You can check the contents of file with: \n od -x %s \n", FILENAME);
  return 0;
}

/* gcc -Wall page162_listing11.8_binout.c -o page162_listing11.8_binout */
