#include "ft_ping.h"

int		ft_optind = 0;
char	ft_optopt = 0;
char	*ft_optarg = 0;

static	void	next_opt(int ac, char **av, int *nexti, int *nextj)
{
	(void)ac;
	(*nextj)++;
	if (av[*nexti][*nextj] == 0)
	{
		(*nexti)++;
		*nextj = 1;
	}
}

/*
 **	Litle reimplementation of getopt lib
 **	
 */
char	ft_getopt(int ac, char **av, const char *flags)
{
	static int nexti = 0;
	static int nextj = 1;

	ft_optind = nexti;
	if (nexti >= ac || av[nexti][0] != '-')
		return -1;
	ft_optopt = av[nexti][nextj];
	for (int i = 0; flags && flags[i]; i++)
	{
		if (flags[i] == ft_optopt)
		{
			if (flags[i + 1] && flags[i + 1] != ':')
			{
				next_opt(ac, av, &nexti, &nextj);
				return ft_optopt;
			}
			if (av[nexti][nextj + 1])
			{
				ft_optarg = av[nexti] + nextj + 1;
				nexti++;
				nextj = 1;
				return ft_optopt;
			}
			ft_optarg = av[nexti + 1];
			nexti += 2;
			nextj = 1;
			return ft_optopt;
		}
	}
	return '?';
}
