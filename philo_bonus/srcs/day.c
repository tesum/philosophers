/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demilan <demilan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 13:38:03 by demilan           #+#    #+#             */
/*   Updated: 2021/08/25 19:42:14 by demilan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		if (get_time(cnf->start_time) - philo->last_eat > cnf->ttd)
		{
			philo->config->die = 1;
			logs(DIE, RED, philo);
			exit(0);
		}
		if (cnf->ene > 0 && philo->ceat > cnf->ene && i)
		{
			sem_post(cnf->eat_check);
			i = 0;
		}
		usleep(500);
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

void	*cheack_eat(void *philos)
{
	t_config	*cnf;
	t_philo		*philo;
	int			i;

	i = 0;
	philo = (t_philo *)philos;
	cnf = philo->config;
	while (i < cnf->count_philo)
	{
		sem_wait(cnf->eat_check);
		i++;
	}
	i = 0;
	while (i < cnf->count_philo)
	{
		kill(cnf->pid[i], SIGTERM);
		i++;
	}
	sem_close(cnf->fork);
	sem_close(cnf->message);
	sem_close(cnf->eat_check);
	sem_unlink("fork");
	sem_unlink("eat_check");
	sem_unlink("message");
	return (0);
}

int	start_day(t_philo *philos)
{
	int			i;
	pthread_t	tid;

	i = 0;
	if (philos->config->ene > 0)
	{
		if (pthread_create(&tid, NULL, cheack_eat, (void *)philos))
			return (1);
	}
	while (i < philos->config->count_philo)
	{
		philos->config->pid[i] = fork();
		if (philos->config->pid[i] == 0)
		{
			if (pthread_create(&philos[i].tid, NULL, die, (void *)&philos[i]))
				return (1);
			day(&philos[i]);
			i = philos->config->count_philo;
		}
		i++;
	}
	return (0);
}

void	all_clear(t_philo *philos, t_config	*cnf)
{
	int	i;

	i = 0;
	waitpid(0, NULL, 0);
	while (i < cnf->count_philo)
	{
		sem_post(cnf->eat_check);
		i++;
	}
	i = 0;
	while (i < cnf->count_philo)
	{
		kill(cnf->pid[i], SIGTERM);
		i++;
	}
	sem_close(cnf->fork);
	sem_close(cnf->message);
	sem_close(cnf->eat_check);
	sem_unlink("fork");
	sem_unlink("eat_check");
	sem_unlink("message");
	free(cnf);
	free(philos);
	exit(1);
}
