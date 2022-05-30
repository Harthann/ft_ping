#include <ft_ping.h>


int help(void)
{
	printf("Usage:\nft_ping [options] destination\n\n");
	printf("Options:\n  destination\tdns or ip address\n  -v\t\tSomething\n  -h\t\tSomething\n");
	return (0);
}

float		diff_time(struct timeval a, struct timeval b)
{
	a.tv_sec -= b.tv_sec;
	a.tv_usec -= b.tv_usec;
	return ( ((float)a.tv_sec * 1000000 + (float)a.tv_usec) / 1000);
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

void		ft_memset(void *addr, const char value, size_t size)
{
	while (size)
		((char*)addr)[size--] = value;
}

float		ft_sqrt(float nb, float x)
{
	for (int i = 0; i < 10; i++)
		x -= (x * x - nb) / (2 * x);
	return (x);
}

/*	UTILS STATS	*/

void init_stats(char *target)
{
	g_stats.target = target;
	g_stats.sended = 0;
	g_stats.success = 0;
	g_stats.min = -1;
	g_stats.max = -1;
	g_stats.sum = 0;
	g_stats.tsum = 0;
	g_stats.tsum2 = 0;
	g_stats.errors = 0;
	if (gettimeofday(&g_stats.start, NULL) < 0)
		fprintf(stderr, "Error getting time of day\n");
}

void	update_stats_time(float timer)
{
	if (timer < g_stats.min || g_stats.min == -1)
		g_stats.min = timer;
	if (timer > g_stats.max || g_stats.max == -1)
		g_stats.max = timer;
	g_stats.sum += timer;
	g_stats.tsum += timer;
	g_stats.tsum2 += timer * timer;
}
