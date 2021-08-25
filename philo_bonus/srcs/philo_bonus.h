/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demilan <demilan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 13:38:15 by demilan           #+#    #+#             */
/*   Updated: 2021/08/25 20:42:19 by demilan          ###   ########.fr       */
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
# include <signal.h>

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
	int			ceat;
	int			dead;
}				t_philo;

void	*die(void *philos);
void	my_sleep(int time);
void	parce(int argc, char **argv, t_config *new);
void	all_clear(t_philo *philos, t_config	*config);
int		start_day(t_philo *philos);
int		get_time(int start);
int		logs(char *status, char *color, t_philo *philo);

#endif