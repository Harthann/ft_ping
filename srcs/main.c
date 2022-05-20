#include <stdio.h>
#include <ft_ping.h>

int help(void)
{
	printf("Usage:\nft_ping [options] destination\n\n");
	printf("Options:\n  destination\tdns or ip address\n  -v\t\tSomething\n  -h\t\tSomething\n");
	return (0);
}

char	*get_host(char **av)
{
	char *arg = *av;
	do
	{
		if (arg[0] != '-')
			break;
		av++;
		arg = *av;
	} while (av && *av);
	if (!arg)
		return (NULL);
	return (arg);
}

// This is a comment
int main(int ac, char **av)
{
	char		*host;
	t_socket	sock;

	if (ac < 2)
		return help();
	host = get_host(av + 1);
	if (!host)
		return help();
	if (resolve_host(host, &sock) < 0)
		RETERROR(2, host, "Name or service not known\n");
	packet_exchange(sock);
	return (0);
}
