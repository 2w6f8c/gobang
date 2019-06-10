#ifndef GOBANG_STACK_H
#define GOBANG_STACK_H

#include <windows.h>

typedef POINT T;
typedef struct Node {
    T data;
    struct Node* next;
} Node, *Stack;

Stack newStack();

int isEmpty(Stack stack);

void push(Stack stack, T data);

T pop(Stack stack);

void freeStack(Stack stack);

#endif //GOBANG_STACK_H
