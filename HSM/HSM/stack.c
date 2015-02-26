
#include "stack.h"
#include <string.h>

void Stack_Init(Stack *stack)
{
	memset(stack->data,0,STACK_MAX);
    stack->size = 0;
}

int Stack_Top(Stack *stack)
{
	int data = 0;
    if (stack->size <= 0) {
#ifdef SYSTEM_SIMULATION
        fprintf(stderr, "Error: stack empty\n");
#endif
        return -1;
    } 
	data = stack->data[stack->size-1];
	Stack_Pop(stack);
    return data;
}

void Stack_Push(Stack *stack, unsigned int value)
{
	if (stack->size < STACK_MAX)
		stack->data[stack->size++] = value;
	else
	{
#ifdef SYSTEM_SIMULATION
		fprintf(stderr, "Error: stack full\n");
#endif
    }
}

void Stack_Pop(Stack *stack)
{
    if (stack->size <= 0)
	{
#ifdef SYSTEM_SIMULATION
        fprintf(stderr, "Error: stack empty\n");
#endif
    }
    else
        stack->size--;
}
