#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void usr2_handler( int sig_num )
{
  printf( "Process (%d) got the SIGUSR2\n", getpid() );
}

int main()
{
  pid_t ret;
  int status;
  int role = -1;
  signal( SIGUSR2, usr2_handler );
  ret = fork();
  if (ret > 0)
  {     /* Parent Context */
    printf( "Parent: This is the parent process (pid %d)\n", getpid() );
    role = 0;
    printf("I will pause now, and you should send me the SIGUSR2 by typing \nkill -12 %d \n", getpid());
    printf("But before you do that, just type ps to see current processes\n");
    pause();
    printf( "Parent: Awaiting child exit (type again ps to see)\n");
    printf( "You should sent to the child the same \nkill -12  %d\n", ret );
    ret = wait( &status );
  }
  else if (ret == 0)
  {     /* Child Context */
    printf( " Child: This is the child process (pid %d)\n", getpid() );
    role = 1;
    pause();
  }
  else {  /* Parent Context — Error */
    printf( "Parent: Error trying to fork() (%d)\n", errno );
  }
  printf( "%s: Exiting...\n", ((role == 0) ? "Parent" : " Child") );
  return 0;
}
/*
gcc -Wall page233_listing14.5_sigtest.c -o page233_listing14.5_sigtest
  run it as a background process and follow the instructions of the output text:
./page233_listing14.5_sigtest &
*/
