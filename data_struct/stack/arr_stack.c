
#define SIZE 10

typedef struct __stack {
    int size;
    int top;
    int arr[0];
} stack_t;

// allocate and init stack
stack_t *stack_create()
{
    stack_t *stack;
    stack = (stack_t*) malloc(sizeof(stack_t)+SIZE*sizeof(int));
    if (!stack) {
        printf("fail to create stack\n");
        return NULL;
    }

    stack->size = SIZE;
    stack->top = -1;
    return stack;
}

bool stack_is_empty(stack_t *stack)
{
    return (stack->top == -1);
}

bool stack_is_full(stack_t *stack)
{
    return (stack->top >= stack->size-1);
}

stack_t *stack_expend(stack_t *stack)
{
    stack_t *new;
    new = (stack_t*) malloc(sizeof(stack_t)+stack->size*2*sizeof(int));
    if (!new) {
        printf("fail to expend stack\n");
        return stack;
    }

    memcpy(new, stack, sizeof(stack_t)+stack->size*sizeof(int));
    new->size = 2*stack->size;
    free(stack);

    return new;
}

bool stack_push(stack_t **stack, int val)
{
    stack_t *new;
    if (stack_is_full(stack))
        new = stack_expend(*stack);

    if (new == stack) {
        printf("stack push failed\n");
        return -1;
    } else {
        stack = new;
    }

    stack->arr[++stack->top] = val;
    return 0;
}

int stack_pop(stack_t *stack, int *ret)
{
    if (stack_is_empty(stack)) {
        printf("stack pop failed\n");
        return -1;
    }

    *ret = stack->arr[stack->top--];
    return 0;
}

// return the top element without removing it
int stack_peek(stack_t *stack, int *ret)
{
    if (stack_is_empty(stack)) {
        printf("stack peek failed\n");
        return -1;
    }

    *ret = stack->arr[stack->top];
    return 0;
}

int main()
{
    
}
