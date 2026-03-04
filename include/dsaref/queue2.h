/* queue using 2 stacks header */
#ifndef QUEUE2_H
#define QUEUE2_H

#include <stddef.h>
#include "dsaref/stack.h"

struct queue2 {
    size_t count, cap;
    stack s1, s2;
};

typedef struct queue2 queue2;

/* lifecycle */
int queue2_init(queue2 *q, size_t elem_size, size_t cap); /* 0 or -1 */ 
void queue2_destroy(queue2 *q);


/* enqueue and dequeue and clear */
int queue2_push_tail(queue2 *q, const void *elem); /* 0 or -1 */ 
int queue2_pop_head(queue2 *q, void *out);         /* 0 or -1 */ 

int queue2_clear(queue2 *q); /* 0 or -1 */

int queue2_peek_head(queue2 *q, void *out);

/* fields*/
int queue2_empty(const queue2 *q); /* 1/0 or -1 */


#endif /* QUEUE2_H */