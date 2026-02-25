// vec impl
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <string.h>

#include "dsaref/vec.h"

static int vec_realloc(vec *v, size_t new_cap) {
    if (!v || new_cap == 0) {
        errno = EINVAL;
        return -1;
    }

    void *t = realloc(v->data, new_cap * v->elem_size);
    if (!t) {
        errno = ENOMEM;
        return -1;
    }

    v->data = t;
    v->cap = new_cap;
    return 0;
}

int vec_init(vec *v, size_t elem_size) {
    if (!v || elem_size == 0) {
        errno = EINVAL;
        return -1;
    }

    v->cap = 0;
    v->len = 0;
    v->elem_size = elem_size;
    v->data = NULL;
    
    return 0;
}

void vec_destroy(vec *v) {
    if (!v) return;
    free(v->data);
    v->data = NULL;
    v->len = v->cap = v->elem_size = 0;
}

int vec_reserve(vec *v, size_t new_cap) {
    if (!v) { errno = EINVAL; return -1; }
    if (new_cap <= v->cap) return 0;
    return vec_realloc(v, new_cap);
}

int vec_shrink_to_fit(vec *v) {
    if (!v) { errno = EINVAL; return -1; }
    return vec_realloc(v, v->len);
}

void *vec_at(vec *v, size_t i) {
    if (!v)          { errno = EINVAL; return NULL; }
    if (i >= v->len) { errno = ERANGE; return NULL; }
    return (char *)v->data + i * v->elem_size;
}


const void *vec_cat(const vec *v, size_t i) {
    if (!v)          { errno = EINVAL; return NULL; }
    if (i >= v->len) { errno = ERANGE; return NULL; }
    return (const char *)v->data + i * v->elem_size;
}

void *vec_back(vec *v) {
    if (!v)          { errno = EINVAL; return NULL; }
    if (v->len == 0) { errno = ENOENT; return NULL; }
    return vec_at(v, v->len - 1);
}

void *vec_front(vec *v) {
    if (!v)          { errno = EINVAL; return NULL; }
    if (v->len == 0) { errno = ENOENT; return NULL; }
    return v->data;
}

int vec_push(vec *v, const void *elem) {
    if (!v || !elem) { errno = EINVAL; return -1; }

    if (v->len == v->cap) {
        size_t new_cap = (v->cap == 0) ? 2 : v->cap * 2;

        if (new_cap < v->cap || new_cap > SIZE_MAX / v->elem_size) {
            errno = EOVERFLOW;
            return -1;
        }
        if (vec_realloc(v, new_cap) != 0) return -1;
    }
    void *dst = (char*)v->data + v->len * v->elem_size;
    memcpy(dst, elem, v->elem_size);
    v->len++;
    return 0;
}


int vec_pop(vec *v, void *out) {
    if (!v)          { errno = EINVAL; return -1; }
    if (v->len == 0) { errno = ENOENT; return -1; }

    v->len--;
    if (out) {
        void *src = (char*)v->data + v->len * v->elem_size;
        memcpy(out, src, v->elem_size);
    }
    return 0;
}

