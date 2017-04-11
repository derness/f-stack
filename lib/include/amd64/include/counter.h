#ifndef __FSTACK_MACHINE_COUNTER_H__
#define __FSTACK_MACHINE_COUNTER_H__

#include <sys/pcpu.h>

#define counter_enter()    do {} while (0)
#define counter_exit()    do {} while (0)

#ifdef IN_SUBR_COUNTER_C

static inline uint64_t
counter_u64_fetch_inline(uint64_t *p)
{
    return (*p);
}

static inline void
counter_u64_zero_inline(counter_u64_t c)
{
    *c = 0;
}
#endif

#define counter_u64_add_protected(c, i)    counter_u64_add(c, i)

static inline void
counter_u64_add(counter_u64_t c, int64_t inc)
{
    *c += inc;
}

#endif    /* ! __FSTACK_MACHINE_COUNTER_H__ */
