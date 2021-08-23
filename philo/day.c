/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demilan <demilan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 13:38:03 by demilan           #+#    #+#             */
/*   Updated: 2021/08/23 13:38:35 by demilan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pdie(t_philo *philo, t_config *cnf)
{
	if (get_time(cnf->start_time) - philo->last_eat > cnf->ttd)
	{
		philo->config->die = 1;
		logs(DIE, RED, philo);
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
			if (pdie(philo, cnf))
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

void	eating(t_philo *philo)
{
	int	time;

	time = philo->config->start_time;
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->right);
	logs(FORK, WHITE, philo);
	logs(EAT, CYAN, philo);
	philo->last_eat = get_time(time);
	philo->config->eat_now += 1;
	my_sleep(philo->config->tte);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	*day(void *philo_)
{
	t_philo	*philo;

	philo = (t_philo *)philo_;
	while (1)
	{
		eating(philo);
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
		if (pthread_create(&philos->tid, NULL, day, (void *)&philos[i]))
			return (1);
		usleep(50);
		i++;
	}
	if (pthread_create(&philos->tid, NULL, day, (void *)&philos[i]))
		return (1);
	pthread_join(tid, NULL);
	return (0);
}
