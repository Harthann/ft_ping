#ifndef FT_PING_H
# define FT_PING_H


/*==========*/
/*	INCLUDE	*/
/*==========*/
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <signal.h>
#include <float.h>

#include <errno.h>

#include "parser.h"

/*==========*/
/*	MACROS	*/
/*==========*/
#define RETERROR(value, args...) { fprintf(stderr, "ft_ping: %s %s", ##args); return value; }
#define ICMP_SEQ(x) x.packet.hdr.un.echo.sequence
#define ICMP_TYPE(x) x.packet.hdr.type
#define ICMP_CODE(x) x.packet.hdr.code

#define MSG_LEN 64 - sizeof(struct icmphdr) - sizeof(struct timeval)

#define DEBUG 1

#if defined(DEBUG)
	#define DPRINT(fmt, args...) fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, \
		__FILE__, __LINE__, __func__, ##args)
#else
	#define DPRINT(fmt, args...)
#endif


/*==============*/
/*	STRUCTURES	*/
/*==============*/

typedef struct s_socket {
	int					fd;
	struct sockaddr_in	addr;
} t_socket;


typedef struct s_icmppkt
{
	struct icmphdr	hdr;
	struct timeval	timestamp;
	char			msg[MSG_LEN];
}	t_icmppkt;

typedef struct s_fullpkt {
	struct iphdr	ip; 
	t_icmppkt		packet;
}	__attribute__((packed)) t_fullpkt;

typedef struct s_stat {
	struct timeval	start;
	char			*target;
	int				sended;
	int				success;
	float			min;
	float			max;
	float			sum;
	t_socket		sock;
}			t_stat;

/*==========*/
/*	GLOBALS	*/
/*==========*/

extern t_stat	g_stats;
extern int		g_ttl;

/*==============*/
/*	PROTOTYPE	*/
/*==============*/

/*		ICMP	*/
int			packet_exchange(t_socket sock, const char *target);
void		init_icmphdr(t_icmppkt *pkt, int id);
int			resolve_host(char *host, t_socket *sock);
uint16_t	compute_checksum(uint16_t *addr, size_t count);
void		dbg_dump_bytes(const void* data, size_t size);
int			emit_icmp(t_socket sock);

/*		UTILS	*/
float		diff_time(struct timeval a,struct timeval b);
int			ft_atoi(const char *str);
void		init_stats(char *target);
int			help(void);
int			is_num(const char* str);

/*		SIGNALS		*/
void		sigint_handler(int signal);
void		sigquit_handler(int signal);
void		sigalrm_handler(int signal);

#endif
