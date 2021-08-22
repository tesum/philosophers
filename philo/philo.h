#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/*
	FORK	- WHITE
	EAT		- CYAN
	SLEEP	- PURPLE
	THINK	- YELLLOW
	DIE		- RED
*/
# define	FORK	" has taken a fork"
# define	EAT		" is eating"
# define	SLEEP	" is sleeping"
# define	THINK	" is thinking"
# define	DIE		" died"
# define	RED		"\033[0;31m"
# define	YELLOW	"\033[0;33m"
# define	PURPLE	"\033[0;35m"
# define	CYAN	"\033[0;36m"
# define	WHITE	"\033[0;37m"

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
	pthread_t		tid;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_config		*config;
	int				id;
	int				last_eat;
}				t_philo;

t_philo	*parce(int argc, char **argv, t_config *new);
int		start_day(t_philo *philos);
void	*die(void *philos);
int		get_time(int start);
void	my_sleep(int time);
void	logs(char *status, char *color, t_philo *philo);



#endif