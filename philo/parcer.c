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

int	get_time(void)
{
	struct timeval	ct;

	gettimeofday(&ct, NULL);
	return(ct.tv_sec * 1000 + ct.tv_usec / 1000);
}

t_philo	*parce(int argc, char **argv, t_config *new)
{
	t_philo	*philo;
	int		i;

	new->count_philo = ft_atoi(argv[1]);
	new->ttd = ft_atoi(argv[2]);
	new->tte = ft_atoi(argv[3]);
	new->tts = ft_atoi(argv[4]);
	new->ene = 0;
	new->die = 0;
	new->start_time = get_time();
	if (argc == 6)
		new->ene = ft_atoi(argv[5]);
	philo = malloc(sizeof(t_philo) * new->count_philo);
	// if (philo == (void*)-1)
	// 	return ;
	i = 0;
	while (i < new->count_philo)
	{
		philo[i].config = new;
		i++;
	}
	return(philo);
}