/* doubly linked list impl */
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include "dsaref/dlist.h"

/* node procedures */
static int dlist_node_init(dlist_node *n, const void *value, size_t elem_size) {
    if (!n || !value || elem_size == 0) { errno = EINVAL; return -1; }
    n->prev = n->next = NULL;
    n->value = malloc(elem_size);
    if (!n->value) return -1;
    memcpy(n->value, value, elem_size);
    return 0;
}

static void dlist_node_destroy(dlist_node *n) {
    if (!n) return;
    n->prev = n->next = NULL;
    free(n->value);
}

int dlist_init(dlist *l) {
    if (!l) { errno = EINVAL; return -1; }
    l->nil->next = l->nil;
    l->nil->prev = l->nil;
    l->nil->value = NULL;
    return 0;
}

void dlist_destroy(dlist *l) {
    if (!l) return;
    dlist_node *n = l->nil->next;
    dlist_node *t;
    while (n != l->nil) {
        t = n->next;
        dlist_node_destroy(n);
        n = t;
    }
}

dlist_node *dlist_search(dlist *l, const void *value) {
    if (!l || !value) { errno = EINVAL; return NULL; }
    dlist_node *n = l->nil->next;
    while (n != l->nil && memcmp(n->value, value, l->elem_size) != 0) {
        n = n->next;
    }
    return n;
}

int dlist_delete(dlist *l, dlist_node *n) {
    if (!l || !n) { errno = EINVAL; return -1; }
    n->prev->next = n->next;
    n->next->prev = n->prev;
    dlist_node_destroy(n);
    return 0;
}

int dlist_push_front(dlist *l, const void *value) {
    if (!l || !value) { errno = EINVAL; return -1; }
    dlist_node n;
    if (dlist_node_init(&n, value, l->elem_size) != 0) return -1;
    n.next = l->nil->next;
    n.prev = l->nil;
    l->nil->next->prev = &n;
    l->nil->next = &n;
    return 0;
}

int dlist_push_back(dlist *l, const void *value) {
    if (!l || !value) { errno = EINVAL; return -1; }
    dlist_node n;
    if (dlist_node_init(&n, value, l->elem_size) != 0) return -1;
    n.next = l->nil;
    n.prev = l->nil->prev;
    l->nil->prev->next = &n;
    l->nil->prev = &n;
    return 0;
}

int dlist_append(dlist *a, dlist *b) {
    if (!a || !b) { errno = EINVAL; return -1; }
    a->nil->prev->next = b->nil->next;
    b->nil->prev->next = a->nil;
    b->nil->prev = b->nil->next = NULL;
    return 0;
}

dlist_node *dlist_front(dlist *l) {
    return l ? l->nil->next : NULL;
}

dlist_node *dlist_back(dlist *l) {
    return l ? l->nil->prev : NULL;
}

int dlist_reverse1(dlist *l) {
    if (!l) { errno = EINVAL; return -1; }
    dlist_node *prev = l->nil;
    dlist_node *curr = l->nil->next;
    dlist_node *next;
    while (curr != l->nil) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return 0;
}

int dlist_reverse2(dlist *l) {
    if (!l) { errno = EINVAL; return -1; }

    dlist_node *curr = l->nil;
    dlist_node *next;
    do {
        next = curr->next;
        curr->next = curr->prev;
        curr->prev = next;
        curr = next;
    } while (curr != l->nil);

    
    /* 
        nil [normal list] nil
           ^            ^   
           insert_a.    curr

        nil [reversed part] [normal list] nil
                           ^            ^
                           insert_a.    curr
    */

//  dlist_node *init_front = dlist_front(l);
//  dlist_node *nil = l->nil;
//  dlist_node *insert_after = nil;
//  dlist_node *curr = nil->prev;
//  dlist_node *next;
//  while (curr != init_front) {
//      next = curr->prev;
//      /* отвязать curr */
//      next->next = nil;
//      nil->prev = next;
//      /* привязать curr после insert_after */
//      curr->prev = insert_after;
//      curr->next = insert_after->next;
//      insert_after->next->prev = curr;
//      insert_after->next = curr;
//      /* изменить insert_after */
//      insert_after = curr;
//      /* изменить curr */
//      curr = next;
//  }

    return 0;
}