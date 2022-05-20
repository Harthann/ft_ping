#ifndef FT_PING_H
# define FT_PING_H

#include <dbg.h>
#include <dbgmacros.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>

#include <errno.h>


#define RETERROR(value, args...) { fprintf(stderr, "ft_ping: %s %s", ##args); return value; }
#define ICMP_SEQ(response) response.hdr.un.echo.sequence

typedef struct s_socket {
	int					fd;
	struct sockaddr_in	addr;
} t_socket;

#define MSG_LEN 64 - sizeof(struct icmphdr)

typedef struct s_icmppkt
{
	struct icmphdr	hdr;
//	struct timeval	timestamp;
	char			msg[MSG_LEN];
}	t_icmppkt;

int		packet_exchange(t_socket socket);
//int		resolve_dns(char *host, struct sockaddr *addr);
void	init_icmphdr(t_icmppkt *pkt, int id);
int		resolve_host(char *host, t_socket *sock);


#endif
