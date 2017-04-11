#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <sys/param.h>

#include <sys/systm.h>
#include <sys/condvar.h>
#include <sys/kdb.h>
#include <sys/kernel.h>
#include <sys/ktr.h>
#include <sys/lock.h>
#include <sys/malloc.h>
#include <sys/mutex.h>
#include <sys/proc.h>
#include <sys/resourcevar.h>
#include <sys/sched.h>
#include <sys/signalvar.h>
#include <sys/sleepqueue.h>
#include <sys/smp.h>
#include <sys/sx.h>
#include <sys/sysctl.h>
#include <sys/vmmeter.h>
#ifdef KTRACE
#include <sys/uio.h>
#include <sys/ktrace.h>
#endif

#include "ff_host_interface.h"

int hogticks;
static uint8_t pause_wchan[MAXCPU];

typedef struct sleep_entry {
    LIST_ENTRY(sleep_entry) list_entry;
    void *chan;
    const char *wmesg;
    struct cv cond;
    int waiters;
} *sleep_entry_t;

static void synch_setup(void *dummy);
SYSINIT(synch_setup, SI_SUB_INTR, SI_ORDER_FIRST, synch_setup,
    NULL);

static struct se_head *se_active;
static u_long se_hashmask;
static struct mtx synch_lock;
#define SE_HASH(chan) (((uintptr_t)chan) & se_hashmask)
LIST_HEAD(se_head, sleep_entry);

static void
synch_setup(void *arg)
{
    mtx_init(&synch_lock, "synch_lock", NULL, MTX_DEF);
    se_active = hashinit(64, M_TEMP, &se_hashmask);
}

int
_sleep(void *ident, struct lock_object *lock, int priority,
    const char *wmesg, sbintime_t sbt, sbintime_t pr, int flags)
{
    //FIXME:we couldn't really sleep.
    return (0);
}


//FIXME.
int
msleep_spin_sbt(void *ident, struct mtx *mtx, const char *wmesg,
    sbintime_t sbt, sbintime_t pr, int flags)
{
    return (0);
}

int
pause_sbt(const char *wmesg, sbintime_t sbt, sbintime_t pr, int flags)
{
    return (_sleep(&pause_wchan[curcpu], NULL, 0, wmesg, sbt, pr, flags));
}

void
wakeup(void *chan)
{

}


void
wakeup_one(void *chan)
{

}

void
kern_yield(int prio)
{

}
