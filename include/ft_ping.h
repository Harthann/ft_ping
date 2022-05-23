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
#include <signal.h>

#include <errno.h>


#define RETERROR(value, args...) { fprintf(stderr, "ft_ping: %s %s", ##args); return value; }
#define ICMP_SEQ(response) response.hdr.un.echo.sequence

typedef struct s_socket {
	int					fd;
	struct sockaddr_in	addr;
} t_socket;

#define MSG_LEN 64 - sizeof(struct icmphdr) - sizeof(struct timeval)

typedef struct s_icmppkt
{
	struct icmphdr	hdr;
	struct timeval	timestamp;
	char			msg[MSG_LEN];
}	t_icmppkt;

typedef struct s_fullpkt {
	struct iphdr ip; 
	t_icmppkt packet;
}	__attribute__((packed)) t_fullpkt;

typedef struct s_stat {
	struct timeval	start;
	int				id;
	int				success;
}			t_stat;



int			packet_exchange(t_socket socket);
void		init_icmphdr(t_icmppkt *pkt, int id);
int			resolve_host(char *host, t_socket *sock);
void		signal_handler(int signal);
uint16_t	compute_checksum(uint16_t *addr, size_t count);
void		dbg_dump_bytes(const void* data, size_t size);


#endif
