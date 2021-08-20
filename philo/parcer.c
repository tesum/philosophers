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

void	parce(int argc, char **argv, t_config *new)
{
	// t_config	new;

	new->count_philo = ft_atoi(argv[1]);
	new->ttd = ft_atoi(argv[2]);
	new->tte = ft_atoi(argv[3]);
	new->tts = ft_atoi(argv[4]);
	new->ene = 0;
	new->die = 0;
	if (argc == 6)
		new->ene = ft_atoi(argv[5]);
}