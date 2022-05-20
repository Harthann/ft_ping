#include "ft_ping.h"

int		resolve_dns(char *host, struct sockaddr *addr)
{
	struct addrinfo hints;
	struct addrinfo *res;
//	char buffer[256];
	int error = 0;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	error = getaddrinfo(host, NULL, &hints, &res);
	if (error)
		return -1;
	*addr = *res->ai_addr;
	freeaddrinfo(res);
	return 0;
}

int		resolve_host(char *host, t_socket *sock)
{
	for (int i = 0; host[i]; i++)
	{
		if (host[i] != '.' && (host[i] < '0' || host[i] > '9'))
		{
			if (resolve_dns(host, (struct sockaddr*)&sock->addr) < 0)
				return -1;
			else
				goto _sockend;
		}
	}
	if (inet_pton(AF_INET, host, &sock->addr.sin_addr) != 1)
		return (-1);
	sock->addr.sin_family = AF_INET;
	sock->addr.sin_port = 80;
_sockend:
	sock->fd = socket(AF_INET,  SOCK_RAW, IPPROTO_ICMP);
	if (sock->fd < 0)
		return -1;
	return 0;
}
