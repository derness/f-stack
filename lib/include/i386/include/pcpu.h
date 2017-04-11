#ifndef _FSTACK_MACHINE_PCPU_H_
#define _FSTACK_MACHINE_PCPU_H_

#include_next <machine/pcpu.h>

#undef __curthread
#undef PCPU_GET
#undef PCPU_ADD
#undef PCPU_INC
#undef PCPU_PTR
#undef PCPU_SET

extern __thread struct thread *pcurthread;
extern struct pcpu *pcpup;

#define PCPU_GET(member)         (pcpup->pc_ ## member)
#define PCPU_ADD(member, val)    (pcpup->pc_ ## member += (val))
#define PCPU_INC(member)         PCPU_ADD(member, 1)
#define PCPU_PTR(member)         (&pcpup->pc_ ## member)
#define PCPU_SET(member, val)    (pcpup->pc_ ## member = (val))

static __inline struct thread *
__curthread_fst(void)
{
    return (pcurthread);
}


#define __curthread __curthread_fst

#ifndef curthread
#define curthread __curthread_fst()
#endif
#endif    /* _FSTACK_MACHINE_PCPU_H_ */
