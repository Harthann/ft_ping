#include <stdio.h>
#include <ft_ping.h>

t_stat	g_stats;
int		g_ttl = 64;

int		parser(int ac, char **av, char **host)
{
	char c;

	while ((c = ft_getopt(ac, av, "vht:")) != -1)
	{
		switch (c)
		{
			case 'v' :
				break;;
			case 't' :
				if (ft_optarg == NULL || !is_num(ft_optarg))
				{
					help();
					return -1;
				}
				g_ttl = ft_atoi(ft_optarg);
				break;;
			case 'h':
				help();
				return -1;
			case '?':
				help();
				return -1;
		}
	}
	if (av[ft_optind] == NULL)
		return -1;
	(*host) = av[ft_optind];
	return 0;
}

// This is a comment
int main(int ac, char **av)
{
	char		*host;
	t_socket	sock;

	if (parser(ac - 1, av + 1, &host) < 0)
		return (1);
	if (resolve_host(host, &sock) < 0)
		RETERROR(2, host, "Name or service not known\n");
	init_stats(host);
	if (setsockopt(sock.fd, IPPROTO_IP, IP_TTL, &g_ttl, sizeof(uint8_t)))
        fprintf(stderr, "Failed to setsockopt(): %s\n", strerror(errno));

	/*	Adding signal handling for statistics print	*/
	signal(SIGINT, sigint_handler);
	signal(SIGKILL, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGALRM, sigalrm_handler);
	packet_exchange(sock, host);
	return (0);
}
