/* doubly linked list demo */
#include "dsaref/dlist.h"
#include "dsaref/die.h"
#include "dsaref/parse_any.h"
#include "dsaref/vec.h" /* dlist_print2 */
#include <stdio.h>
#include <inttypes.h>
#include <stddef.h>

DEF_PARSE_ANY(intmax_t, "%" SCNdMAX)

#define dlist_print(type, fmt, list)                       \
do {                                                       \
    printf("<= nil <=> ");                                 \
    if ((list).nil->next != (list).nil) {                  \
        dlist_node *curr = (list).nil->next;               \
        while (curr != (list).nil) {                       \
            printf(fmt " <=> ", *(type*)(curr->value));    \
            curr = curr->next;                             \
        }                                                  \
    } else printf("(empty) <=> ");                         \
    printf("nil =>\n");                                    \
} while (0)

void dlist_print2(const dlist *l, const char *fmt) {
    if (!l || !fmt) return;

    vec v;
    if (vec_init(&v, l->elem_size) != 0) return;

    dlist_node *curr = l->nil->next;
    while (curr != l->nil) {
        if (vec_push(&v, curr->value) != 0) {
            vec_destroy(&v);
            return;
        }
        curr = curr->next;
    }

    size_t half = v.len / 2;

    for (size_t i = half; i > 0; --i) {
        void *p = vec_at(&v, i - 1);
        printf(fmt, *(intmax_t *)p);
        printf(" <=> ");
    }

    printf("NIL <=> ");

    for (size_t i = v.len; i > half; --i) {
        void *p = vec_at(&v, i - 1);
        printf(fmt, *(intmax_t *)p);
        printf(" <=> ");
    }

    vec_destroy(&v);
}
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <intmax values...>\n", argv[0]);
        return 1;
    }

    dlist l;
    if (dlist_init(&l, sizeof(intmax_t)) != 0) DIE1("dlist_init");

    dlist_print2(&l, "%" PRIdMAX);
    printf("\n\n");

    intmax_t t;
    for (int i = 1; i < argc; ++i) {
        if (parse_intmax_t(argv[i], &t) != 0) DIE2("parse_intmax_t", argv[i]);
        if (dlist_push_front(&l, &t) != 0)   DIE3("dlist_push_front", t, "%"PRIdMAX);
        printf("list_push_front: %" PRIdMAX "\n", t);
    }

    printf("\n\n");
    // dlist_print(intmax_t, "%" PRIdMAX, l);
    dlist_print2(&l, "%" PRIdMAX);
    printf("\n\n");

    while (dlist_pop_front(&l, &t) == 0) {
        printf("list_pop_front: %" PRIdMAX "\n", t);
    }

    printf("\n\n");
    dlist_print2(&l, "%" PRIdMAX);
    printf("\n\n");

    for (int i = 1; i < argc; ++i) {
        if (parse_intmax_t(argv[i], &t) != 0) DIE2("parse_intmax_t", argv[i]);
        if (dlist_push_back(&l, &t) != 0)   DIE3("dlist_push_back", t, "%"PRIdMAX);
        printf("list_push_back: %" PRIdMAX "\n", t);
    }

    printf("\n\n");
    dlist_print2(&l, "%" PRIdMAX);
    printf("\n\n");

    while (dlist_pop_back(&l, &t) == 0) {
        printf("list_pop_back: %" PRIdMAX "\n", t);
    }

    printf("\n\n");
    dlist_print2(&l, "%" PRIdMAX);
    printf("\n\n");

    dlist_destroy(&l);
    return 0;
}