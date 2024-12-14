/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:44:15 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/14 17:38:41 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	res = 0;
	sign = 1;
	if (!str)
		return (0);
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

uint64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

void	u_got_knocked_out(long long ms)
{
	unsigned long long	end_time;

	end_time = get_time() + ms;
	while (get_time() < end_time)
	{
		usleep(500);
	}
}

int	log_action(t_philosopher *philo, const char *action)
{
	long	current_time;

	current_time = get_time();
	pthread_mutex_lock(&philo->table->print_lock);
	if (philo->table->stop_simulation == true)
	{
		pthread_mutex_unlock(&philo->table->print_lock);
		return (1);
	}
	printf("%ldms Philosopher %d %s\n", (current_time - philo->start),
		philo->id, action);
	pthread_mutex_unlock(&philo->table->print_lock);
	return (0);
}
