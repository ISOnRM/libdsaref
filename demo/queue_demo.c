/* queue demo */

#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>
#include <unistd.h>

#define QUEUE_FIELDS_W_MACROS
#include "dsaref/die.h"
#include "dsaref/parse_any.h"
#include "dsaref/queue.h"

#define ANSI_RESET   "\x1b[0m"
#define ANSI_FG_RED  "\x1b[31m"

DEF_PARSE_ANY(double, "%lf")
DEF_PARSE_ANY(size_t, "%zu")

static void print_help(const char *prog_name) {
    fprintf(stderr, "Usage: %s <queue's cap> <double values...>\n", prog_name);
}

#define queue_fields_dump(q) \
printf("Count: %zu\n"        \
       "Cap: %zu\n"          \
       "Head: %zu\n"         \
       "Tail: %zu\n",        \
       (q)->count, (q)->cap, (q)->head, (q)->tail)

int main(int argc, char **argv) {
    if (argc < 3) { print_help(argv[0]); return 1;}

    size_t init_cap;
    if (parse_size_t(argv[1], &init_cap) != 0) DIE2("parse_size_t", argv[1]);

    queue q;
    if (queue_init(&q, sizeof(double), init_cap) != 0) DIE1("queue_init");



    double t;
    for (int i = 2; i < argc; ++i) {
        if (parse_double(argv[i], &t) != 0) DIE2("parse_double", argv[i]);
        if (queue_push_tail(&q, &t) != 0) DIE3("queue_enq", t, "%lf");
        printf("Push Tail: %lf\n", t);
        queue_fields_dump(&q);
    }

    printf("\n");
    double peek_tail, peek_head;
    if (queue_peek_tail(&q, &peek_tail) != 0) DIE1("queue_peek_tail");
    if (queue_peek_head(&q, &peek_head) != 0) DIE1("queue_peek_head");
    printf("Head: %lf, Tail: %lf\n", peek_head, peek_tail);
    queue_fields_dump(&q);
    printf("\n\n");

    double o;
    while (!queue_empty(&q)) {
        if (queue_pop_head(&q, &o) != 0) DIE1("queue_deq");
        printf("Pop Head: %lf\n", o);
        queue_fields_dump(&q);
    }

    if (isatty(1)) {
        printf("\n" ANSI_FG_RED "NOW IN REVERSE\n\n" ANSI_RESET);
    } else {
        printf("\nNOW IN REVERSE\n\n");
    }

    for (int i = argc - 1; i >= 2; --i) {
        if (parse_double(argv[i], &t) != 0) DIE2("parse_double", argv[i]);
        if (queue_push_head(&q, &t) != 0) DIE3("queue_enq", t, "%lf");
        printf("Push Head: %lf\n", t);
        queue_fields_dump(&q);
    }
    
    printf("\n");
    if (queue_peek_tail(&q, &peek_tail) != 0) DIE1("queue_peek_tail");
    if (queue_peek_head(&q, &peek_head) != 0) DIE1("queue_peek_head");
    printf("Tail: %lf, Head: %lf\n", peek_tail, peek_head);
    queue_fields_dump(&q);
    printf("\n\n");

    while (!queue_empty(&q)) {
        if (queue_pop_tail(&q, &o) != 0) DIE1("queue_deq");
        printf("Pop Tail: %lf\n", o);
        queue_fields_dump(&q);
    }
    
    queue_destroy(&q);
    return 0;
}
