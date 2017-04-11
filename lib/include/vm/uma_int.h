#ifndef _FSTACK_VM_UMA_INT_H_
#define _FSTACK_VM_UMA_INT_H_

#include <sys/mutex.h>

#define vtoslab   vtoslab_native
#define vsetslab  vsetslab_native
#include_next <vm/uma_int.h>
#undef vtoslab
#undef vsetslab

#undef UMA_MD_SMALL_ALLOC

#define critical_enter() do {} while(0)
#define critical_exit()  do {} while(0)

extern int uma_page_mask;

#define UMA_PAGE_HASH(va) (((va) >> PAGE_SHIFT) & uma_page_mask)

typedef struct uma_page {
    LIST_ENTRY(uma_page) list_entry;
    vm_offset_t up_va;
    uma_slab_t up_slab;
} *uma_page_t;

LIST_HEAD(uma_page_head, uma_page);
extern struct uma_page_head *uma_page_slab_hash;

static __inline uma_slab_t
vtoslab(vm_offset_t va)
{       
    struct uma_page_head *hash_list;
    uma_page_t up;

    hash_list = &uma_page_slab_hash[UMA_PAGE_HASH(va)];
    LIST_FOREACH(up, hash_list, list_entry)
            if (up->up_va == va)
                    return (up->up_slab);
    return (NULL);
}

static __inline void
vsetslab(vm_offset_t va, uma_slab_t slab)
{
    struct uma_page_head *hash_list;
    uma_page_t up;
    hash_list = &uma_page_slab_hash[UMA_PAGE_HASH(va)];
    LIST_FOREACH(up, hash_list, list_entry)
        if (up->up_va == va)
            break;

    if (up != NULL) {
        up->up_slab = slab;
        return;
    }

    up = malloc(sizeof(*up), M_DEVBUF, M_WAITOK);
    up->up_va = va;
    up->up_slab = slab;
    LIST_INSERT_HEAD(hash_list, up, list_entry);
}

#endif    /* _FSTACK_VM_UMA_INT_H_ */
