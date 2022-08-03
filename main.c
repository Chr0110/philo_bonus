#include "philo_bonus.h"
void	do_it()
{
	
}
int	main(int ac, char **av)
{
	if ((ac == 5 || ac == 6) && (ft_check_integer(ac, av) == 0))
	{
		int i = ft_atoi(av[1]);
		int j = 0;
		int philo[100];
		while(j < i)
		{
			if ((philo[i] = fork()) < 0)
			{
				perror("fork");
			}
			else if (philo[i] == 0)
			{
    			do_it();
    			return(0);
			}
			j++;
		}
	}
	return (0);
}
