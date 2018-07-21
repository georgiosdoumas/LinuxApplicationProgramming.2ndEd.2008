#include <stdio.h>
#include <stdlib.h>
#define FILENAME "myobjects.txt"
#include "page158_listing11.6_7struct.h"
#define MAX_OBJECTS 3
/* Initialize an array of three objects */
MY_TYPE_T objects[MAX_OBJECTS]={
  { 0, 1.5, 8.4, "First-object" },
  { 1, 9.2, 7.4, "Second-object" },
  { 2, 4.1, 5.6, "Final-object" }
};

int main()
{
  int i;
  FILE *fout;
  fout = fopen( FILENAME, "w" );    /* Open the output file */
  if (fout == (FILE *)0) exit(-1);
  for ( i = 0 ; i < MAX_OBJECTS ; i++ )   /* Emit each of the objects, one per line */
  {
    fprintf( fout, "%d %f %f %s\n", objects[i].id, objects[i].x_coord, objects[i].y_coord, objects[i].name );
  }
  fclose( fout );
  return 0;
}

/* gcc -Wall page158_listing11.6_strucout.c -o page158_listing11.6_strucout  */
