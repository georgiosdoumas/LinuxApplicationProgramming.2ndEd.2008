#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
  int pfds[2];
  if ( pipe(pfds) == 0 )  /* pipe was created OK */
  {  /* Data  can  be  written  to  the  file  descriptor  pfds[1] and read from the file descriptor pfds[0]. */
    if ( fork() == 0 )
    {     /* then we are in the child process */
      close(1);   /* close the stdout fd, since we will not output anything to stdout, but only to the pipe */
      dup2( pfds[1], 1 );
      close( pfds[0] );  /* since we will not use the read-from part of the pipe, we may close it */
      execlp( "ls", "ls", "-1", NULL );
    }
    else   /* we are in the parent process */
    {
      close(0);   /* close the stdin fd, since we will not receive from stdin, but only from the pipe */
      dup2( pfds[0], 0 ); /* stdin was related to something, now the read-from part of the pipe is related with it */
      close( pfds[1] );  /* since we will not use the write-to part of the pipe, it is good to close it */
      execlp( "wc", "wc", "-l", NULL );
    }
  }
  else printf("Failed to create the pipe!\n");
  return 0;
}

/* gcc -Wall page180_listing12.3_dup.c -o page180_listing12.3_dup */
