#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>

#define QUEUE_FIELDS_W_MACROS
#include "dsaref/die.h"
#include "dsaref/parse_any.h"
#include "dsaref/queue.h"

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
        if (queue_enq(&q, &t) != 0) DIE3("queue_enq", t, "%lf");
        printf("Enqueued: %lf\n", t);
        queue_fields_dump(&q);
    }

    printf("\n");
    queue_fields_dump(&q);
    printf("\n\n");

    double o;
    while (!queue_empty(&q)) {
        if (queue_deq(&q, &o) != 0) DIE1("queue_deq");
        printf("Dequeued: %lf\n", o);
        queue_fields_dump(&q);
    }
    
    queue_destroy(&q);
    return 0;
}
