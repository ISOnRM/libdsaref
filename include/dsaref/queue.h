/* queue header */

#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include "dsaref/vec.h"

struct queue {
    size_t head, tail, count, cap;
    vec v;
};

typedef struct queue queue;

/* lifecycle */
int queue_init(queue *q, size_t elem_size, size_t cap); /* 0 or -1 */ 
void queue_destroy(queue *q);

/* enqueue and dequeue and clear */
int queue_push_tail(queue *q, const void *elem); /* 0 or -1 */ 
int queue_pop_head(queue *q, void *out);         /* 0 or -1 */ 

int queue_push_head(queue *q, const void *elem); /* 0 or -1 */ 
int queue_pop_tail(queue *q, void *out);         /* 0 or -1 */ 

int queue_clear(queue *q);                 /* 0 or -1 */ 

int queue_peek_head(queue *q, void *out); /* 0 or -1 */
int queue_peek_tail(queue *q, void *out); /* 0 or -1 */

/* fields */
#ifdef QUEUE_FIELDS_W_MACROS
#define queue_empty(q) (((q)-> count == 0) ? 1 : 0)
#else
int queue_empty(const queue *q);           /* 1/0 or -1 */ 
#endif

#endif /* QUEUE_ */