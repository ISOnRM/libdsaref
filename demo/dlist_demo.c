/* doubly linked list demo */
#include "dsaref/dlist.h"
#include "dsaref/die.h"
#include "dsaref/parse_any.h"
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

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <intmax values...>\n", argv[0]);
        return 1;
    }

    dlist l;
    if (dlist_init(&l, sizeof(intmax_t)) != 0) DIE1("dlist_init");

    dlist_print(intmax_t, "%" PRIdMAX, l);
    printf("\n\n");

    intmax_t t;
    for (int i = 1; i < argc; ++i) {
        if (parse_intmax_t(argv[i], &t) != 0) DIE2("parse_intmax_t", argv[i]);
        if (dlist_push_front(&l, &t) != 0)   DIE3("dlist_push_front", t, "%"PRIdMAX);
        printf("list_push_front: %" PRIdMAX "\n", t);
    }

    printf("\n\n");
    dlist_print(intmax_t, "%" PRIdMAX, l);
    printf("\n\n");

    while (dlist_pop_front(&l, &t) == 0) {
        printf("list_pop_front: %" PRIdMAX "\n", t);
    }

    printf("\n\n");
    dlist_print(intmax_t, "%" PRIdMAX, l);
    printf("\n\n");

    for (int i = 1; i < argc; ++i) {
        if (parse_intmax_t(argv[i], &t) != 0) DIE2("parse_intmax_t", argv[i]);
        if (dlist_push_back(&l, &t) != 0)   DIE3("dlist_push_back", t, "%"PRIdMAX);
        printf("list_push_back: %" PRIdMAX "\n", t);
    }

    printf("\n\n");
    dlist_print(intmax_t, "%" PRIdMAX, l);
    printf("\n\n");

    while (dlist_pop_back(&l, &t) == 0) {
        printf("list_pop_back: %" PRIdMAX "\n", t);
    }

    printf("\n\n");
    dlist_print(intmax_t, "%" PRIdMAX, l);
    printf("\n\n");

    dlist_destroy(&l);
    return 0;
}