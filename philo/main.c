#include "philo.h"

pthread_mutex_t	*init_forks(t_config config, t_philo *philos)
{
	int				i;
	pthread_mutex_t	*fork;

	fork = malloc(sizeof(pthread_mutex_t) * config.count_philo);
	if (fork == (void *)-1)
		return (NULL);
	i = 0;
	while (i < config.count_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
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

	if (argc < 5)
		return (1);
	philos = parce(argc, argv, &config);
	printf("%d | %d | %d | %d | %d | %d\n", config.count_philo, config.ttd, config.tte, config.tts, config.ene, config.start_time);
	fork = init_forks(config, philos);
	start_day(philos);
	return (0);
}