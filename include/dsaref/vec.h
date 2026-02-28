/* vec header */
#ifndef VEC_H
#define VEC_H

#include <stddef.h>

struct vec {
    size_t len, cap, elem_size;
    void *data;
};

typedef struct vec vec;

/* lifecycle */
int vec_init(vec *v, size_t elem_size); /* 0 or -1 */ 
void vec_destroy(vec *v);

/* cap management */
int vec_reserve(vec *v, size_t new_cap); /* 0 or -1 */ 
int vec_shrink_to_fit(vec *v);           /* 0 or -1 */ 

/* fields */
#ifdef VEC_FIELDS_W_MACROS /* just a little experiment; will remove later */
#define vec_empty(v) (((v)->len == 0) ? 1 : 0)
#else
int vec_empty(const vec *v); /* 1/0 or -1 */ 
#endif

/* ptr to elems */
void *vec_at(vec *v, size_t i);              /* ptr or NULL */ 
const void *vec_cat(const vec *v, size_t i); /* ptr or NULL */ 
void *vec_back(vec *v);                      /* ptr or NULL */ 
void *vec_front(vec *v);                     /* ptr or NULL*  */

/* push or pop elems */
int vec_push(vec *v, const void *elem);      /* 0 or -1 */ 
int vec_pop(vec *v, void *out);              /* 0 or -1 */ 

/* inteface for other data structures */
void *vec_ptr(vec *v, size_t i);


#endif /* VEC_H */ 
