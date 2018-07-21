#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 10
int main()
{
  const char* filename = "testfile.txt";
  char line[LEN+1];
  FILE *fin;
  fin = fopen( filename, "r" );
  if ( fin == (FILE *)0 ) exit(-1);
  while ( (fgets( line, LEN-4, fin )) != NULL ) {
    printf("  We read %lu characters from file:",strlen(line));
    printf( "%s", line );
  }
  fclose( fin );
  return 0;
}

/* gcc -Wall page157_listing11.5_strin.c -o page157_listing11.5_strin */
