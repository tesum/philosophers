#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

/*
	[int] count philo
	[int] ttd - time to die
	[int] tte - time to eat
	[int] tts - time to sleep
	[int] ene - each need eat
*/
typedef struct s_config
{
	int	count_philo;
	int	ttd;
	int	tte;
	int	tts;
	int	ene;
	int	die;
}				t_config;

typedef struct s_philo
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_config	*conf;
}				t_philo;

void	parce(int argc, char **argv, t_config *new);
#endif