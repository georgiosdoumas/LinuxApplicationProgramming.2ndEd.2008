//#define STACK_CREATED 0xFAF32000  /* I do not know why the book uses this big hex number */
#define STACK_CREATED 1   /* we can use any number practically, so I chose this */
#define MAX_STACK_SIZE 1024
typedef struct {
  int state;
  int index;
  int max;   /* the top element , last inserted first to be poped-out */
  int *storage;
} stack_t;

int stackCreate( stack_t *stack, int stackSize );
int stackPush( stack_t *stack, int element );
int stackPop( stack_t *stack, int *element );
int stackDestroy( stack_t *stack );
