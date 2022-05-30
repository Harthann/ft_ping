#include "ft_ping.h"


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

void	print_icmp_error(t_fullpkt packet, const char *hostname, const char *str)
{
	if (ICMP_TYPE(packet) == 11 && ICMP_CODE(packet) == 0)
	{
		fprintf(stdout, "64 bytes from %s (%s): ", hostname, str);
		fprintf(stdout, "icmp_seq=%d Time to live exceeded\n", g_stats.sended);
	}
	else if (g_flags.verbose)
	{
		fprintf(stdout, "64 bytes from %s (%s): ", "tmp", str);
		fprintf(stdout, "type = %d, code = %d \n", ICMP_TYPE(packet), ICMP_CODE(packet));
	}
	g_stats.errors++;
}

int		packet_exchange(t_socket sock, const char *target)
{
	float				time;
	struct	timeval		res_time;
	t_fullpkt			packet;
	char				*str;
	char				hostname[NI_MAXHOST];
	
	str = inet_ntoa(sock.addr.sin_addr);
	ft_memset(hostname, 0, sizeof(hostname));
	getnameinfo((struct sockaddr*)&sock.addr, sizeof(sock.addr),  hostname, sizeof(hostname), NULL, 0, 0);
	g_stats.sock = sock;
	fprintf(stdout, "FT_PING %s (%s)  56(84) bytes of data.\n", target, str);
	while(1) {
		alarm(1);
		if (receive(sock, &packet) >= 0)
		{
			if (ICMP_TYPE(packet) == 0)
			{
				fprintf(stdout, "64 bytes from %s (%s): ", hostname, str);
				if (gettimeofday(&res_time, NULL) < 0)
					fprintf(stderr, "Error getting time of day\n");
				time = diff_time(res_time, packet.packet.timestamp);
				update_stats_time(time);
				g_stats.success += 1;
				fprintf(stdout, "icmp_seq=%d ttl=%d time=%.2fms\n", g_stats.sended, g_flags.ttl, time);
			}
			else
				print_icmp_error(packet, hostname, str);
		}
	}
	return (0);
}
