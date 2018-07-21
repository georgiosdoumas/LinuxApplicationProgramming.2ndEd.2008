#include <stdio.h>
#include <stdlib.h>
#define FILENAME "myobjects.bin"
#include "page158_listing11.6_7struct.h"
#define MAX_OBJECTS 3

int main()
{
  MY_TYPE_T object;
  FILE *fin;
  fin = fopen( FILENAME, "r" );   /* Open the input file */
  if (fin == (FILE *)0) exit(-1);
  for(int i = MAX_OBJECTS; i > 0; --i)
  {
     if(i != 1) /* this test can be ommited and do the fseek even for i==1 */
       fseek( fin, ( (i-1) * sizeof(MY_TYPE_T)), SEEK_SET );
     fread( &object, sizeof(MY_TYPE_T), 1, fin );
     printf("%d %.2f %.2f %s\n", object.id, object.x_coord, object.y_coord, object.name );
     rewind( fin );
  }
  fclose( fin );
  return 0;
}

/* gcc -Wall page165_listing11.10_binin_nonseq.c -o page165_listing11.10_binin_nonseq */
