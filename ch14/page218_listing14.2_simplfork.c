#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
int main()
{
  pid_t ret;
  int status, i;
  int role = -1;
  ret = fork();
  if (ret > 0)
  {
    printf("Parent: This is the parent process (pid %d)\n", getpid());
    for (i = 0 ; i < 5 ; i++)
    {
      printf("Parent: At count %d\n", i);
      sleep(1);
    }
    ret = wait( &status );
    ++role; /* role = 0; */
    printf("Parent sets role to : %d \n", role);
  }
  else if (ret == 0)
  {
    printf("  Child: This is the child process (pid %d)\n", getpid());
    for (i = 0 ; i < 7 ; i++)  /* good to try it with a value of i<3 to see the different behavior */
    {
      printf("  Child: At count %d\n", i);
      sleep(1);
    }
    --role;/* role = -1; */
    printf("  Cild sets role to : %d \n", role);
  } else {
    printf("Parent: Error trying to fork() (%d)\n", errno);
  }
  printf("%s: Exiting...\n", ((role == 0) ? "Parent" : "Child"));
  return 0;
}

/* gcc -Wall page218_listing14.2_simplfork.c -o page218_listing14.2_simplfork */
