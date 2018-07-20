#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 10  /* max characters  allowed for a line to have */
int main()
{
  const char* filename = "testfile.txt";
  char line[LEN+1];   /* one more for the final termination \0 */
  FILE *fout, *fin;
  fout = fopen( filename, "w" );
  if ( fout == (FILE *)0 ) exit(-1);
  fin = fdopen( 0, "r" );  /* Associate filedescriptor 0 (stdin from console) with fin */
  printf("Enter text, line-by-line. \
          \nMake one of the lines with more than %d characters to see what happens.\n",LEN);
  while ( (fgets( line, LEN, fin )) != NULL ) {
    fputs( line, fout );
    printf("  a line of %lu characters will be writen to the file. Type another line or Ctrl+d to end\n",strlen(line));
  }
  fclose( fout );
  fclose( fin );
  return 0;
}
/* gcc -Wall page156_listing11.4_strout.c -o page156_listing11.4_strout */

/*  from man pages
fgets() reads in at most one less than size characters from stream and stores them into the buffer pointed to by s.
Reading stops after an EOF or a newline.  If a newline is read, it is stored into the buffer.
A terminating  null  byte  ('\0')  is stored after the last character in the buffer.
*/
