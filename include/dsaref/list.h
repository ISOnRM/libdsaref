/* singly linked list header */
#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct list_node {
    struct list_node *next;
    unsigned char    *value;
} list_node;

typedef struct list {
    size_t elem_size;
    list_node *nil;
} list;

/* lifecycle */
int list_init(list *l, size_t elem_size);
void list_destroy(list *l);

/* nodes procedures */
list_node *list_search(list *l, const void *value);
int list_push_front(list *l, const void *value);
int list_pop_front(list *l, void *out);

/* algo */
int list_reverse(list *l);

#endif /* LIST_H */