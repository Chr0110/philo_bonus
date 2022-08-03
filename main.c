#include "philo_bonus.h"
void	*do_it(void *s, int j)
{
	t_sharing	*share;
	share = (t_sharing *)s;
	sem_wait(&share->fork[j]);
	printf("philo %d has taken a fork\n",j);
	sem_post(&share->fork[j]);
	sem_wait(&share->fork[j + 1]);
	printf("philo %d has taken a fork 2\n",j);
	sem_post(&share->fork[j + 1]);
	return (NULL);
}
int	main(int ac, char **av)
{
	if ((ac == 5 || ac == 6) && (ft_check_integer(ac, av) == 0))
	{
		int i = ft_atoi(av[1]);
		int j = 1;
		int philo[100];
		t_sharing *share;
		share = malloc(1 * sizeof(t_sharing));
		sem_init(&share->how_much_eating,0,0);
		sem_init(&share->last_eat,0,0);
		sem_init(&share->how_much_eating,0,0);
		while(j < i)
			sem_init(&share->fork[j],0,0);
		while(j <= i)
		{
			if ((philo[i] = fork()) < 0)
				perror("fork");
			else if (philo[i] == 0)
			{
    			do_it(share, j);
    			return(0);
			}
			j++;
		}
	}
	return (0);
}
