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
