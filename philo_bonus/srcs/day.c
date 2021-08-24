/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demilan <demilan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 13:38:03 by demilan           #+#    #+#             */
/*   Updated: 2021/08/24 18:12:43 by demilan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	pdie(t_philo *philo, t_config *cnf)
{
	if (get_time(cnf->start_time) - philo->last_eat > cnf->ttd)
	{
		logs(DIE, RED, philo);
		sem_wait(philo->config->message);
		philo->config->die = 1;
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
	i = 1;
	while (1)
	{
		if (pdie(philo, cnf))
			return ((void *) 1);
		if (cnf->ene > 0 && philo->ceat > cnf->ene && i)
		{
			sem_wait(cnf->eat_check);
			i = 0;
		}
		// if (cnf->eat_now >= cnf->ene * cnf->count_philo && cnf->ene > 0)
		// {
		// 	sem_wait(cnf->message);
		// 	exit(0);
		// 	return ((void *) 1);
		// }
	}
	return ((void *)0);
}

void	day(void *philo_)
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
		philo->ceat += 1;
		my_sleep(philo->config->tte);
		sem_post(philo->config->fork);
		sem_post(philo->config->fork);
		logs(SLEEP, PURPLE, philo);
		my_sleep(philo->config->tts);
		logs(THINK, YELLOW, philo);
	}
}

void	*cheack_eat(void *config)
{
	t_config	*cnf;
	int			i;

	i = 0;
	cnf = (t_config *)config;
	while (i < cnf->count_philo)
	{
		sem_wait(cnf->eat_check);
		i++;
	}
	return (0);
}

int	start_day(t_philo *philos)
{
	int			i;
	pthread_t	tid;

	i = 0;
	if (philos->config->ene > 0)
		pthread_create(&tid, NULL, cheack_eat, (void *)philos->config);
	while (i < philos->config->count_philo)
	{
		philos->config->pid[i] = fork();
		if (philos->config->pid[i] == 0)
		{
			if (pthread_create(&tid, NULL, die, (void *)&philos[i]))
				return (1);
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
	i = 0;
	waitpid(0, NULL, 0);
	while (i < philos->config->count_philo)
	{
		sem_post(philos->config->eat_check);
		i++;
	}
	i = 0;
	while (i < philos->config->count_philo)
	{
		kill(philos->config->pid[i], SIGTERM);
		i++;
	}
	sem_close(philos->config->fork);
	sem_close(philos->config->message);
	sem_close(philos->config->eat_check);
	sem_unlink("fork");
	sem_unlink("eat_check");
	sem_unlink("message");
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
