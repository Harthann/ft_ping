#include "ft_ping.h"

void	sigint_handler(int signal)
{
	(void)signal;
	struct timeval	tmp;
	float			elapsed_time;

	errno = 0;
	if (gettimeofday(&tmp, NULL) < 0)
		fprintf(stderr, "Error getting time of day\n");
	elapsed_time = diff_time(tmp, g_stats.start);
	fprintf(stdout, "\n--- %s ft_ping statistics ---\n", g_stats.target);
	fprintf(stdout, "%d packets transmitted, %d received, ", g_stats.sended, g_stats.success);
	if (g_stats.errors != 0)
		fprintf(stdout, "+%d errors, ", g_stats.errors);
	fprintf(stdout, "%.3f%% packet loss, time=%.0fms\n", \
			(float)(g_stats.sended - g_stats.success) / (float)g_stats.sended * 100.0, elapsed_time);
	if (g_stats.min != -1 && g_stats.max != -1)
	{
		g_stats.tsum /= g_stats.success;
		g_stats.tsum2 /= g_stats.success;
		fprintf(stdout, "rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n", g_stats.min, g_stats.sum / g_stats.success, g_stats.max, ft_sqrt(g_stats.tsum2 - g_stats.tsum * g_stats.tsum, 2));
	}
	exit (0);
}

void	sigquit_handler(int signal)
{
	(void)signal;
	fprintf(stdout, "\b\b%d/%d packets, %.3f%% loss", g_stats.success, g_stats.sended, (float)(g_stats.sended - g_stats.success)/ (float)g_stats.sended * 100.0);
	if (g_stats.min != -1 && g_stats.max != -1)
		fprintf(stdout, ", min/avg/max = %.3f/%.3f/%.3f ms\n", \
			g_stats.min, g_stats.sum / g_stats.success, g_stats.max);
	else
		fprintf(stdout, "\n");
}

void	sigalrm_handler(int signal)
{
	(void)signal;
	emit_icmp(g_stats.sock);
	alarm(1);
}
