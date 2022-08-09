/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eradi- <eradi-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:38:16 by eradi-            #+#    #+#             */
/*   Updated: 2022/08/09 03:24:27 by eradi-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int			sign;
	long int	nb;
	char		*p;
	int			i;

	p = (char *)str;
	sign = 1;
	while ((*p >= 9 && *p <= 13) || *p == ' ')
		p++;
	if (*p == '-' || *p == '+')
	{
		if (*p == '-')
			sign *= -1;
		p++;
	}
	nb = 0;
	i = 0;
	while (p[i] >= '0' && p[i] <= '9')
		nb = (nb * 10) + p[i++] - '0';
	if (nb > 4294967295)
		return (0);
	return (sign * nb);
}

int	time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

int	ft_time(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	return (time_now() - philo->share->start_time);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_check_integer(int ac, char **av)
{
	int	i;
	int	x;

	x = -1;
	i = 0;
	while (++i < ac)
	{
		while (++x < ft_strlen(av[i]))
		{
			if (ft_atoi(av[i]) == 0)
				return (1);
			if ((av[i][x] >= '0' && av[i][x] <= '9') && (av[i][x + 1] == '-'
				|| av[i][x + 1] == '+'))
				return (1);
			if (ft_strlen(av[i]) == 1 && (av[i][0] >= '0' && av[i][0] <= '9')
				&& av[i][0] == '0')
				return (1);
			if (!((av[i][x] >= '0') && (av[i][x] <= '9')))
				return (1);
		}
		x = -1;
	}
	return (0);
}
