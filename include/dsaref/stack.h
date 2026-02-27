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

/* fields */
#ifdef STACK_FIELDS_W_MACROS
#define stack_empty(s) (((s)->count == 0) ? 1 : 0)
#else
int stack_empty(const stack *s); // 1/0 or -1
#endif


#endif // STACK_H