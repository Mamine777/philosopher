/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils&&timing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:16:58 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/11 16:13:37 by mokariou         ###   ########.fr       */
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

uint16_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return (long)((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	u_got_knocked_out(long ms)
{
	long	start;
	long	now;

	start = get_time();
	now = get_time();
	while (now - start < ms)
	{
		sleep(333);
		now = get_time();
	}
}