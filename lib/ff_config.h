#ifndef __FSTACK_CONFIG_H
#define __FSTACK_CONFIG_H

// dpdk argc, argv, max argc: 4, member of dpdk_config
#define DPDK_CONFIG_NUM 4
#define DPDK_CONFIG_MAXLEN 64

extern int dpdk_argc;
extern char *dpdk_argv[DPDK_CONFIG_NUM + 1];

struct ff_port_cfg {
    char *name;
    uint8_t port_id;
    uint8_t mac[6];
    char *addr;
    char *netmask;
    char *broadcast;
    char *gateway;
    char *pcap;
};

struct ff_freebsd_cfg {
    char *name;
    char *str;
    void *value;
    size_t vlen;
    struct ff_freebsd_cfg *next;
};

struct ff_config {
    struct {
        /* mask of enabled lcores */
        char *lcore_mask;
        /* mask of current proc on all lcores */
        char *proc_mask;
        /* mask of enabled ports
         * use uint32_t because num of max ports is 32
         */
        uint32_t port_mask;
        int nb_channel;
        int memory;
        int no_huge;
        int nb_procs;
        int proc_id;
        int nb_ports;
        int promiscuous;
        int numa_on;
        struct ff_port_cfg *port_cfgs;
    } dpdk;

    struct {
        int enable;
        char *method;
        char *tcp_port;
        char *udp_port;
    } kni;

    struct {
        int level;
        const char *dir;
    } log;

    struct {
        struct ff_freebsd_cfg *boot;
        struct ff_freebsd_cfg *sysctl;
        long physmem;
        int hz;
    } freebsd;
};

extern struct ff_config ff_global_cfg;

int ff_load_config(const char *conf, int argc, char * const argv[]);

#endif /* ifndef __FSTACK_CONFIG_H */
