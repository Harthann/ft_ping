#include "ft_ping.h"

float		diff_time(struct timeval a, struct timeval b)
{
	a.tv_sec -= b.tv_sec;
	a.tv_usec -= b.tv_usec;
	return ((float)a.tv_usec / 1000);
}

int		receive(t_socket sock, t_fullpkt *packet)
{
	char				buffer[64];

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

int		emit_icmp(t_socket sock, int id)
{
	t_icmppkt	packet;

	init_icmphdr(&packet, id);
	errno = 0;
	if (sendto(sock.fd, &packet, sizeof(t_icmppkt), 0, (struct sockaddr*)&sock.addr, sizeof(struct sockaddr_in)) < 0)
		RETERROR(-1, "error:", strerror(errno));
	return (0);
}

int		packet_exchange(t_socket sock)
{
	float				time;
	struct	timeval		res_time;
	t_fullpkt			packet;

	while(1) {
		if (emit_icmp(sock, g_stats.id++) < 0)
			return -1;
		if (receive(sock, &packet) < 0)
			return -1;
		gettimeofday(&res_time, NULL);
		time = diff_time(res_time, packet.packet.timestamp);
		fprintf(stdout, "64 bytes from %s (%s): icmp_seq=%d ttl=%d time=%.2fms\n", "tmp", "tmp2", ICMP_SEQ(packet.packet), -1, time);
	}
	return (0);
}
