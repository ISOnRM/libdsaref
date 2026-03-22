/* doubly linked list impl */
#include "dsaref/dlist.h"
#include <asm-generic/errno-base.h>
#include <stdlib.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>

/* helpers */

static dlist_node *dlist_node_create(const void *value, size_t elem_size) {
	if (elem_size == 0) {
		errno = EINVAL;
		return NULL;
	}

    dlist_node *n = malloc(sizeof *n);
	if (!n) {
		errno = ENOMEM;
		return NULL;
	}

    if (value) {
        n->value = malloc(elem_size);
        if (!n->value) {
            errno = ENOMEM;
            free(n);
            return NULL;
        }
        memcpy(n->value, value, elem_size);
    } else {
        n->value = NULL;
    }

    n->prev = n->next = NULL;

    return n;
}

static void dlist_node_free(dlist_node *n) {
    if (n) {
        n->prev = n->next = NULL;
        free(n->value);
        free(n);
    }
}

int dlist_init(dlist *l, size_t elem_size) {
    if (!l || elem_size == 0) {
        errno = EINVAL;
        return -1;
    }

    dlist_node *nil = dlist_node_create(NULL, elem_size);
    if (!nil) return -1;

    l->elem_size = elem_size;
    l->nil = nil;
    l->nil->prev = l->nil;
    l->nil->next = l->nil;

    return 0;
}

void dlist_destroy(dlist *l) {
    if (l) {
        dlist_node *curr = l->nil->next;
        dlist_node *next;
        while (curr != l->nil) {
            next = curr->next;
            dlist_node_free(curr);
            curr = next;
        }
        dlist_node_free(l->nil);
        l->elem_size = 0;
        l->nil = NULL;
    }
}

dlist_node *dlist_search(dlist *l, const void *value) {
    if (!l || !value) {
        errno = EINVAL;
        return NULL;
    }

    dlist_node *curr = l->nil->next;
    while (curr != l->nil) {
        if (memcmp(curr->value, value, l->elem_size) == 0) return curr;
        curr = curr->next;
    }
    return NULL;
}

int dlist_push_back(dlist *l, const void *value) {
    if (!l || !value) {
        errno = EINVAL;
        return -1;
    }

    dlist_node *n = dlist_node_create(value, l->elem_size);
    if (!n) return -1;

    n->next = l->nil;
    n->prev = l->nil->prev;
    l->nil->prev->next = n;
    l->nil->prev = n;

    return 0;
}

int dlist_push_front(dlist *l, const void *value) {
    if (!l || !value) {
        errno = EINVAL;
        return -1;
    }

    dlist_node *n = dlist_node_create(value, l->elem_size);
    if (!n) return -1;

    n->prev = l->nil;
    n->next = l->nil->next;
    l->nil->next->prev = n;
    l->nil->next = n;

    return 0;
}

int dlist_pop_back(dlist *l, void *out) {
    if (!l) {
        errno = EINVAL;
        return -1;
    }

    if (l->nil->prev == l->nil) {
        errno = ENOENT;
        return -1;
    }

    dlist_node *n = l->nil->prev;
    dlist_node *new_back = n->prev;

    new_back->next = l->nil;
    l->nil->prev = new_back;

    if (out) {
        memcpy(out, n->value, l->elem_size);
    }

    dlist_node_free(n);

    return 0;
}

int dlist_pop_front(dlist *l, void *out) {
    if (!l) {
        errno = EINVAL;
        return -1;
    }

    if (l->nil->next == l->nil) {
        errno = ENOENT;
        return -1;
    }

    dlist_node *n = l->nil->next;
    dlist_node *new_front = n->next;

    new_front->prev = l->nil;
    l->nil->next = new_front;

    if (out) {
        memcpy(out, n->value, l->elem_size);
    }

    dlist_node_free(n);

    return 0;
}


int dlist_delete(dlist *l, dlist_node *n) {
    if (!l || !n) {
        errno = EINVAL;
        return -1;
    }

   n->prev->next = n->next;
   n->next->prev = n->prev;

   dlist_node_free(n);
   
   return 0;
}

int dlist_reverse(dlist *l) {
    if (!l) {
        errno = EINVAL;
        return -1;
    }

    /*
        ...
    */

    return -1;
}