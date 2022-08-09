/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eradi- <eradi-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 01:22:39 by eradi-            #+#    #+#             */
/*   Updated: 2022/08/09 07:28:47 by eradi-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_check_eating(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	while (1)
	{
		sem_wait(philo->share->last_eat);
		if (philo->last_eat
			> philo->share->number_of_times_each_philosopher_must_eat)
			exit(0);
		sem_post(philo->share->last_eat);
	}
	return (1);
}

int	ft_check_death(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	while (1)
	{
		sem_wait(philo->share->finish_eating);
		if (time_now() - philo->finish_eating >= philo->share->time_to_die)
		{
			ft_print(philo->id, philo, "is died");
			exit(0);
		}
		sem_post(philo->share->finish_eating);
	}
	return (1);
}

void	*do_it(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		sem_wait(philo->share->fork);
		ft_print(philo->id, philo, "has taken a fork");
		sem_wait(philo->share->fork);
		ft_print(philo->id, philo, "has taken a fork2");
		ft_print(philo->id, philo, "is eating");
		sem_wait(philo->share->last_eat);
		philo->last_eat++;
		sem_post(philo->share->last_eat);
		my_usleep(philo->share->time_to_eat);
		sem_wait(philo->share->finish_eating);
		philo->finish_eating = time_now();
		sem_post(philo->share->finish_eating);
		sem_post(philo->share->fork);
		sem_post(philo->share->fork);
		ft_print(philo->id, philo, "is sleeping");
		my_usleep(philo->share->time_to_sleep);
		ft_print(philo->id, philo, "is thinking");
	}
	exit(0);
}

void	ft_creat_process(int j, t_philo *philo_struct, char **av, int *philo)
{
	pthread_t	*philo_shinigami;
	pthread_t	*philo_shinigami2;

	philo_shinigami = malloc(ft_atoi(av[1]) * sizeof(pthread_t));
	philo_shinigami2 = malloc(ft_atoi(av[1]) * sizeof(pthread_t));
	while (j < ft_atoi(av[1]))
	{
		philo[j] = fork();
		if (philo[j] == 0)
		{
			philo_struct[0].id = j;
			philo_struct[0].pid = philo[j];
			philo_struct[0].last_eat = 0;
			philo_struct[0].finish_eating = time_now();
			if (av[5])
				pthread_create(&philo_shinigami[j], NULL,
					(void *)ft_check_eating, &philo_struct[0]);
			pthread_create(&philo_shinigami2[j], NULL,
				(void *)ft_check_death, &philo_struct[0]);
			do_it(&philo_struct[0]);
		}
		usleep(1000);
		j++;
	}
}

int	main(int ac, char **av)
{
	int			j;
	int			status;
	t_sharing	*share;
	t_philo		*philo_struct;
	int			philo[200];

	if ((ac == 5 || ac == 6) && (ft_check_integer(ac, av) == 0))
	{
		j = 0;
		share = malloc(1 * sizeof(t_sharing));
		philo_struct = malloc(1 * sizeof(t_philo));
		for_share(share, av);
		philo_struct->share = share;
		ft_creat_process(j, philo_struct, av, philo);
		waitpid(-1, &status, 0);
		while (j < ft_atoi(av[1]))
		{
			kill(philo[j], SIGKILL);
			j++;
		}
	}
	return (0);
}
