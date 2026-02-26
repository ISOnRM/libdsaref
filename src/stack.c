// stack impl
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "dsaref/stack.h"
#include "dsaref/vec.h"

int stack_init(stack *s, size_t elem_size) {
    if (!s || elem_size == 0) { errno = EINVAL; return -1; }
    if (vec_init(&s->v, elem_size) != 0) return -1;
    s->count = 0;
    return 0;
}

void stack_destroy(stack *s) {
    if (!s) return;
    vec_destroy(&s->v);
    s->count = 0;
}

int stack_push(stack *s, const void *elem) {
    if (!s || !elem) { errno = EINVAL; return -1; }
    if (vec_push(&s->v, elem) != 0 )   return -1;
    s->count++;
    return 0;
}

int stack_pop(stack *s, void *out) {
    if (!s)            { errno = EINVAL; return -1; }
    if (s->count == 0) { errno = ENOENT; return -1; }
    if (vec_pop(&s->v, out) != 0)        return -1;
    s->count--;
    return 0;
}

int stack_peek(const stack *s, void *out) {
    if (!s || !out) { errno = EINVAL; return -1; }
    const void *src = vec_cat(&s->v, s->v.len-1);
    if (!src)       { errno = ENOENT; return -1; }
    memcpy(out, src, s->v.elem_size);
    return 0;
}

int stack_empty(const stack *s) {
    if (!s) { errno = EINVAL; return -1; }
    return (s->count == 0) ? 1 : 0;
}