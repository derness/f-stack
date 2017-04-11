#ifndef _FSTACK_API_H
#define _FSTACK_API_H

#ifdef __cplusplus
extern "C" {
#endif
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/poll.h>

#include "ff_event.h"
#include "ff_errno.h"

struct linux_sockaddr {
    short sa_family;
    char sa_data[14];
};

typedef int (*loop_func_t)(void *arg);

int ff_init(const char *conf, int argc, char * const argv[]);

void ff_run(loop_func_t loop, void *arg);

int ff_fcntl(int fd, int cmd, ...);

int ff_sysctl(const int *name, u_int namelen, void *oldp, size_t *oldlenp,
    const void *newp, size_t newlen);

int ff_ioctl(int fd, unsigned long request, ...);

int ff_socket(int domain, int type, int protocol);

int ff_setsockopt(int s, int level, int optname, const void *optval,
    socklen_t optlen);

int ff_getsockopt(int s, int level, int optname, void *optval,
    socklen_t *optlen);

int ff_socketpair(int domain, int type, int protocol, int *sv);

int ff_listen(int s, int backlog);
int ff_bind(int s, const struct linux_sockaddr *addr, socklen_t addrlen);
int ff_accept(int s, struct linux_sockaddr *addr, socklen_t *addrlen);
int ff_connect(int s, const struct linux_sockaddr *name, socklen_t namelen);
int ff_close(int fd);
int ff_shutdown(int s, int how);

int ff_getpeername(int s, struct linux_sockaddr *name,
    socklen_t *namelen);
int ff_getsockname(int s, struct linux_sockaddr *name,
    socklen_t *namelen);

ssize_t ff_read(int d, void *buf, size_t nbytes);
ssize_t ff_readv(int fd, const struct iovec *iov, int iovcnt);

ssize_t ff_write(int fd, const void *buf, size_t nbytes);
ssize_t ff_writev(int fd, const struct iovec *iov, int iovcnt);

ssize_t ff_send(int s, const void *buf, size_t len, int flags);
ssize_t ff_sendto(int s, const void *buf, size_t len, int flags,
    const struct linux_sockaddr *to, socklen_t tolen);
ssize_t ff_sendmsg(int s, const struct msghdr *msg, int flags);

ssize_t ff_recv(int s, void *buf, size_t len, int flags);
ssize_t ff_recvfrom(int s, void *buf, size_t len, int flags,
    struct linux_sockaddr *from, socklen_t *fromlen);
ssize_t ff_recvmsg(int s, struct msghdr *msg, int flags);

int ff_select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
    struct timeval *timeout);

int ff_poll(struct pollfd fds[], nfds_t nfds, int timeout);

int ff_kqueue(void);
int ff_kevent(int kq, const struct kevent *changelist, int nchanges, 
    struct kevent *eventlist, int nevents, const struct timespec *timeout);

#ifdef __cplusplus
}
#endif
#endif

