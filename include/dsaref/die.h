#ifndef DIE_H
#define DIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static inline void die_impl(const char *file,
                            int         line,
                            const char *func,
                            const char *msg,
                            const char *ent)
{
    if (ent) {
        fprintf(stderr, "%s:%d:%s:%s: %s (%s)\n",
                        file, line, func, msg, strerror(errno), ent);
    } else {
        fprintf(stderr, "%s:%d:%s:%s: %s\n",
                        file, line, func, msg, strerror(errno));
    }
    exit(EXIT_FAILURE);
}

#define DIE1(msg) \
die_impl(__FILE__, __LINE__, __func__, msg, NULL)

#define DIE2(msg, ent) \
die_impl(__FILE__, __LINE__, __func__, msg, ent)

#define DIE3(msg, ent, ent_fmt)        \
do {                                   \
    char s[BUFSIZ];                    \
    snprintf(s, BUFSIZ, ent_fmt, ent); \
    DIE2(msg, s);                      \
} while (0)


#endif /* DIE_H */
