#include "ft_ping.h"

int		receive(t_socket sock, t_icmppkt *packet)
{
	char			buffer[64];
	int				error;
	struct iovec	iov = {
		.iov_base = packet,
		.iov_len = sizeof(t_icmppkt)
	};
	struct msghdr	message = {
		.msg_iov = &iov,
		.msg_iovlen = 1,
		.msg_control = buffer,
		.msg_controllen = sizeof(buffer),
		.msg_flags = 0
	};

	errno = 0;
	error = recvmsg(sock.fd, &message, 0);
	if (error < 0)
		RETERROR(-1, "error:", strerror(errno));
	return 0;
}

int		emit_icmp(t_socket sock, int id)
{
	t_icmppkt	packet;
	int			error;

	init_icmphdr(&packet, id);
	//fprintf(stdout, "size {%ld} {%ld} {%ld}\n", sizeof(t_icmppkt), sizeof(struct iphdr), sizeof(struct timeval));
	fprintf(stderr, "Checksum {%d} {%ld}\n", packet.hdr.checksum, sizeof(t_icmppkt));
	errno = 0;
	dbg_dump_bytes(&packet, sizeof(t_icmppkt));
	error = sendto(sock.fd, &packet, sizeof(t_icmppkt), 0, (struct sockaddr*)&sock.addr, sizeof(struct sockaddr_in));
	if (error < 0)
		RETERROR(-1, "error:", strerror(errno));
	return (0);
}

int		packet_exchange(t_socket sock)
{
	t_icmppkt response;
	int			id =1;

	while(1) {
		if (emit_icmp(sock, id++) < 0)
			return -1;
		if (receive(sock, &response) < 0)
			return -1;
		dbg_dump_bytes(&response, sizeof(t_icmppkt));
//		fprintf(stdout, "64 bytes from %s (%s): icmp_seq=%d ttl=%d time=%dms\n", "tmp", "tmp2", ICMP_SEQ(response), -1, -1);
		sleep(1);
	}

	return (0);
}
