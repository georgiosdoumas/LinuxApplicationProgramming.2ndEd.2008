#include "page562_listing29.2_stack.h"
#include <stdlib.h>

int stackCreate( stack_t *stack, int stackSize )
{
  if ((stackSize < 1) || (stackSize > MAX_STACK_SIZE)) return -1;
  stack->storage = (int *)malloc( sizeof(int) * stackSize );
  if (stack->storage == (void *)0)  /* failed to allocate requested memory? */
    return -1;
  stack->state = STACK_CREATED;
  stack->max = stackSize;
  stack->index = 0;  /* current element that we deal  with */
  return 0;
}

int stackPush( stack_t *stack, int element )
{
  if (stack == (stack_t *)NULL) return -1;
  if (stack->state != STACK_CREATED) return -1;
  if (stack->index >= stack->max) return -1; /* do not insert elements on full stacks! */
  stack->storage[stack->index++] = element;
  return 0;
}

int stackPop( stack_t *stack, int *element )
{
  if (stack == (stack_t *)NULL) return -1;
  if (stack->state != STACK_CREATED) return -1;
  if (stack->index == 0) return -1;
  *element = stack->storage[--stack->index];
  return 0;
}

int stackDestroy( stack_t *stack )
{
  if (stack == (stack_t *)NULL) return -1;
  if (stack->state != STACK_CREATED) return -1;
  stack->state = 0;
  free( (void *)stack->storage );
  return 0;
}
