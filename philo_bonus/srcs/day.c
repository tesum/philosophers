/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsenijdrozdov <arsenijdrozdov@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 13:38:03 by demilan           #+#    #+#             */
/*   Updated: 2021/08/24 14:21:49 by arsenijdroz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	pdie(t_philo *philo, t_config *cnf)
{
	if (get_time(cnf->start_time) - philo->last_eat > cnf->ttd)
	{
		logs(DIE, RED, philo);
		philo->config->die = 1;
		// sem_wait()
		exit(0);
		return (1);
	}
	return (0);
}

void	*die(void *philos)
{
	t_philo		*philo;
	t_config	*cnf;
	int			i;

	philo = philos;
	cnf = philo->config;
	while (1)
	{
		i = 0;
		while (i < cnf->count_philo)
		{
			if (pdie(&philo[i], cnf))
				return ((void *) 1);
			if (cnf->eat_now >= cnf->ene * cnf->count_philo && cnf->ene > 0)
			{
				// pthread_mutex_lock(&philo->config->message);
				return ((void *) 1);
			}
			i++;
		}
	}
	return ((void *)0);
}

void	*day(void *philo_)
{
	t_philo	*philo;

	philo = (t_philo *)philo_;
	while (1)
	{
		sem_wait(philo->config->fork);
		logs(FORK, WHITE, philo);
		sem_wait(philo->config->fork);
		logs(FORK, WHITE, philo);
		logs(EAT, CYAN, philo);
		philo->last_eat = get_time(philo->config->start_time);
		philo->config->eat_now += 1;
		my_sleep(philo->config->tte);
		sem_post(philo->config->fork);
		sem_post(philo->config->fork);
		logs(SLEEP, PURPLE, philo);
		my_sleep(philo->config->tts);
		logs(THINK, YELLOW, philo);
	}
	return ((void *)0);
}

int	start_day(t_philo *philos)
{
	int			i;
	pthread_t	tid;

	i = 0;
	if (pthread_create(&tid, NULL, die, (void *)&philos[0]))
		return (1);	
	while (i < philos[i].config->count_philo - 1)
	{
		philos->config->pid[i] = fork();
		if (philos->config->pid[i] == 0)
		{
			day(&philos[i]);
			i = philos->config->count_philo;
		}
		// if (pthread_create(&philos[i].tid, NULL, day, (void *)&philos[i]))
		// 	return (1);
		// pthread_detach(philos[i].tid);
		// usleep(50);
		i++;
	}
	// if (pthread_create(&philos->tid, NULL, day, (void *)&philos[i]))
	// 	return (1);
	pthread_join(tid, NULL);
	return (0);
}

void	all_clear(t_philo *philos, pthread_mutex_t *fork, t_config	config)
{
	int	i;

	i = 0;
	while (i < config.count_philo)
	{
		// pthread_mutex_destroy(&fork[i]);
		i++;
	}
	free(fork);
	free(philos);
	// pthread_mutex_destroy(&config.message);
}
