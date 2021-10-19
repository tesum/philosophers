/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsenijdrozdov <arsenijdrozdov@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 13:38:11 by demilan           #+#    #+#             */
/*   Updated: 2021/09/07 20:28:14 by arsenijdroz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// my is digit
int	mid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}

int	parce(int argc, char **argv, t_config *new)
{
	if (mid(argv[1]) || mid(argv[2]) || mid(argv[3]) || mid(argv[4]))
		return (1);
	new->count_philo = ft_atoi(argv[1]);
	new->ttd = ft_atoi(argv[2]);
	new->tte = ft_atoi(argv[3]);
	new->tts = ft_atoi(argv[4]);
	new->ene = -1;
	new->die = 0;
	new->eat_now = 0;
	new->stop = 0;
	new->start_time = get_time(0);
	if (argc == 6)
	{
		if (mid(argv[5]))
			return (1);
		new->ene = ft_atoi(argv[5]);
	}
	if (new->count_philo == 0 || new->ene == 0)
		return (2);
	if (new->count_philo < 0 || new->count_philo > 200 || \
		new->ttd < 0 || new->tte < 0 || new->tts < 0 || new->ene < -1)
		return (1);
	if (pthread_mutex_init(&new->message, NULL))
		return (1);
	return (0);
}

void	my_sleep(int time)
{
	time_t	start;
	time_t	end;

	start = get_time(0);
	end = get_time(0) + time;
	while (start < end)
	{
		usleep(500);
		start = get_time(0);
	}
}

int	logs(char *status, char *color, t_philo *philo)
{
	int	time;

	if (philo == NULL)
	{
		printf("%s%s\n", color, status);
		return (1);
	}
	time = philo->config->start_time;
	pthread_mutex_lock(&philo->config->message);
	if (philo->config->die != 1 || \
		(philo->config->die && philo->config->stop == 0))
		printf("%s%d %d %s\n", color, get_time(time), philo->id, status);
	pthread_mutex_unlock(&philo->config->message);
	return (0);
}
