#include "ft_ping.h"

uint16_t	compute_checksum(uint16_t *addr, size_t count)
{
	/*
	 * Compute Internet Checksum for "count" bytes
	 *         beginning at location "addr".
	 **/
	long sum = 0;
	while( count > 1 )  {
		/*  This is the inner loop */
		sum += *addr++;
		count -= 2;
	}
	/*  Add left-over byte, if any */
	if( count > 0 )
		sum += *addr;
	/*  Fold 32-bit sum to 16 bits */
	while (sum>>16)
		sum = (sum & 0xffff) + (sum >> 16);
	return ~sum;
}

void	init_icmphdr(t_icmppkt *pkt, int id)
{
	pkt->hdr.type = 8;
	pkt->hdr.code = 0;
	pkt->hdr.un.echo.id = 42;
	pkt->hdr.un.echo.sequence = id;
	pkt->hdr.checksum = 0;
	if (gettimeofday(&pkt->timestamp, NULL) < 0)
		fprintf(stderr, "Error getting time of day\n");
	memset(pkt->msg, 42, MSG_LEN);
	pkt->hdr.checksum = compute_checksum((uint16_t*)pkt, sizeof(t_icmppkt));
}

