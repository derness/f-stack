#include <sys/cdefs.h>
#include <sys/param.h>
#include <sys/pcpu.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/lock.h>
#include <sys/sx.h>
#include <sys/vmmeter.h>
#include <sys/cpuset.h>
#include <sys/sysctl.h>

#include <vm/uma.h>
#include <vm/uma_int.h>
#include <vm/vm.h>
#include <vm/vm_extern.h>

#include "ff_host_interface.h"
#include "ff_api.h"
#include "ff_config.h"

unsigned int sleep(unsigned int seconds);

int ff_freebsd_init(void);

extern void mutex_init(void);
extern void mi_startup(void);
extern void uma_startup(void *, int);
extern void uma_startup2(void);

extern void ff_init_thread0(void);

struct sx proctree_lock;
struct pcpu *pcpup;
struct uma_page_head *uma_page_slab_hash;
int uma_page_mask;
extern cpuset_t all_cpus;

long physmem;

int
ff_freebsd_init(void)
{
    int boot_pages;
    unsigned int num_hash_buckets;
    char tmpbuf[32] = {0};
    void *bootmem;
    int error;

    snprintf(tmpbuf, sizeof(tmpbuf), "%u", ff_global_cfg.freebsd.hz);
    error = kern_setenv("kern.hz", tmpbuf);
    if (error != 0) {
        panic("kern_setenv failed: kern.hz=%s\n", tmpbuf);
    }

    struct ff_freebsd_cfg *cur;
    cur = ff_global_cfg.freebsd.boot;
    while (cur) {
        error = kern_setenv(cur->name, cur->str);
        if (error != 0) {
            printf("kern_setenv failed: %s=%s\n", cur->name, cur->str);
        }

        cur = cur->next;
    }

    physmem = ff_global_cfg.freebsd.physmem;

    pcpup = malloc(sizeof(struct pcpu), M_DEVBUF, M_ZERO);
    pcpu_init(pcpup, 0, sizeof(struct pcpu));
    CPU_SET(0, &all_cpus);

    ff_init_thread0();

    boot_pages = 16;
    bootmem = (void *)kmem_malloc(NULL, boot_pages*PAGE_SIZE, M_ZERO);
    uma_startup(bootmem, boot_pages);
    uma_startup2();

    num_hash_buckets = 8192;
    uma_page_slab_hash = (struct uma_page_head *)kmem_malloc(NULL, sizeof(struct uma_page)*num_hash_buckets, M_ZERO);
    uma_page_mask = num_hash_buckets - 1;

    mutex_init();
    mi_startup();
    sx_init(&proctree_lock, "proctree");

    cur = ff_global_cfg.freebsd.sysctl;
    while (cur) {
        error = kernel_sysctlbyname(curthread, cur->name, NULL, NULL,
            cur->value, cur->vlen, NULL, 0);

        if (error != 0) {
            printf("kernel_sysctlbyname failed: %s=%s\n", cur->name, cur->str);
        }

        cur = cur->next;
    }

    return (0);
}
