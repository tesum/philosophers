#include "philo.h"

int	main(int argc, char **argv)
{
	pthread_mutex_t	*fork;
	t_config		config;

	parce(argc, argv, &config);
	printf("%d | %d | %d | %d | %d", config.count_philo, config.ttd, config.tte, config.tts, config.ene);

	fork = malloc(sizeof(pthread_mutex_t) * config.count_philo);
	if (fork == -1)
		return ;
	return (0);
}