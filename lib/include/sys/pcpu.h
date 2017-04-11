#ifndef _FSTACK_SYS_PCPU_H_
#define _FSTACK_SYS_PCPU_H_

#include_next <sys/pcpu.h>
#undef curcpu

#define curcpu    0
#ifndef curthread
#define curthread __curthread
#endif
#endif    /* _FSTACK_SYS_PCPU_H_ */
