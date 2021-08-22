#include "philo.h"

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
	i = 0;
	while (i < config.count_philo)
	{
		philos[i].left = &fork[i];
		philos[i].right = &fork[i + 1];
		i++;
	}
	philos[i].left = &fork[i];
	philos[i].right = &fork[0];
	return (fork);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	*fork;
	t_config		config;
	t_philo			*philos;
	int				i;

	if (argc < 5 || argc > 6)
		return (1);
	if (parce(argc, argv, &config) == 1)
		return (logs("Error", RED, NULL));
	philos = malloc(sizeof(t_philo) * config.count_philo);
	if (!philos)
		return (logs("Error", RED, philos));
	i = 0;
	while (i < config.count_philo)
	{
		philos[i].id = i + 1;
		philos[i].last_eat = config.start_time + config.ttd;
		philos[i].config = &config;
		i++;
	}
	fork = init_forks(config, philos);
	if (!fork)
		return (logs("Error", RED, philos));
	if (start_day(philos) == 1)
		return (logs("Error", RED, philos));
	return (0);
}