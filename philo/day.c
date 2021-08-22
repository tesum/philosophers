#include "philo.h"

void	pdie(t_philo *philo, t_config	*cnf)
{
	if (get_time(cnf->start_time) - philo->last_eat > cnf->ttd)
	{
		philo->config->die = 1;
		printf("He is die :(\n");
		logs(DIE, RED, philo);
		exit(1);
	}
}
void	*die(void *philos)
{
	t_philo *philo;
	t_config	*cnf;
	int i = 0;
	philo = philos;
	cnf = philo->config;
	while (1)
	{
		i = 0;
		while (i < cnf->count_philo)
		{
			if (get_time(cnf->start_time) - philo->last_eat > cnf->ttd)
			{
				philo->config->die = 1;
				logs(DIE, RED, philo);
				exit(1);
			}
			i++;
		}
		// if (philo->config->die == 1)
		// {
		// 	printf("He is die :(\n");
		// 	i += 1;
		// 	exit(1);
		// 	return ((void *)1);
		// }
	}
	return ((void *)0);
}

void	eating(t_philo *philo)
{
	int	time;

	time = philo->config->start_time;
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->right);
	logs(FORK, WHITE, philo);
	logs(EAT, CYAN, philo);
	philo->last_eat = get_time(time);
		// philo->last_eat = get_time() + philo->config->ttd;

	my_sleep(philo->config->tte);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	*day(void *philo_)
{
	t_philo *philo;
	int	time;

	philo = (t_philo *)philo_;
	time = philo->config->start_time;
	while(1)
	{
		// if (get_time() - time - philo->last_eat + philo->config->tts > philo->config->ttd)
		// {
		// 	philo->config->die = 1;
		// 	logs(DIE, RED, philo);
		// }
		eating(philo);
		logs(SLEEP, PURPLE, philo);
		my_sleep(philo->config->tts);
		logs(THINK, YELLOW, philo);
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
		usleep(50);
	// 	printf("kek\n");
		// usleep(50);
		i++;
	}
		pthread_create(&philos->tid, NULL, day, (void *)&philos[i]);

	pthread_join(tid, NULL);

	return (0);
}