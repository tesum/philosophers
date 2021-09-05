/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsenijdrozdov <arsenijdrozdov@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 13:38:03 by demilan           #+#    #+#             */
/*   Updated: 2021/09/05 20:25:57 by arsenijdroz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pdie(t_philo *philo, t_config *cnf)
{
	if (get_time(cnf->start_time) - philo->last_eat > cnf->ttd)
	{
		philo->config->die = 1;
		logs(DIE, RED, philo);
		philo->config->stop = 1;
		pthread_mutex_lock(&philo->config->message);
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
				pthread_mutex_lock(&philo->config->message);
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
		pthread_mutex_lock(philo->left);
		logs(FORK, WHITE, philo);
		pthread_mutex_lock(philo->right);
		logs(FORK, WHITE, philo);
		logs(EAT, CYAN, philo);
		philo->last_eat = get_time(philo->config->start_time);
		philo->config->eat_now += 1;
		my_sleep(philo->config->tte);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
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
	if (pthread_create(&tid, NULL, die, (void *)philos))
		return (1);
	while (i < philos[i].config->count_philo - 1)
	{
		if (pthread_create(&philos[i].tid, NULL, day, (void *)&philos[i]))
			return (1);
		pthread_detach(philos[i].tid);
		usleep(50);
		i++;
	}
	if (pthread_create(&philos->tid, NULL, day, (void *)&philos[i]))
		return (1);
	pthread_join(tid, NULL);
	return (0);
}

void	all_clear(t_philo *philos, pthread_mutex_t *fork, t_config	config)
{
	free(fork);
	free(philos);
	pthread_mutex_destroy(&config.message);
}
