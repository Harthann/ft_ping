#include <ft_ping.h>


int help(void)
{
	printf("Usage:\nft_ping [options] destination\n\n");
	printf("Options:\n  destination\tdns or ip address\n  -v\t\tSomething\n  -h\t\tSomething\n");
	return (0);
}

void init_stats(char *target)
{
	g_stats.target = target;
	g_stats.sended = 0;
	g_stats.success = 0;
	g_stats.min = -1;
	g_stats.max = -1;
	gettimeofday(&g_stats.start, NULL);
}

int		ft_atoi(const char *str)
{
	int		nb;
	int		sign;

	nb = 0;
	sign = 1;
	while ((*str == 32 || (*str >= 9 && *str <= 13)) && *str)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while ((*str >= '0' && *str <= '9') && *str)
	{
		nb = nb * 10 + *str - 48;
		str++;
	}
	return (nb * sign);
}

int		is_num(const char* str)
{
	while(str && *str)
	{
		if (*str > '9' || *str < '0')
			return 0;
		str++;
	}
	return 1;
}
