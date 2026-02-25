// vec demo

#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>

#include "dsaref/vec.h"
#include "dsaref/parse_any.h"
#include "dsaref/die.h"

DEF_PARSE_ANY(intmax_t, "%" SCNiMAX)
DEF_PARSE_ANY(size_t, "%zu")

static void print_help(const char *prog_name) {
    fprintf(stderr, "Usage: %s <init cap> <intmax values...>\n", prog_name);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        print_help(argv[0]);
        return 1;
    }

    vec v;
    if (vec_init(&v, sizeof(intmax_t)) != 0)   DIE1("vec_init");
    size_t init_cap;
    if (parse_size_t(argv[1], &init_cap) != 0) DIE2("parse_size_t", argv[1]);
    if (vec_reserve(&v, init_cap) != 0)        DIE3("vec_reserve", init_cap, "%zu");

    intmax_t t;
    for (int i = 2; i < argc; ++i) {
        if (parse_intmax_t(argv[i], &t) != 0) DIE2("parse_int_max", argv[i]);
        if (vec_push(&v, &t) != 0)            DIE3("vec_push", t, "%" PRIdMAX);
        printf("Pushed: %" PRIdMAX ", Len=%zu\n", t, v.len);
    }

    void *f, *b;
    f = vec_front(&v);
    b = vec_back(&v);
    if (!f || !b) {
        DIE1((f) ? "vec_back" : "vec_front");
    }

    printf("\n\nFront: %"PRIdMAX"\nBack: %"PRIdMAX"\n\n\n",
           *(intmax_t*)(f), *(intmax_t*)(b));

    while (v.len != 0) {
        if (vec_pop(&v, NULL) != 0) DIE1("vec_pop");
        printf("Popped. Len=%zu\n", v.len);
    }

    vec_destroy(&v);
}