#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <time.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <inttypes.h>
# include <sys/wait.h>
# include <semaphore.h>
typedef struct s_sharing
{
	sem_t	print;
	sem_t	*fork;
	sem_t	last_eat;
	sem_t	lets_break;
	sem_t	how_much_eating;
}	t_sharing;

// typedef struct s_sharing
// {
// 	int				id;
// 	int				start_time;
// 	int				time_to_die;
// 	int				time_to_eat;
// 	int				time_to_sleep;
// 	int				time_to_break;
// 	int				n_o_p;
// 	int				number_of_times_each_philosopher_must_eat;
// 	int				time_of_repeat;
// 	pthread_mutex_t	print;
// 	pthread_mutex_t	*fork;
// 	pthread_mutex_t	last_eat;
// 	pthread_mutex_t	lets_break;
// 	pthread_mutex_t	how_much_eating;
// }	t_sharing;
int		ft_check_integer(int ac, char **av);
int		ft_atoi(const char *str);
int		time_now(void);
int		ft_time(void *phi);
void	ft_put_time(void *phi);
void	my_usleep(long ti);
//void	for_share(t_sharing *share, char **av);
void	ft_print(int j, void *phii, const char *s);
//int		check_time_of_eating(t_philo *philo, int j);
# endif