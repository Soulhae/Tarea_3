#include <stdlib.h>
#include <stdio.h>

#ifndef _list_h
#define _list_h

typedef struct List Lista;
typedef Lista Stack;

/* stack operations */
Stack *createStack();
void pop(Stack* s);
void* top(Stack* s);
void push(Stack* s, void* data);
int is_empty(Lista* list);




#endif /* _list_h */