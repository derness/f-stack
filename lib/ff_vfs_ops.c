#include <sys/cdefs.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/limits.h>
#include <sys/malloc.h>
#include <sys/namei.h>
#include <sys/refcount.h>
#include <sys/resourcevar.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/priv.h>
#include <sys/time.h>
#include <sys/ucred.h>
#include <sys/vnode.h>
#include <sys/uio.h>
#include <sys/file.h>
#include <sys/capsicum.h>

void
NDFREE(struct nameidata *ndp, const u_int flags)
{

}

int    
vn_open(struct nameidata *ndp, int *flagp, int cmode, struct file *fp)
{
    panic("vn_open not implemented");

    return (0);
}


int    
vn_close(struct vnode *vp,
        int flags, struct ucred *file_cred, struct thread *td)
{
    panic("vn_close not implemented");

    return (0);
}


int    
vn_rdwr(enum uio_rw rw, struct vnode *vp, void *base,
        int len, off_t offset, enum uio_seg segflg, int ioflg,
        struct ucred *active_cred, struct ucred *file_cred, ssize_t *aresid,
        struct thread *td)
{
    panic("vn_rdwr not implemented");

    return (0);
}

int
vn_fill_kinfo_vnode(struct vnode *vp, struct kinfo_file *kif)
{
    panic("vn_fill_kinfo_vnode not implemented");

    return (0);
}

void
NDINIT_ALL(struct nameidata *ndp, u_long op, u_long flags, enum uio_seg segflg,
    const char *namep, int dirfd, struct vnode *startdir, cap_rights_t *rightsp,
    struct thread *td)
{

    ndp->ni_cnd.cn_nameiop = op;
    ndp->ni_cnd.cn_flags = flags;
    ndp->ni_segflg = segflg;
    ndp->ni_dirp = namep;
    ndp->ni_dirfd = dirfd;
    ndp->ni_startdir = startdir;
    ndp->ni_strictrelative = 0;
    if (rightsp != NULL)
        ndp->ni_rightsneeded = *rightsp;
    else
        cap_rights_init(&ndp->ni_rightsneeded);
    filecaps_init(&ndp->ni_filecaps);
    ndp->ni_cnd.cn_thread = td;
}

