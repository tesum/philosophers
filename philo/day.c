#include "philo.h"

void	*day(void *philo_)
{
	t_philo *philo;

	philo = philo_;
	int i = 0;
	while(i < 3)
	{
		printf("philo %d say %d\n", philo->id, i);
		i++;
	}
	return ((void*)0);
}

int	start_day(t_philo *philos)
{
	void		*philo;
	pthread_t	tid;
	int			i;

	i = 0;
	while (i < philos->config->count_philo)
	{
		philos[i].id = i;
		philo = &philos[i];
		pthread_create(&tid, NULL, &day, philo);
		pthread_join(tid, NULL);
		i++;
	}
	return (0);
}