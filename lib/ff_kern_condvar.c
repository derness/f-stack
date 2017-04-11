#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include "opt_ktrace.h"

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/lock.h>
#include <sys/mutex.h>
#include <sys/proc.h>
#include <sys/kernel.h>
#include <sys/ktr.h>
#include <sys/condvar.h>
#include <sys/sched.h>
#include <sys/signalvar.h>
#include <sys/sleepqueue.h>
#include <sys/resourcevar.h>

void
cv_init(struct cv *cvp, const char *desc)
{
    cvp->cv_description = desc;
}

void
cv_destroy(struct cv *cvp)
{

}

void
_cv_wait(struct cv *cvp, struct lock_object *lock)
{

}

int
_cv_wait_sig(struct cv *cvp, struct lock_object *lock)
{
    return (0);
}

int
_cv_timedwait(struct cv *cvp, struct lock_object *lock, int timo)
{
    return (0);
}

int
_cv_timedwait_sig(struct cv *cvp, struct lock_object *lock, int timo)
{
    return (0);
}

int
_cv_timedwait_sig_sbt(struct cv *cvp, struct lock_object *lock,
    sbintime_t sbt, sbintime_t pr, int flags)
{
    return (0);
}

void
cv_signal(struct cv *cvp)
{

}

void
cv_broadcastpri(struct cv *cvp, int pri)
{

}
