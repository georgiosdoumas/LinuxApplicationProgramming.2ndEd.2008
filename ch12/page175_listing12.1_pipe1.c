#include <unistd.h>   /* ssize_t write(int fildes, const void *buf, size_t nbyte);   int pipe(int fildes[2]); */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#define MAX_LINE 80
#define APP_STDIN 0
#define APP_STDOUT 1

int main()
{
  const char* string={"A sample message."};
  int ret, myPipe[2];
  char buffer[MAX_LINE+1];
  ret = pipe( myPipe );   /* Create the pipe */
  /* Data  can  be  written  to  the  file  descriptor  myPipe[1] and read from the file descriptor myPipe[0]. */
  if (ret == 0)  /* successfully created pipe ? */
  {
    write( myPipe[APP_STDOUT], string, strlen(string) );   /* Write the message into the pipe */
    ret = read( myPipe[APP_STDIN], buffer, MAX_LINE );   /* Read the message from the pipe */
    buffer[ ret ] = '\0';      /* Null terminate the string */
    printf("%s\n", buffer);
  }
  else {
    printf("Failed to create pipe. %d \n", errno);
  }
  return 0;
}

/* gcc -Wall page175_listing12.1_pipe1.c -o page175_listing12.1_pipe1 */
