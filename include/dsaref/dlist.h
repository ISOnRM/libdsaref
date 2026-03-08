/* doubly linked list header */
#ifndef DLIST_H
#define DLIST_H

#include <stddef.h>
#include <stdint.h>    

typedef struct dlist_node {
    struct dlist_node *prev, *next;
    uint8_t *value;
} dlist_node;

typedef struct dlist { 
    dlist_node *nil;
    size_t elem_size;
} dlist;

/* lifecycle */
int dlist_init(dlist *l);
void dlist_destroy(dlist *l);

/* procedures (list) */
dlist_node *dlist_search(dlist *l, const void *data);
dlist_node *dlist_front(dlist *l);
dlist_node *dlist_back(dlist *l);
//int dlist_insert(dlist *l, dlist_node *n); (screw clrs)
int dlist_push_front(dlist *l, const void *value);
int dlist_push_back(dlist *l, const void *value);
int dlist_delete(dlist *l, dlist_node *n);
int dlist_append(dlist *a, dlist *b);
int dlist_reverse1(dlist *l);
int dlist_reverse2(dlist *l);


#endif /* DLIST_H */