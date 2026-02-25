#ifndef PARSE_ANY_H
#define PARSE_ANY_H

#include <stdio.h>
#include <errno.h>

#define DEF_PARSE_ANY(type, fmt)                            \
static inline int parse_##type(const char *s, type *out) {  \
    if (!s || !out) return -1;                              \
    type t;                                                 \
    if (sscanf(s, fmt, &t) != 1) {errno=EINVAL; return -1;};\
    *out = t;                                               \
    return 0;                                               \
}                                                            
    

#endif /* PARSE_ANY_H */
