/* queue2 demo */

#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>
#include <unistd.h>

#include "dsaref/die.h"
#include "dsaref/parse_any.h"
#include "dsaref/queue2.h"

#define ANSI_RESET   "\x1b[0m"
#define ANSI_FG_RED  "\x1b[31m"

DEF_PARSE_ANY(double, "%lf")
DEF_PARSE_ANY(size_t, "%zu")

static void print_help(const char *prog_name) {
    fprintf(stderr, "Usage: %s <queue's cap> <double values...>\n", prog_name);
}

#define queue2_fields_dump(q) \
printf("s1 Count: %zu\n" \
       "s2 Count: %zu\n" \
       "Count:    %zu\n" \
       "Capacity: %zu\n",\
       (q)->s1.count, \
       (q)->s2.count, \
       (q)->count, \
       (q)->cap); \


int main(int argc, char **argv) {
    if (argc < 3) { print_help(argv[0]); return 1;}

    size_t init_cap;
    if (parse_size_t(argv[1], &init_cap) != 0) DIE2("parse_size_t", argv[1]);

    queue2 q;
    if (queue2_init(&q, sizeof(double), init_cap) != 0) DIE1("queue2_init");



    double t;
    for (int i = 2; i < argc; ++i) {
        if (parse_double(argv[i], &t) != 0) DIE2("parse_double", argv[i]);
        if (queue2_push_tail(&q, &t) != 0) DIE3("queue2_enq", t, "%lf");
        printf("Push Tail: %lf\n", t);
        queue2_fields_dump(&q);
    }

    printf("\n");
    double peek_head;
    if (queue2_peek_head(&q, &peek_head) != 0) DIE1("queue2_peek_head");
    printf("Head: %lf\n", peek_head);
    queue2_fields_dump(&q);
    printf("\n\n");

    double o;
    while (!queue2_empty(&q)) {
        if (queue2_pop_head(&q, &o) != 0) DIE1("queue2_deq");
        printf("Pop Head: %lf\n", o);
        queue2_fields_dump(&q);
    }

    queue2_destroy(&q);
    return 0;
}
