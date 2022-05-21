#ifndef FT_PING_H
# define FT_PING_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
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

#define MSG_LEN 64 - sizeof(struct icmphdr)// - sizeof(struct timeval)

typedef struct s_icmppkt
{
	struct icmphdr	hdr;
//	struct timeval	timestamp;
	char			msg[MSG_LEN];
}	t_icmppkt;

int		packet_exchange(t_socket socket);
void	init_icmphdr(t_icmppkt *pkt, int id);
int		resolve_host(char *host, t_socket *sock);
uint16_t	compute_checksum(unsigned char *addr, size_t count);
void dbg_dump_bytes(const void* data, size_t size);


#endif
