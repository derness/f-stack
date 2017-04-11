#ifndef _FSTACK_SYS_CONDVAR_H_
#define _FSTACK_SYS_CONDVAR_H_

#ifndef LOCORE
#include <sys/queue.h>

#include "ff_host_interface.h"

struct lock_object;
struct thread;

TAILQ_HEAD(cv_waitq, thread);

/*
 * Condition variable.  The waiters count is protected by the mutex that
 * protects the condition; that is, the mutex that is passed to cv_wait*()
 * and is held across calls to cv_signal() and cv_broadcast().  It is an
 * optimization to avoid looking up the sleep queue if there are no waiters.
 */
struct cv {
    const char *cv_description;
    ff_cond_t cv_cond;
};

#ifdef _KERNEL
void cv_init(struct cv *cvp, const char *desc);
void cv_destroy(struct cv *cvp);

void _cv_wait(struct cv *cvp, struct lock_object *lock);
void _cv_wait_unlock(struct cv *cvp, struct lock_object *lock);
int _cv_wait_sig(struct cv *cvp, struct lock_object *lock);
int _cv_timedwait(struct cv *cvp, struct lock_object *lock, int timo);
int _cv_timedwait_sig(struct cv *cvp, struct lock_object *lock, int timo);
int _cv_timedwait_sig_sbt(struct cv *cvp, struct lock_object *lock,
    sbintime_t sbt, sbintime_t pr, int flags);

void cv_signal(struct cv *cvp);
void cv_broadcastpri(struct cv *cvp, int pri);

#define cv_wait(cvp, lock)                        \
    _cv_wait((cvp), &(lock)->lock_object)
#define cv_wait_unlock(cvp, lock)                    \
    _cv_wait_unlock((cvp), &(lock)->lock_object)
#define cv_wait_sig(cvp, lock)                        \
    _cv_wait_sig((cvp), &(lock)->lock_object)
#define cv_timedwait(cvp, lock, timo)                    \
    _cv_timedwait((cvp), &(lock)->lock_object, (timo))
#define cv_timedwait_sig(cvp, lock, timo)                \
    _cv_timedwait_sig((cvp), &(lock)->lock_object, (timo))
#define cv_timedwait_sig_sbt(cvp, lock, sbt, pr, flags)            \
    _cv_timedwait_sig_sbt((cvp), &(lock)->lock_object, (sbt), (pr), (flags))

#define cv_broadcast(cvp) cv_broadcastpri(cvp, 0)

#define cv_wmesg(cvp) ((cvp)->cv_description)

#endif    /* _KERNEL */
#endif    /* !LOCORE */
#endif    /* _FSTACK_SYS_CONDVAR_H_ */
