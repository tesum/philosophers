#include "philo.h"

int	main(int argc, char **argv)
{
	pthread_mutex_t	*fork;
	t_config		config;
	t_philo			*philos;

	printf("lol\n");
	philos = parce(argc, argv, &config);
	printf("%d | %d | %d | %d | %d | %d\n", config.count_philo, config.ttd, config.tte, config.tts, config.ene, config.start_time);

	fork = malloc(sizeof(pthread_mutex_t) * config.count_philo);
	if (fork == (void *)-1)
		return (1);
	start_day(philos);
	return (0);
}