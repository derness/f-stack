#ifndef _FSTACK_VETH_H
#define _FSTACK_VETH_H

struct ff_port_cfg;
void *ff_veth_attach(struct ff_port_cfg *cfg);
int ff_veth_detach(void *arg);

void *ff_mbuf_gethdr(void *pkt, uint16_t total, void *data, uint16_t len);
void *ff_mbuf_get(void *m, void *data, uint16_t len);
void ff_mbuf_free(void *m);

int ff_mbuf_copydata(void *m, void *data, int off, int len);

void ff_veth_process_packet(void *arg, void *m);


#endif /* ifndef _FSTACK_VETH_H */
