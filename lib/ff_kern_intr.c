#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include "opt_ddb.h"

#include <sys/param.h>
#include <sys/bus.h>
#include <sys/conf.h>
#include <sys/cpuset.h>
#include <sys/rtprio.h>
#include <sys/systm.h>
#include <sys/interrupt.h>
#include <sys/kernel.h>
#include <sys/kthread.h>
#include <sys/ktr.h>
#include <sys/limits.h>
#include <sys/lock.h>
#include <sys/malloc.h>
#include <sys/mutex.h>
#include <sys/priv.h>
#include <sys/proc.h>
#include <sys/random.h>
#include <sys/resourcevar.h>
#include <sys/sched.h>
#include <sys/smp.h>
#include <sys/sysctl.h>
#include <sys/syslog.h>
#include <sys/unistd.h>
#include <sys/vmmeter.h>
#include <machine/atomic.h>
#include <machine/cpu.h>
#include <machine/md_var.h>
#include <machine/stdarg.h>
#ifdef DDB
#include <ddb/ddb.h>
#include <ddb/db_sym.h>
#endif

struct intr_event *clk_intr_event;

void
critical_enter(void)
{

}

void
critical_exit(void)
{

}

int
swi_add(struct intr_event **eventp, const char *name, driver_intr_t handler,
        void *arg, int pri, enum intr_type flags, void **cookiep)
{
    return 0;
}

void
swi_sched(void *cookie, int flags)
{

}

int
swi_remove(void *cookie)
{
    return 0;
}

int
intr_event_bind(struct intr_event *ie, int cpu)
{
    return (EOPNOTSUPP);
}

