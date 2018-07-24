#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

void* myThread( void* arg )
{
  int val;
  pthread_t pt = pthread_self();
  //printf(" Thread (%lu) will do a simple doubling of your input (you have 5 secs to give input)!\n", pt);
  printf(" Thread (%x) will do a simple doubling of your input (you have 5 secs to give input)!\n", (long int)pt);
  printf(" Enter an integer:");
  scanf("%d", &val);
  printf(" Your value doubled is %d \n  Thread will now exit\n", 2*val);
  pthread_exit( NULL );   /* Terminate the thread */
}

int main()
{
  int ret;
  pthread_t mythread;
  printf("Lets create a thread.\n");
  ret = pthread_create( &mythread, NULL, myThread, NULL );
  if (ret != 0) {
    printf( "Can’t create pthread (%s)\n", strerror( errno ) );
    exit(-1);
  }
  sleep(5);   /* This is important, to actually have time to see the thread execution, and give input */
  /* Instead of the above line with sleep, we could also use the following way : */
  /* pthread_join(mythread, NULL);  this is presented on page 260 and will be used thereafter */
  printf("Main program finishes now (after thread exited).\n");
  return 0;
}

/* gcc -Wall page257_listing15.1_2_ptcreate.c -o page257_listing15.1_2_ptcreate -lpthread */
