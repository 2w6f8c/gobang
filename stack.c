#include "stack.h"

Stack newStack() {
    Stack stack = NULL;
    stack = (Stack) malloc(sizeof(Node));
    if (stack == NULL) exit(0);
    stack->next = NULL;
}

int isEmpty(Stack stack) {
    if(!stack) return 1;
    return stack->next == NULL;
}

void push(Stack stack, T data) {
    Node* node = NULL;
    node = malloc(sizeof(Node));
    if(node == NULL) exit(0);
    node -> next = stack -> next;
    node -> data = data;
    stack -> next = node;
}

T pop(Stack stack) {
    if(stack -> next == NULL) exit(0);
    Node* node = stack->next;
    stack -> next = node -> next;
    T data = node -> data;
    free(node);
    return data;
}

void freeStack(Stack stack) {
    if(!stack) return;
    while(!isEmpty(stack)) {
        pop(stack);
    }
    free(stack);
}