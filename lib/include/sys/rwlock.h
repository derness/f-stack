#ifndef _FSTACK_SYS_RWLOCK_H_
#define _FSTACK_SYS_RWLOCK_H_
#include_next <sys/rwlock.h>

#undef rw_init
#undef rw_init_flags
#undef rw_destroy
#undef rw_wowned
#undef _rw_wlock
#undef _rw_try_wlock
#undef _rw_wunlock
#undef _rw_rlock
#undef _rw_try_rlock
#undef _rw_runlock
#undef _rw_try_upgrade
#undef _rw_downgrade

#define DO_NOTHING do {} while(0)

void ff_rw_init_flags(struct lock_object *lo, const char *name, int opts);

#define rw_init(rw, n)          \
    rw_init_flags((rw), (n), 0)
#define rw_init_flags(rw, n, o) \
    ff_rw_init_flags(&(rw)->lock_object, (n), (o))
#define rw_destroy(rw) DO_NOTHING
#define rw_wowned(rw) 1
#define _rw_wlock(rw, f, l)    DO_NOTHING
#define _rw_try_wlock(rw, f, l) 1
#define _rw_wunlock(rw, f, l) DO_NOTHING
#define _rw_rlock(rw, f, l)    DO_NOTHING
#define _rw_try_rlock(rw, f, l) 1
#define _rw_runlock(rw, f, l) DO_NOTHING
#define _rw_try_upgrade(rw, f, l) 1
#define _rw_downgrade(rw, f, l) DO_NOTHING

#endif    /* _FSTACK_SYS_RWLOCK_H_ */
