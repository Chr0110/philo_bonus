/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eradi- <eradi-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:39:14 by eradi-            #+#    #+#             */
/*   Updated: 2022/08/09 03:28:03 by eradi-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	my_usleep(long ti)
{
	long	timetowake;

	timetowake = time_now() + ti;
	while (timetowake > time_now())
		usleep(10);
}

void	for_share(t_sharing *share, char **av)
{
	share->n_o_p = ft_atoi(av[1]);
	share->time_to_die = ft_atoi(av[2]);
	share->time_to_eat = ft_atoi(av[3]);
	share->time_to_sleep = ft_atoi(av[4]);
	share->start_time = time_now();
	sem_unlink("./fork");
	sem_unlink("./print");
	sem_unlink("./last_eat");
	sem_unlink("./how_much_eating");
	share->how_much_eating = sem_open("./how_much_eating", O_CREAT, 0660, 1);
	share->print = sem_open("./print", O_CREAT, 0660, 1);
	share->last_eat = sem_open("./last_eat", O_CREAT, 0660, 1);
	share->fork = sem_open("./fork", O_CREAT, 0660, share->n_o_p);
	if (av[5])
		share->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
}

void	ft_print(int j, void *phii, const char *s)
{
	t_philo		*philo;
	const char	*str;

	philo = (t_philo *)phii;
	str = "is died";
	sem_wait(philo->share->print);
	printf("%d ms %d %s \n", ft_time(philo), j + 1, s);
	if (s == str)
		exit(0);
	sem_post(philo->share->print);
}
