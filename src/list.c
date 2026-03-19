/* singly linked list impl */
#include "dsaref/list.h"
#include <stdlib.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>

/* helpers */

static list_node *list_node_create(const void *value, size_t elem_size) {
	if (elem_size == 0) {
		errno = EINVAL;
		return NULL;
	}
	list_node *n = malloc(sizeof *n);
	if (!n) {
		errno = ENOMEM;
		return NULL;
	}
	n->next = NULL;
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
	return n;
}

static void list_node_free(list_node *n) {
    if (n) {
        n->next = NULL;
        free(n->value);
		free(n);
    }
}

int list_init(list *l, size_t elem_size) {
    if (!l || elem_size == 0) { errno = EINVAL; return -1; }
	list_node *nil = list_node_create(NULL, elem_size);
	if (!nil) return -1;
    l->elem_size = elem_size;
	l->nil = nil;
	l->nil->next = l->nil;
    return 0;
}

void list_destroy(list *l) {
    if (l) {
		list_node *curr = l->nil->next;
		list_node *next;
		while (curr != l->nil) {
			next = curr->next;
			list_node_free(curr);
			curr = next;
		}
		list_node_free(l->nil);
        l->elem_size = 0;
        l->nil = NULL;
    }
}

list_node *list_search(list *l, const void *value) {
    if (!l || !value) { errno = EINVAL; return NULL; }
    list_node *curr = l->nil->next;
    while (curr != l->nil) {
        if (memcmp(curr->value, value, l->elem_size) == 0) return curr;
        curr = curr->next;
    }
    return NULL;
}

int list_push_front(list *l, const void *value) {
    if (!l || !value) { 
        errno = EINVAL;
        return -1;
    }
    list_node *n = list_node_create(value, l->elem_size);
    if (!n) return -1;
    n->next = l->nil->next;
    l->nil->next = n;
    return 0;
}

int list_pop_front(list *l, void *out) {
    if (!l) {
        errno = EINVAL;
        return -1;
    }
    if (l->nil->next == l->nil) return -1;
    list_node *n = l->nil->next;
    l->nil->next = n->next;

    if (out) {
        memcpy(out, n->value, l->elem_size);
    }
    
    list_node_free(n);
    return 0;
}

int list_reverse(list *l) {
    if (!l) {
        errno = EINVAL;
        return -1;
    }
    list_node *prev = l->nil;
    list_node *curr = l->nil->next;
    list_node *next;
    while (curr != l->nil) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    /*
        nil -> e0 -> e1 -> e2 -> nil
        ^      ^
        prev   curr  ^
                     next
        
        nil <- e0 -> e1 -> e2 -> nil
               ^     ^
               prev  curr  ^
                           next

        nil <- e0 <- e1 -> e2 -> nil
                     ^     ^
                     prev  curr  ^
                                 next
    */
    return 0;
}