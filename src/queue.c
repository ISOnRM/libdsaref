/* queue impl */

#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "dsaref/queue.h"

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


int queue_enq(queue *q, const void *elem) {
    if (!q || !elem) { errno = EINVAL; return -1; }
    if (q->cap == q->count)          { return -1; }
//  void *dst = (char*)q->v.data + q->tail * q->v.elem_size;
    void *dst = vec_ptr(&q->v, q->tail);
    if (!dst)                          return -1;       
    memcpy(dst, elem, q->v.elem_size);
    
    q->tail = (q->tail + 1) % q->cap;
    q->count++;

    return 0;
}
int queue_deq(queue *q, void *out) {
    if (!q) { errno = EINVAL; return -1; }
    if (q->count == 0)      { return -1; }
    if (out) {
//      void *src = (char *)q->v.data + q->head * q->v.elem_size;
        void *src = vec_ptr(&q->v, q->head);
        if (!src)             return -1;       
        memcpy(out, src, q->v.elem_size);
    }

    q->head = (q->head + 1) % q->cap;
    q->count--;

    return 0;
}
int queue_clear(queue *q) {
    if (!q) { errno = EINVAL; return -1; }
    q->count = q->head = q->tail = 0;
    q->v.len = 0;
    return 0;
}
