#include "ft_ping.h"

void	init_icmphdr(t_icmppkt *pkt, int id)
{
	pkt->hdr.type = 8;
	pkt->hdr.code = 0;
	pkt->hdr.un.echo.id = 42;
	pkt->hdr.un.echo.sequence = id;
	pkt->hdr.checksum = 0;
	//gettimeofday(&pkt->timestamp, NULL);
	memset(pkt->msg, 42, MSG_LEN);
}

void	init_iphdr(struct iphdr *pkt)
{
	pkt->version = 4;
	pkt->ihl = sizeof(struct iphdr) / 4;
	pkt->tos = 0;
	pkt->tot_len = sizeof(t_ippkt);
	pkt->id = 0;
	pkt->frag_off = 0;
	pkt->ttl = 20;
	pkt->protocol = IPPROTO_ICMP;
	pkt->check = 0;
	pkt->saddr = INADDR_ANY;
}

