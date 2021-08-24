#include "philo_bonus.h"

int	get_time(int start)
{
	struct timeval	ct;

	gettimeofday(&ct, NULL);
	return ((ct.tv_sec * 1000 + ct.tv_usec / 1000) - start);
}

t_philo	*init_philo(t_config *config)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * config->count_philo);
	if (!philos)
		exit(logs("Error", RED, NULL));
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
	t_config		config;
	t_philo			*philos;

	if (argc < 5 || argc > 6)
		return (logs("Error", RED, NULL));
	parce(argc, argv, &config);
	philos = init_philo(&config);
	config.pid = malloc(sizeof(pid_t) * config.count_philo);
	if (config.pid == 0)
		return (logs("Error", RED, NULL));
	sem_unlink("fork");
	sem_unlink("message");
	sem_unlink("eat_check");
	config.fork = sem_open("fork", O_CREAT, S_IRWXU, config.count_philo);
	config.message = sem_open("message", O_CREAT, S_IRWXU, 1);
	config.eat_check = sem_open("eat_check", O_CREAT, S_IRWXU, 0);
	if (!config.fork || !config.message || !config.eat_check)
		exit(0);
	if (start_day(philos) == 1)
		return (logs("Error", RED, NULL));
	// all_clear(philos, fork, config);
	return (0);
}