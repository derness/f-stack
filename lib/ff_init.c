#include <stdlib.h>

#include "ff_api.h"
#include "ff_config.h"
#include "ff_dpdk_if.h"

extern int ff_freebsd_init();

int
ff_init(const char *conf, int argc, char * const argv[])
{
    int ret;
    ret = ff_load_config(conf, argc, argv);
    if (ret < 0)
        exit(1);

    ret = ff_dpdk_init(dpdk_argc, (char **)&dpdk_argv);
    if (ret < 0)
        exit(1);

    ret = ff_freebsd_init();
    if (ret < 0)
        exit(1);

    ret = ff_dpdk_if_up();
    if (ret < 0)
        exit(1);

    return 0;
}

void
ff_run(loop_func_t loop, void *arg)
{
    ff_dpdk_run(loop, arg);
}

