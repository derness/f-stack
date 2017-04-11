#ifndef _FSTACK_SYS__RWLOCK_H_
#define _FSTACK_SYS__RWLOCK_H_

#include "ff_host_interface.h"

/*
 * Reader/writer lock.
 */
struct rwlock {
    struct lock_object lock_object;
    ff_rwlock_t rw_lock;
};

struct rwlock_padalign {
    struct lock_object lock_object;
    ff_rwlock_t rw_lock;
} __aligned(CACHE_LINE_SIZE);

#endif    /* _FSTACK_SYS__RWLOCK_H_ */
