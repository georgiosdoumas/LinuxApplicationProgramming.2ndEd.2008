/* Including ideas form listing 31.2 as I tried to implement the syslog() 
* I also edited the macro CHECK_TARGET_MARKER and made a function instead, that 
* does not terminate the program but just writes on the file /var/log/messages */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <syslog.h>
// #define TARGET_MARKER_SIG 0xFAF32000
#define TARGET_MARKER_SIG 2
typedef struct {
  unsigned int signature;
  unsigned int targetType;
  double x, y, z;
} targetMarker_t;

#define INIT_TARGET_MARKER(ptr) (((targetMarker_t *)ptr)->signature = TARGET_MARKER_SIG)
//#define CHECK_TARGET_MARKER(ptr) assert(((targetMarker_t *)ptr)->signature == TARGET_MARKER_SIG)
int CHECK_TARGET_MARKER(targetMarker_t* ptr)
{
  if( ((targetMarker_t *)ptr)->signature == TARGET_MARKER_SIG )
    return 0;
  syslog( LOG_ERR, "passed object was not of proper type!" );
  return -1;
}

void displayTarget( targetMarker_t *target )
{
  if( CHECK_TARGET_MARKER(target) == 0 )    /* Pre-check of the target structure */
    printf( "Target type is %d\n", target->targetType );
  return;
}

int main()
{
  void *object1, *object2;   /* Create two objects */
  object1 = (void *)malloc( sizeof(targetMarker_t) );
  assert(object1);
  object2 = malloc( sizeof(targetMarker_t) );
  assert(object2);
  INIT_TARGET_MARKER(object1);      /* Init object1 as a target marker struct */
  displayTarget( (targetMarker_t *)object1 );  /* Try to display object1, it succeeds */
  displayTarget( (targetMarker_t *)object2 );  /* Try to display object2, a message is writen on /var/log/messages */
    // now lets create no a general pointer to void, but a pointer to a real targetMarker_t */
  targetMarker_t* marker = malloc( sizeof(targetMarker_t) );
  INIT_TARGET_MARKER(marker);      /* Init marker as a target marker struct is again required */
  marker->targetType = 3;
  displayTarget( marker) ;   /* Try to display marker, it succeeds  */
  return 0;
}

/* gcc -Wall page598_listing31.1_selfident.c -o page598_listing31.1_selfident */
/* execute, and check the /var/log/messages */
