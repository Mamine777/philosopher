/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   travel_through.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 13:20:58 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/08 13:44:08 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (10 * res) + (str[i++] - 48);
		if (res > 9223372036854775807 && sign > 0)
			return (-1);
		if (res > 9223372036854775807 && sign < 0)
			return (0);
	}
	return ((int)(res * sign));
}

void	check_table(t_table *table, char **av)
{
	table->philo_nbr = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]) * 1e3;
	table->time_to_eat = ft_atoi(av[3]) * 1e3;
	table->time_to_sleep = ft_atoi(av[4]) * 1e3;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		err_exit("Use timespace more than 60ms");
	if (av[5])
		table->nbr_limits_meal = ft_atoi(av[5]);
	else
		table->nbr_limits_meal = -1;
}