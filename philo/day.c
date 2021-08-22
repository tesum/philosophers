#include "philo.h"

void	*die(void *philos)
{
	t_philo *philo;
	int i = 0;
	philo = philos;
	while (1)
	{
		if (philo->config->die == 1)
		{
			printf("He is die :(\n");
			i += 1;
			return ((void *)1);
		}
	}
	return ((void *)0);
}

void	*day(void *philo_)
{
	t_philo *philo;

	philo = (t_philo *)philo_;
	int i = 0;
	while(1)
	{
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->right);
		printf("philo %d say %d\n", philo->id, i);
		usleep(50);
		i++;
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	}
	return ((void*)0);
}

int	start_day(t_philo *philos)
{
	int			i;
	pthread_t		tid;
	

	i = 0;
	pthread_create(&tid, NULL, die, (void *)&philos[0]);
	printf("count = %d\n", philos[1].config->count_philo);
	while (i < philos[i].config->count_philo - 1)
	{
		pthread_create(&philos->tid, NULL, day, (void *)&philos[i]);
		// pthread_detach(philos->tid);
	// 	printf("kek\n");
		usleep(50);
		i++;
	}
		pthread_create(&philos->tid, NULL, day, (void *)&philos[i]);

	pthread_join(tid, NULL);

	return (0);
}