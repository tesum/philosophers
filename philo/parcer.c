#include "philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			num;
	int			minus;
	long long	result;

	i = 0;
	num = 0;
	minus = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		minus = ',' - str[i];
		i++;
	}
	while ((*(str + i) >= '0' && *(str + i) <= '9'))
	{
		result = result * 10 + *(str + i) - '0';
		num++;
		i++;
	}
	return (result * minus);
}

int	get_time(int start)
{
	struct timeval	ct;

	gettimeofday(&ct, NULL);
	return((ct.tv_sec * 1000 + ct.tv_usec / 1000) - start);
}

int	parce(int argc, char **argv, t_config *new)
{
	new->count_philo = ft_atoi(argv[1]);
	new->ttd = ft_atoi(argv[2]);
	new->tte = ft_atoi(argv[3]);
	new->tts = ft_atoi(argv[4]);
	new->ene = -1;
	new->die = 0;
	new->eat_now = 0;
	new->start_time = get_time(0);
	if (argc == 6)
		new->ene = ft_atoi(argv[5]);
	if (new->count_philo < 0 || new->count_philo > 200 || new->ttd < 0 || new->tte < 0 || new->tts < 0 || new->ene < -1)
		return (1);
	if (pthread_mutex_init(&new->message, NULL))
		return (1);
	return (0);
}

void	my_sleep(int time)
{
	time_t	end;

	end = get_time(0) + time;
	while (get_time(0) < end)
	{
		usleep(10);
	}
}

int		logs(char *status, char *color, t_philo *philo)
{
	int	time;

	if (philo == NULL)
	{
		printf("%s%s\n", color, status);
		return (1);
	}
	time = philo->config->start_time;
	pthread_mutex_lock(&philo->config->message);
	printf("%s%d %d %s\n", color, get_time(time), philo->id, status);
	if (philo->config->die != 1)
		pthread_mutex_unlock(&philo->config->message);
	return (0);
}
