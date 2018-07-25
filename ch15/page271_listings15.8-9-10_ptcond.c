#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h> /* for random() */
#include <unistd.h> /* for sleep() , in case we use it for a more slow output */
#define MAX_CONSUMERS 5
#define MAX_WORKSTEPS 20
pthread_mutex_t cond_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
int workCount = 0;

void *producerThread( void *arg )
{
  int i, j, ret;
  double result=0.0;
  printf("Producer started\n");
  for ( i = 0 ; i < MAX_WORKSTEPS ; i++ )
  {
    ret = pthread_mutex_lock( &cond_mutex );
    if (ret == 0)
    {
      /* ++workCount; */
      workCount += 3 ;
      printf( "Producer: Created workload (%d)\n", workCount );
      pthread_cond_broadcast( &condition );
      pthread_mutex_unlock( &cond_mutex );
    }
    else {
      assert(0);
    }
    for ( j = 0 ; j < 6000 ; j++ ) {
      result = result + (double)random();
    }
  }
  printf("Producer finished\n");
  pthread_exit( NULL );
}

void *consumerThread( void *arg )
{
  pthread_detach( pthread_self() );
  printf( "  Consumer %lu: Started\n", pthread_self() );
  while( 1 )
  {
    assert( pthread_mutex_lock( &cond_mutex ) == 0);
    assert( pthread_cond_wait( &condition, &cond_mutex ) == 0 );
    if (workCount)
    {
      --workCount;
      printf( "  Consumer %lu: Performed reduction of workcount to: %d\n", pthread_self(), workCount );
    }
    else {
      printf("  (no workload) Relaxing for some millisecs ... \n");
      //sleep(1);   // uncomment it for a slower output 
    }
    assert( pthread_mutex_unlock( &cond_mutex ) == 0);
  }
  printf( "  Consumer %lu: Finished\n", pthread_self() );
  pthread_exit( NULL );
}

int main()
{
  int i;
  pthread_t consumers[MAX_CONSUMERS];
  pthread_t producer;
  for ( i = 0 ; i < MAX_CONSUMERS ; i++ )
  {    /* Spawn the consumer thread */
    pthread_create( &consumers[i], NULL, consumerThread, NULL );
  }
  pthread_create( &producer, NULL, producerThread, NULL ); /* Spawn the single producer thread */
  pthread_join( producer, NULL );   /* Wait for the producer thread */
  while ((workCount > 0))
    ;
  for ( i = 0 ; i < MAX_CONSUMERS ; i++ )
  {     /* Cancel and join the consumer threads */
    pthread_cancel( consumers[i] );
  }
  pthread_mutex_destroy( &cond_mutex );
  pthread_cond_destroy( &condition );
  return 0;
}

/* gcc -Wall page271_listings15.8-9-10_ptcond.c  -o page271_listings15.8-9-10_ptcond -lpthread */
