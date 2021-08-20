#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>


/*
	[int] count philo
	[int] ttd - time to die
	[int] tte - time to eat
	[int] tts - time to sleep
	[int] ene - each need eat
*/
typedef struct s_config
{
	int				count_philo;
	int				ttd;
	int				tte;
	int				tts;
	int				ene;
	int				die;
	int				start_time;
	pthread_mutex_t	message;
}				t_config;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_config		*config;
}				t_philo;

t_philo	*parce(int argc, char **argv, t_config *new);
int		start_day(t_philo *philos);

#endif