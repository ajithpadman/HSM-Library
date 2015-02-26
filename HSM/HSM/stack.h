#ifndef _STACK_H_
#define _STACK_H_
#ifdef SYSTEM_SIMULATION
#include <stdio.h>
#endif
#define STACK_MAX 10


typedef struct  {
    int     data[STACK_MAX];
    int     size;
}Stack;
void Stack_Init(Stack *stack);
int Stack_Top(Stack *stack);
void Stack_Push(Stack *stack, unsigned int value);
void Stack_Pop(Stack *stack);
#endif