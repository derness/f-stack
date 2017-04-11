#ifndef _FSTACK_SYS__MUTEX_H_
#define _FSTACK_SYS__MUTEX_H_

#include <machine/param.h>

#include "ff_host_interface.h"

/*
 * Sleep/spin mutex
 */
struct mtx {
    struct lock_object lock_object;
    ff_mutex_t mtx_lock;
};

/*
 * Members of struct mtx_padalign must mirror members of struct mtx.
 * mtx_padalign mutexes can use the mtx(9) API transparently without
 * modification.
 */
struct mtx_padalign {
    struct lock_object    lock_object;
    ff_mutex_t    mtx_lock;
} __aligned(CACHE_LINE_SIZE);

#endif    /* _FSTACK_SYS__MUTEX_H_ */
