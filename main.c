/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eradi- <eradi-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 01:22:39 by eradi-            #+#    #+#             */
/*   Updated: 2022/08/07 01:51:30 by eradi-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_check_death(void *phi)
{
	t_philo	*philo;
	int		j;

	philo = (t_philo *)phi;
	while (1)
	{
		j = -1;
		while (++j < philo->share->n_o_p)
		{
			// printf("this time of last eat %d\n",philo[j].last_eat);
			sem_wait(philo->share->last_eat);
			if ((time_now() - philo[j].last_eat) >= (philo->share->time_to_die))
			{
				ft_print(j, philo, "is died");
				return (0);
			}
			sem_post(philo->share->last_eat);
			// sem_wait(philo->share->how_much_eating);
			// if (philo->share->number_of_times_each_philosopher_must_eat
			// 	&& check_time_of_eating(philo, j) == 0)
			// 	return (0);
			// sem_post(philo->share->how_much_eating);
		}
	}
	return (1);
}

void	ft_print(int j, void *phii, const char *s)
{
	t_philo		*philo;
	const char	*str;
	const char	*str1;
	philo = (t_philo *)phii;
	str = "is died";
	str1 = "stop";
	if (s == str1)
		return ;
	printf("%d ms %d %s \n",ft_time(philo), j + 1, s);
	if (s == str)
		return ;
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
		sem_wait(philo->share->last_eat);
		philo->last_eat = time_now();
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
		int philo[200];
		t_sharing *share;
		pthread_t	*philo_shinigami;
		t_philo		*philo_struct;
		philo_shinigami = malloc(i * sizeof(pthread_t));
		share = malloc(1 * sizeof(t_sharing));
		philo_struct = malloc(1 * sizeof(t_philo));
		sem_unlink("./print");
		sem_unlink("./last_eat");
		sem_unlink("./how_much_eating");
		share->how_much_eating = sem_open("./how_much_eating",O_CREAT,0660,1);
		share->print = sem_open("./print",O_CREAT,0660,1);
		share->last_eat = sem_open("./last_eat",O_CREAT,0660,1);
		for_share(share, av);
		philo_struct->share = share;
		j = 0;
		while(j < i)
		{
			if ((philo[j] = fork()) < 0)
				printf("error");
			else if (philo[j] == 0)
			{
				philo_struct[0].id = j;
				philo_struct[0].last_eat = time_now();
				do_it(&philo_struct[0]);
			}
			usleep(100);
			j++;
		}
		while(1)
		{
			if (ft_check_death(philo_struct) == 0)
				exit(0);
		}
		int status;
		while(waitpid( -1,&status, 0) != -1)
			;
		sem_close(share->fork);
		sem_close(share->how_much_eating);
		sem_close(share->print);
		sem_close(share->last_eat);
	}
	return (0);
}
