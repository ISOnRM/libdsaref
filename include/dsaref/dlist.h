/* doubly linked list header */
#ifndef DLIST_H
#define DLIST_H

#include <stddef.h>

typedef struct dlist_node {
    struct dlist_node *prev, *next;
    unsigned char *value;
} dlist_node;

typedef struct dlist {
    size_t elem_size;
    dlist_node *nil;
} dlist;

/* lifecycle */

int dlist_init(dlist *l, size_t elem_size);
void dlist_destroy(dlist *l);

/* node procedures */

dlist_node *dlist_search(dlist *l, const void *data);
int dlist_delete(dlist *l, dlist_node *n);
int dlist_push_back(dlist *l, const void *data);
int dlist_push_front(dlist *l, const void *data);
int dlist_pop_back(dlist *l, void *out);
int dlist_pop_front(dlist *l, void *out);

/* algo */

int dlist_reverse(dlist *l);

#endif /* DLIST_H */