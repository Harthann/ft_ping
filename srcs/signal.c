#include "ft_ping.h"

void	sigint_handler(int signal)
{
	(void)signal;
	struct timeval	tmp;
	float			elapsed_time;

	gettimeofday(&tmp, NULL);
	elapsed_time = diff_time(tmp, g_stats.start);
	fprintf(stdout, "\n--- %s ft_ping statistics ---\n", g_stats.target);
	fprintf(stdout, "%d packets transmitted, %d received, %.3f%% packet loss, time=%.2fms\n", \
			g_stats.sended, g_stats.success, (float)(g_stats.sended - g_stats.success) / (float)g_stats.sended * 100.0, elapsed_time);
	if (g_stats.min != -1 && g_stats.max != -1)
		fprintf(stdout, "rtt min/avg/max = %.3f/%.3f/%.3f ms\n", g_stats.min, g_stats.sum / g_stats.success, g_stats.max);
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
}
