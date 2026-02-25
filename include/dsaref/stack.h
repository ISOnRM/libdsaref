// stack header
#ifndef STACK_H
#define STACK_H

#include "dsaref/vec.h"

struct stack {
    size_t count;
    vec v;
};

typedef struct stack stack;

/* lifecycle */
int stack_init(stack *s, size_t elem_size); // 0 or -1
void stack_destroy(stack *s);

/* elem procedures */
int stack_push(stack *s, const void *elem); // 0 or -1
int stack_pop(stack *s, void *out);         // out can be NULL, 0 or -1
int stack_peek(const stack *s, void *out);  // 0 or -1


#endif // STACK_H