#include "ft_ping.h"

float		diff_time(struct timeval a, struct timeval b)
{
	a.tv_sec -= b.tv_sec;
	a.tv_usec -= b.tv_usec;
	return ((float)a.tv_usec / 1000);
}

void	update_stats_time(float timer)
{
	if (timer < g_stats.min || g_stats.min == -1)
		g_stats.min = timer;
	if (timer > g_stats.max || g_stats.max == -1)
		g_stats.max = timer;
	g_stats.sum += timer;
}

int		receive(t_socket sock, t_fullpkt *packet)
{
	char	buffer[64];

	/* recvmsg struct initialisation */
	struct iovec	iov = {
		.iov_base = packet,
		.iov_len = sizeof(t_fullpkt)
	};
	struct msghdr	message = {
		.msg_iov = &iov,
		.msg_iovlen = 1,
		.msg_control = buffer,
		.msg_controllen = sizeof(buffer),
		.msg_flags = 0
	};

	errno = 0;
	if (recvmsg(sock.fd, &message, 0) < 0)
		RETERROR(-1, "error:", strerror(errno));
	return 0;
}

int		emit_icmp(t_socket sock)
{
	t_icmppkt	packet;

	init_icmphdr(&packet, g_stats.sended);
	errno = 0;
	if (sendto(sock.fd, &packet, sizeof(t_icmppkt), 0, (struct sockaddr*)&sock.addr, sizeof(struct sockaddr_in)) < 0)
		RETERROR(-1, "error:", strerror(errno));
	g_stats.sended++;
	return (0);
}

int		packet_exchange(t_socket sock, const char *target)
{
	float				time;
	struct	timeval		res_time;
	t_fullpkt			packet;
	char				*str;
   
	str = inet_ntoa(sock.addr.sin_addr);
	g_stats.sock = sock;
	fprintf(stdout, "FT_PING %s (%s)  56(84) bytes of data.\n", target, str);
	while(1) {
		alarm(1);
		if (receive(sock, &packet) >= 0)
		{
			if (ICMP_TYPE(packet) == 11 && ICMP_CODE(packet) == 0)
				fprintf(stdout, "64 bytes from %s (%s): icmp_seq=%d Time to live exceeded\n", "tmp", "tmp2", g_stats.sended);
			else
			{
				gettimeofday(&res_time, NULL);
				time = diff_time(res_time, packet.packet.timestamp);
				update_stats_time(time);
				g_stats.success += 1;
				fprintf(stdout, "64 bytes from %s (%s): icmp_seq=%d ttl=%d time=%.2fms\n", \
						"tmp", str, g_stats.sended, g_ttl, time);
			}
		}
	}
	return (0);
}
