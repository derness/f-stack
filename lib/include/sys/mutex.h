#ifndef _FSTACK_SYS_MUTEX_H_
#define _FSTACK_SYS_MUTEX_H_
#include_next <sys/mutex.h>

#undef __mtx_lock
#undef __mtx_unlock
#undef __mtx_lock_spin
#undef __mtx_unlock_spin

#undef _mtx_lock_flags
#undef _mtx_unlock_flags
#undef _mtx_lock_spin_flags
#undef _mtx_unlock_spin_flags

#undef thread_lock_flags_
#undef thread_lock
#undef thread_lock_flags
#undef thread_unlock

#undef mtx_trylock_flags_
#undef _mtx_trylock_spin_flags
#undef __mtx_trylock_spin

#undef mtx_init
#undef mtx_destroy
#undef mtx_owned

#define DO_NOTHING do {} while(0)

#define __mtx_lock(mp, tid, opts, file, line) DO_NOTHING
#define __mtx_unlock(mp, tid, opts, file, line) DO_NOTHING
#define __mtx_lock_spin(mp, tid, opts, file, line) DO_NOTHING
#define __mtx_unlock_spin(mp) DO_NOTHING

#define _mtx_lock_flags(m, opts, file, line) DO_NOTHING
#define _mtx_unlock_flags(m, opts, file, line) DO_NOTHING
#define _mtx_lock_spin_flags(m, opts, file, line) DO_NOTHING
#define _mtx_unlock_spin_flags(m, opts, file, line) DO_NOTHING

#define thread_lock_flags_(tdp, opts, file, line) DO_NOTHING
#define thread_lock(tdp) DO_NOTHING
#define thread_lock_flags(tdp, opt)    DO_NOTHING
#define thread_unlock(tdp) DO_NOTHING

#define mtx_trylock_flags_(m, o, f, l) 1
#define _mtx_trylock_spin_flags(m, o, f, l) 1
#define __mtx_trylock_spin(m, t, o, f, l) 1

void ff_mtx_init(struct lock_object *lo, const char *name, const char *type, int opts);

#define mtx_init(m, n, t, o) \
    ff_mtx_init(&(m)->lock_object, n, t, o)

#define mtx_destroy(m) DO_NOTHING

#define mtx_owned(m)    (1)

#endif    /* _FSTACK_SYS_MUTEX_H_ */
