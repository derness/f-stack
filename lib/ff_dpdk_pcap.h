#ifndef _FSTACK_DPDK_PCAP_H
#define _FSTACK_DPDK_PCAP_H

#include <rte_config.h>
#include <rte_mbuf.h>

int ff_enable_pcap(const char* dump_path);
int ff_dump_packets(const char* dump_path, struct rte_mbuf *pkt);


#endif /* ifndef _FSTACK_DPDK_PCAP_H */
