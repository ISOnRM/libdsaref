/* singly linked list demo */
#include "dsaref/list.h"
#include "dsaref/die.h"
#include "dsaref/parse_any.h"
#include <stdio.h>
#include <inttypes.h>
#include <stddef.h>

DEF_PARSE_ANY(intmax_t, "%" SCNdMAX)

#define list_print(type, fmt, list)                     \
do {                                                    \
    printf("nil -> ");                                  \
    if ((list).nil->next != (list).nil) {               \
        list_node *curr = (list).nil->next;             \
        while (curr != (list).nil) {                    \
            printf(fmt " -> ", *(type*)(curr->value));  \
            curr = curr->next;                          \
        }                                               \
    } else printf("(empty) -> ");                       \
    printf("nil\n");                                    \
} while (0)

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <intmax values...>\n", argv[0]);
        return 1;
    }

    list l;
    if (list_init(&l, sizeof(intmax_t)) != 0) DIE1("list_init");

    list_print(intmax_t, "%" PRIdMAX, l);
    printf("\n\n");

    intmax_t t;
    for (int i = 1; i < argc; ++i) {
        if (parse_intmax_t(argv[i], &t) != 0) DIE2("parse_intmax_t", argv[i]);
        if (list_push_front(&l, &t) != 0)   DIE3("list_push_front", t, "%"PRIdMAX);
        printf("list_push_front: %" PRIdMAX "\n", t);
    }

    printf("\n\n");
    list_print(intmax_t, "%" PRIdMAX, l);
    printf("\n\n");

    while (list_pop_front(&l, &t) == 0) {
        printf("list_pop_front: %" PRIdMAX "\n", t);
    }

    printf("\n\n");
    list_print(intmax_t, "%" PRIdMAX, l);
    printf("\n\n");

    list_destroy(&l);
    return 0;
}