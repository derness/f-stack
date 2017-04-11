#ifndef _FSTACK_DPDK_IF_H
#define _FSTACK_DPDK_IF_H

#include "ff_api.h"

#define ff_IF_NAME "f-stack-%d"

struct loop_routine {
    loop_func_t loop;
    void *arg;
};

int ff_dpdk_init(int argc, char **argv);
int ff_dpdk_if_up(void);
void ff_dpdk_run(loop_func_t loop, void *arg);

struct ff_dpdk_if_context;
struct ff_port_cfg;

struct ff_dpdk_if_context *ff_dpdk_register_if(void *sc, void *ifp,
    struct ff_port_cfg *cfg);
void ff_dpdk_deregister_if(struct ff_dpdk_if_context *ctx);

void ff_dpdk_set_if(struct ff_dpdk_if_context *ctx, void *sc, void *ifp);

int ff_dpdk_if_send(struct ff_dpdk_if_context* ctx, void *buf, int total);

void ff_dpdk_pktmbuf_free(void *m);


#endif /* ifndef _FSTACK_DPDK_IF_H */
