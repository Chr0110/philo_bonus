/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eradi- <eradi-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 01:22:39 by eradi-            #+#    #+#             */
/*   Updated: 2022/08/09 02:49:14 by eradi-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_check_eating(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	while (1)
	{
		if (philo->last_eat > philo->share->number_of_times_each_philosopher_must_eat)
			exit(0);
	}
	return (1);
}

int	ft_check_death(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	while (1)
	{
		if (time_now() - philo->finish_eating >= philo->share->time_to_die)
		{
			ft_print(philo->id, philo, "is died");
			exit(0);
		}
	}
	return (1);
}

void	ft_print(int j, void *phii, const char *s)
{
	t_philo		*philo;
	philo = (t_philo *)phii;
	const char *str;
	str = "is died";
	sem_wait(philo->share->print);
	printf("%d ms %d %s \n",ft_time(philo), j + 1, s);
	if (s == str)
		exit(0);
	sem_post(philo->share->print);
}

void	*do_it(void *p)
{
	t_philo	*philo;
	while(1)
	{
		philo = (t_philo *)p;
		sem_wait(philo->share->fork);
		ft_print(philo->id, philo, "has taken a fork");
		sem_wait(philo->share->fork);
		ft_print(philo->id, philo, "has taken a fork2");
		ft_print(philo->id, philo, "is eating");
		my_usleep(philo->share->time_to_eat);
		philo->finish_eating = time_now();
		sem_wait(philo->share->last_eat);
		philo->last_eat++;
		sem_post(philo->share->last_eat);
		sem_post(philo->share->fork);
		sem_post(philo->share->fork);
		ft_print(philo->id, philo, "is sleeping");
		my_usleep(philo->share->time_to_sleep);
		ft_print(philo->id, philo, "is thinking");
	}
		exit(0);
}

int	main(int ac, char **av)
{
	if ((ac == 5 || ac == 6) && (ft_check_integer(ac, av) == 0))
	{
		int i = ft_atoi(av[1]);
		int j = 0;
		int status;
		int philo[200];
		t_sharing *share;
		pthread_t	*philo_shinigami;
		pthread_t	*philo_shinigami2;
		t_philo		*philo_struct;
		philo_shinigami = malloc(i * sizeof(pthread_t));
		philo_shinigami2 = malloc(i * sizeof(pthread_t));
		share = malloc(1 * sizeof(t_sharing));
		philo_struct = malloc(1 * sizeof(t_philo));
		for_share(share, av);
		philo_struct->share = share;
		j = 0;
		while(j < i)
		{
			if ((philo[j] = fork()) == 0)
			{
				philo_struct[0].id = j;
				philo_struct[0].pid = philo[j];
				philo_struct[0].last_eat = 0;
				philo_struct[0].finish_eating = time_now();
				if (av[5])
					pthread_create(&philo_shinigami[j], NULL, (void *)ft_check_eating, &philo_struct[0]);
				pthread_create(&philo_shinigami2[j], NULL, (void *)ft_check_death, &philo_struct[0]);
				do_it(&philo_struct[0]);
			}
			usleep(1000);
			j++;
		}
		j = 0;
		waitpid(-1, &status, 0);
		while (j < i)
		{
			kill(philo[j], SIGKILL);
			j++;
		}
	}
	return (0);
}
