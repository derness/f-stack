#ifndef _FSTACK_DPDK_KNI_H
#define _FSTACK_DPDK_KNI_H

#include <rte_config.h>
#include <rte_mbuf.h>
#include <rte_mempool.h>

enum FilterReturn {
    FILTER_UNKNOWN = -1,
    FILTER_ARP = 1,
    FILTER_KNI = 2,
};

void ff_kni_init(uint16_t nb_ports, const char *tcp_ports,
    const char *udp_ports, int accept);

void ff_kni_alloc(uint8_t port_id, unsigned socket_id,
    struct rte_mempool *mbuf_pool);

void ff_kni_process(uint8_t port_id, uint16_t queue_id,
    struct rte_mbuf **pkts_burst, unsigned count);

enum FilterReturn ff_kni_proto_filter(const void *data, uint16_t len);

int ff_kni_enqueue(uint8_t port_id, struct rte_mbuf *pkt);


#endif /* ifndef _FSTACK_DPDK_KNI_H */
