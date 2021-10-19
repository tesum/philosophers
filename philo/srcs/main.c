/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demilan <demilan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 13:38:08 by demilan           #+#    #+#             */
/*   Updated: 2021/10/19 15:25:40 by demilan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(int start)
{
	struct timeval	ct;

	gettimeofday(&ct, NULL);
	return ((ct.tv_sec * 1000 + ct.tv_usec / 1000) - start);
}

void	give_forks(t_config config, t_philo *philos, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < config.count_philo - 1)
	{
		philos[i].left = &fork[i];
		philos[i].right = &fork[i + 1];
		i++;
	}
	philos[i].left = &fork[i];
	philos[i].right = &fork[0];
}

pthread_mutex_t	*init_forks(t_config config, t_philo *philos)
{
	int				i;
	pthread_mutex_t	*fork;

	fork = malloc(sizeof(pthread_mutex_t) * config.count_philo);
	if (!fork)
		return (NULL);
	i = 0;
	while (i < config.count_philo)
	{
		if (pthread_mutex_init(&fork[i], NULL))
			return (NULL);
		i++;
	}
	give_forks(config, philos, fork);
	return (fork);
}

t_philo	*init_philo(t_config *config)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * config->count_philo);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < config->count_philo)
	{
		philos[i].id = i + 1;
		philos[i].last_eat = 0;
		philos[i].config = config;
		i++;
	}
	return (philos);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	*fork;
	t_config		config;
	t_philo			*philos;
	int				err;

	if (argc < 5 || argc > 6)
		return (logs("Error", RED, NULL));
	err = parce(argc, argv, &config);
	if (err == 1)
		return (logs("Error", RED, NULL));
	if (err == 2)
		return (0);
	philos = init_philo(&config);
	if (!philos)
		return (logs("Error", RED, NULL));
	fork = init_forks(config, philos);
	if (!fork)
		return (logs("Error", RED, NULL));
	if (start_day(philos) == 1)
		return (logs("Error", RED, NULL));
	all_clear(philos, fork, config);
	return (0);
}
