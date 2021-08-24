/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsenijdrozdov <arsenijdrozdov@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 13:38:15 by demilan           #+#    #+#             */
/*   Updated: 2021/08/24 13:29:10 by arsenijdroz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

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
	int		count_philo;
	int		ttd;
	int		tte;
	int		tts;
	int		ene;
	int		die;
	int		start_time;
	int		eat_now;
	pid_t	*pid;
	sem_t	*fork;
	sem_t	*message;
	sem_t	*eat_check;
}				t_config;

typedef struct s_philo
{
	pthread_t	tid;
	t_config	*config;
	int			id;
	int			last_eat;
	int			dead;
}				t_philo;

void	parce(int argc, char **argv, t_config *new);
int		start_day(t_philo *philos);
void	*die(void *philos);
int		get_time(int start);
void	my_sleep(int time);
int		logs(char *status, char *color, t_philo *philo);
void	all_clear(t_philo *philos, pthread_mutex_t *fork, t_config	config);

#endif