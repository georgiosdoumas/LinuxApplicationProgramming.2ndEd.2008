#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#define MAX_LINE 80

int main()
{
  int thePipe[2], ret;
  char buf[MAX_LINE+1];
  const char *testbuf={"a test string."};
  if ( pipe( thePipe ) == 0 )   /* Create the pipe and check if the creation was successful */
  {
    if (fork() == 0)  /* then we are in the child */
    {
      printf("   Inside child, we will read from pipe.\n");
      ret = read( thePipe[0], buf, MAX_LINE );
      buf[ret] = 0;
      printf("   Child read: %s\n", buf );
    }
    else      /* we are in the parent */
    {
      printf("Inside parent we will write to pipe.");
      ret = write( thePipe[1], testbuf, strlen(testbuf) );
      /* putchar('\n'); */ /* uncomment this line, comppile and run again to see different behavior */
      ret = wait( NULL );
    }
  }
  printf("Finish! But it is good practice to explicitly close the 2 pipes before we go.\n");
  close( thePipe[0] );
  close( thePipe[1] );
  return 0;
}

/* gcc -Wall page178_listing12.2_fpipe.c -o page178_listing12.2_fpipe */

