// stack demo
#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>

#define STACK_FIELDS_W_MACROS
#include "dsaref/stack.h"
#include "dsaref/parse_any.h"
#include "dsaref/die.h"

DEF_PARSE_ANY(double, "%lf")

static void print_help(const char *prog_name) {
    fprintf(stderr, "Usage: %s <double values...>\n", prog_name);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        print_help(argv[0]);
        return -1;
    }

    stack s;
    if (stack_init(&s, sizeof(double)) != 0) DIE1("stack_init");

    double t;
    for (int i = 1; i < argc; ++i) {
        if (parse_double(argv[i], &t) != 0) DIE2("parse_double", argv[i]);
        if (stack_push(&s, &t) != 0)        DIE3("stack_push", t, "%lf");
        printf("Pushed: %lf, Count=%zu\n", t, s.count);
    }

    double peek;
    if (stack_peek(&s, &peek) != 0) DIE1("stack_peek");
    printf("\n\nPeek: %lf\n\n\n", peek);

    while (!stack_empty(&s)) {
        if (stack_pop(&s, NULL) != 0) DIE1("stack_pop");
        printf("Popped. Count=%zu\n", s.count);
    }


    stack_destroy(&s);
}
