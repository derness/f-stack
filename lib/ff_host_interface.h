#ifndef _FSTACK_HOST_INTERFACE_H_
#define _FSTACK_HOST_INTERFACE_H_

#define ff_PROT_NONE     0x00
#define ff_PROT_READ     0x01
#define ff_PROT_WRITE    0x02

#define ff_MAP_SHARED    0x0001
#define ff_MAP_PRIVATE   0x0002
#define ff_MAP_ANON      0x1000
#define ff_MAP_NOCORE    0x00020000

#define ff_MAP_FAILED    ((void *)-1)

void *ff_mmap(void *addr, uint64_t len, int prot, int flags, int fd, uint64_t offset);
int ff_munmap(void *addr, uint64_t len);

void *ff_malloc(uint64_t size);
void *ff_calloc(uint64_t number, uint64_t size);
void *ff_realloc(void *p, uint64_t size);
void ff_free(void *p);

#define ff_CLOCK_REALTIME        0
#define ff_CLOCK_MONOTONIC        4
#define ff_CLOCK_MONOTONIC_FAST       12

#define ff_NSEC_PER_SEC    (1000ULL * 1000ULL * 1000ULL)

void ff_clock_gettime(int id, int64_t *sec, long *nsec);
uint64_t ff_clock_gettime_ns(int id);
int ff_nanosleep(uint64_t nsecs);

typedef void * ff_mutex_t;
typedef void * ff_cond_t;
typedef void * ff_rwlock_t;

void ff_arc4rand(void *ptr, unsigned int len, int reseed);
uint32_t ff_arc4random(void);

int ff_setenv(const char *name, const char *value);
char *ff_getenv(const char *name);

void ff_os_errno(int error);

int ff_rss_check(uint32_t saddr, uint32_t daddr, uint16_t sport, uint16_t dport);

#endif

