#include "page562_listing29.2_stack.h"
#include <stdlib.h>
#include <stdio.h>

/* int failed;  */  /* here is an implementation that avoids this global variable */
void checkResult( int testnum, int result, int* pfailed , char* msg)
{
  if (result == 0) {
    printf( "*** Failed test number %d\n", testnum );
    (*pfailed)++;
  }
  else {
    printf( "Test number %2d passed. %s", testnum, msg );
  }
}

void test1( int* pfailed)
{
  stack_t myStack;
  char* scenario;
  int ret;
  *pfailed = 0;
  ret = stackCreate( NULL, 0 );   scenario = "creating an empty stack must fail\n";
  checkResult( 0, (ret == -1), pfailed, scenario );
  ret = stackCreate( &myStack, 0 );  scenario = "creating a stack of no length must fail\n";
  checkResult( 1, (ret == -1), pfailed, scenario );
  ret = stackCreate( &myStack, 65536 );  scenario = "creating a very big stack must fail\n";
  checkResult( 2, (ret == -1), pfailed, scenario );
  ret = stackCreate( &myStack, 1024 );  scenario = "creating the max-size stack must succeed\n";
  checkResult( 3, (ret == 0), pfailed, scenario );
  scenario = "status of the newly-created stack\n";
  checkResult( 4, (myStack.state == STACK_CREATED), pfailed, scenario );
  scenario = "new stack's index must be at the beginning\n";
  checkResult( 5, (myStack.index == 0), pfailed, scenario );
  scenario = "top element OK\n";
  checkResult( 6, (myStack.max == 1024), pfailed, scenario );
  scenario = "stack is non-empty\n";
  checkResult( 7, (myStack.storage != (int *)0), pfailed, scenario );
  ret = stackDestroy( NULL );  scenario = "destroying an empty stack must fail\n";
  checkResult( 8, (ret == -1), pfailed, scenario );
  ret = stackDestroy( &myStack );  scenario = "destroying the non-empty stack should be OK\n";
  checkResult( 9, (ret == 0), pfailed, scenario );
  scenario = "The destroyed stack should be in a non-created state\n";
  checkResult( 10, (myStack.state != STACK_CREATED), pfailed, scenario );
  if (*pfailed == 0) printf( "test1 passed.\n");  /* all 10 test cases succeeded ? */
  else printf("test1 failed\n");
}

int main()
{
  int failed = 0;
  test1(&failed);
  stack_t anotherstack;
  int stackElem;
  int result = stackCreate( &anotherstack, 8 );
  if(result == 0)
    for(int i=10; i < 50; i+=10)
      stackPush(&anotherstack, i);
  while( stackPop(&anotherstack, &stackElem) == 0 ){
      printf(" Poped out element : %d \n",stackElem);
  }
  return 0;
}

/* gcc -Wall page563_listing29.3_4_5_regress.c  page560_listing29.1_stack.c -o page563_listing29.3_4_5_regress */
