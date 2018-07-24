#include <pthread.h>
#include <stdio.h>
#define MAX_THREADS 5

void *myThread( void *arg )
{
  printf( " Thread %d started, it has ID %lu \n", (int)arg , pthread_self() );
  pthread_exit( arg );
}

int main()
{
  int ret, i, status;
  pthread_t threadIds[MAX_THREADS];
  for (i = 0 ; i < MAX_THREADS ; i++)  /* the book has 2 for loops, but I put all actions in one, to have a more logical output */
  {
    ret = pthread_create( &threadIds[i], NULL, myThread, (void *)i );
    if (ret != 0) {
      printf( "Error creating thread %d\n", (int)threadIds[i] );
    }
    ret = pthread_join( threadIds[i], (void **)&status );
    if (ret != 0) {
      printf( "Error joining thread %d\n", (int)threadIds[i] );
    }
    else {
      printf( "Status = %d\n", status );
    }
  }
  return 0;
}

/* gcc -Wall page260_listing15.5_ptjoin.c -o page260_listing15.5_ptjoin -lpthread */
