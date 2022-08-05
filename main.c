#include "philo_bonus.h"
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
	sem_wait(philo->share->fork);
	printf("%d ms %d %s \n",ft_time(philo), j + 1, s);
	if (s == str)
		return ;
	sem_post(philo->share->fork);
}

void	for_share(t_sharing *share, char **av)
{
	share->n_o_p = ft_atoi(av[1]);
	share->time_to_die = ft_atoi(av[2]);
	share->time_to_eat = ft_atoi(av[3]);
	share->time_to_sleep = ft_atoi(av[4]);
	share->start_time = time_now();
	if (av[5])
		share->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
}

void	*do_it(void *p)
{
	t_philo	*philo;
	philo = (t_philo *)p;
	sem_wait(philo->share->fork);
	ft_print(philo->id, philo, "has taken a fork");
	sem_post(philo->share->fork);
	sem_wait(philo->share->fork);
	ft_print(philo->id, philo, "has taken a fork2");
	sem_post(philo->share->fork);
	return (NULL);
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
		sem_unlink("how_much_eating");
		sem_unlink("print");
		sem_unlink("last_eat");
		sem_unlink("how_much_eating");
		sem_unlink("fork");
		share->how_much_eating = sem_open("/how_much_eating",O_CREAT,0660,1);
		share->print = sem_open("/print",O_CREAT,0660,1);
		share->last_eat = sem_open("/last_eat",O_CREAT,0660,1);
		share->how_much_eating = sem_open("/how_much_eating",O_CREAT,0660,1);
		philo_struct[0].share = share;
		for_share(share, av);
		while(j < i) 
		{
			share->fork = sem_open("/fork",O_CREAT,O_RDWR,0660,share->n_o_p);
			j++;
		}
		j = 0;
		while(j < i)
		{
			if ((philo[j] = fork()) < 0)
				perror("fork");
			else if (philo[j] == 0)
			{
				philo_struct[0].id = j;
				philo_struct[0].last_eat = time_now();
				do_it(&philo_struct[0]);
				return(0);
			}
			usleep(100);
			j++;
		}
	}
	return (0);
}
