/* queue using 2 stacks impl */

#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "dsaref/queue2.h"
#include "dsaref/stack.h"

int queue2_init(queue2 *q, size_t elem_size, size_t cap) {
    if (!q || elem_size == 0 || cap == 0) { errno = EINVAL; return -1; }
    if (stack_init(&q->s1, elem_size) != 0) return -1;
    if (stack_init(&q->s2, elem_size) != 0) return -1;
    q->count = 0;
    q->cap = cap;
    return 0; 
}

void queue2_destroy(queue2 *q) {
    if (!q) return;
    stack_destroy(&q->s1);
    stack_destroy(&q->s2);
}

int queue2_empty(const queue2 *q) {
    if (!q) { errno = EINVAL; return -1; }
    return (stack_empty(&q->s1) && stack_empty(&q->s2)) ? 1 : 0;
}

int queue2_clear(queue2 *q) {
    if (!q) { errno = EINVAL; return -1; }
    q->count = q->s1.count = q->s2.count = 0;
    return 0;
}

int queue2_push_tail(queue2 *q, const void *elem) {
    if (!q || !elem)        { errno = EINVAL; return -1; }
    if (q->cap == q->count) { errno = ENOSPC; return -1; }
    if (stack_push(&q->s1, elem) != 0) { return -1; }
    q->count++;
    return 0;
}

int queue2_pop_head(queue2 *q, void *out) {
    if (!q) { errno = EINVAL; return -1; }
    if (q->count == 0)      { return -1; }
    if (q->s2.count == 0) {
        void *t = NULL;
        while (q->s1.count != 0) {
            if (stack_pop(&q->s1, t) != 0) return -1;
            if (stack_push(&q->s2, t) != 0) return -1;
        }
    }
    
    if (out) {
        if (stack_pop(&q->s2, out) != 0) return -1;
    }
    
    return 0;
}

int queue2_peek_head(queue2 *q, void *out) {
    if (!q || !out) { errno = EINVAL; return -1; }
    if (stack_peek(&q->s2, out) != 0) return -1;
    return 0;

}