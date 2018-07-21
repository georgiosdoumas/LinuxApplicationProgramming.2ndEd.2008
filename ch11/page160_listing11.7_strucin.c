#include <stdio.h>
#include <stdlib.h>
#define FILENAME "myobjects.txt"
/*typedef struct
{
  int id;
  float x_coord;
  float y_coord;
  char name[MAX_LINE+1];
} MY_TYPE_T; */
#include "page158_listing11.6_7struct.h"

int main()
{
  FILE *fin;
  MY_TYPE_T object;
  fin = fopen( FILENAME, "r" );   /* Open the input file */
  if (fin == (FILE *)0) exit(-1);
  while ( !feof(fin) ) /* Read the records from the file and emit */
  {
    fscanf( fin, "%d %f %f %s\n", &object.id, &object.x_coord, &object.y_coord, object.name );
    printf("%d: %.2f %.2f %s\n", object.id, object.x_coord, object.y_coord, object.name );
  }
  fclose( fin );
  return 0;
}

/* gcc -Wall page160_listing11.7_strucin.c -o page160_listing11.7_strucin  */
