#include "ft_ping.h"


int		resolve_host(char *host, t_socket *sock)
{
	struct addrinfo hints;
	struct addrinfo *res;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	if (getaddrinfo(host, NULL, &hints, &res))
		return -1;
	sock->addr = *(struct sockaddr_in*)res->ai_addr;
	freeaddrinfo(res);

	sock->addr.sin_family = AF_INET;
	sock->addr.sin_port = 80;
	sock->fd = socket(AF_INET,  SOCK_RAW, IPPROTO_ICMP);
	if (sock->fd < 0)
		return -1;
	return 0;
}
