/* queue impl */

#include <asm-generic/errno-base.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "dsaref/queue.h"
#include "dsaref/vec.h"

#define nexti(i, c) (((i) + 1 == (c)) ? 0 : ((i) + 1))   /* incr or 0 */
#define previ(i, c) (((i) == 0) ? ((c) - 1) : ((i) - 1)) /* decr or last idx*/

int queue_init(queue *q, size_t elem_size, size_t cap) {
    if (!q || elem_size == 0 || cap == 0) { errno = EINVAL; return -1; }
    if (vec_init(&q->v, elem_size) != 0) return -1;
    if (vec_reserve(&q->v, cap) != 0) return -1;
    q->count = q->head = q->tail = 0;
    q->cap = cap;
    return 0; 
}

void queue_destroy(queue *q) {
    if (!q) return;
    vec_destroy(&q->v);
    q->cap = q->count = q->head = q->tail = 0;
}

int queue_empty(const queue *q) {
    if (!q) { errno = EINVAL; return -1; }
    return (q->count == 0) ? 1 : 0;
}


int queue_push_tail(queue *q, const void *elem) {
    if (!q || !elem)        { errno = EINVAL; return -1; }
    if (q->cap == q->count) { errno = ENOSPC; return -1; }

    size_t new_tail = q->tail;
    void *dst = vec_ptr(&q->v, new_tail);
    if (!dst)                          return -1;       
    memcpy(dst, elem, q->v.elem_size);
    
    new_tail = nexti(new_tail, q->cap);
    q->tail = new_tail;
    q->count++;

    return 0;
}

int queue_pop_head(queue *q, void *out) {
    if (!q) { errno = EINVAL; return -1; }
    if (q->count == 0)      { return -1; }
    size_t new_head = q->head;
    if (out) {
        void *src = vec_ptr(&q->v, new_head);
        if (!src)             return -1;       
        memcpy(out, src, q->v.elem_size);
    }

    new_head = nexti(new_head, q->cap);
    q->head = new_head;
    q->count--;

    return 0;
}

int queue_push_head(queue *q, const void *elem) {
    if (!q || !elem)        { errno = EINVAL; return -1; }
    if (q->cap == q->count) { errno = ENOSPC; return -1; }
    
    size_t new_head = q->head;
    new_head = previ(new_head, q->cap);
    void *dst = vec_ptr(&q->v, new_head);
    if (!dst) return -1;
    memcpy(dst, elem, q->v.elem_size);
    
    q->head = new_head;
    q->count++;

    return 0;
}

int queue_pop_tail(queue *q, void *out) {
    if (!q) { errno = EINVAL; return -1; }
    if (q->count == 0)      { return -1; }
    
    size_t new_tail = q->tail;
    new_tail = previ(new_tail, q->cap);

    if (out) {
        void *src = vec_ptr(&q->v, new_tail);
        if (!src) return -1;
        memcpy(out, src, q->v.elem_size);
    }

    q->tail = new_tail;
    q->count--;

    return 0;
}

int queue_clear(queue *q) {
    if (!q) { errno = EINVAL; return -1; }
    q->count = q->head = q->tail = 0;
    q->v.len = 0;
    return 0;
}

int queue_peek_head(queue *q, void *out) {
    if (!q || !out) { errno = EINVAL; return -1; }
    void *src = vec_ptr(&q->v, q->head);
    if (!src) return -1;
    memcpy(out, src, q->v.elem_size);
    return 0;
}


int queue_peek_tail(queue *q, void *out) {
    if (!q || !out) { errno = EINVAL; return -1; }
    size_t i = q->tail;
    i = previ(i, q->cap);
    void *src = vec_ptr(&q->v, i);
    if (!src) return -1;
    memcpy(out, src, q->v.elem_size);
    return 0;
}