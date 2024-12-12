/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils&&timing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:16:58 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/12 17:20:53 by mokariou         ###   ########.fr       */
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

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return (long)((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void u_got_knocked_out(long long ms)
{
    long long start = get_time() + ms;

    //while (get_time() - start < ms)
	long temp = get_time();
    while (start > get_time())
	{
		//printf("time left: %lld\n", start - get_time());
        usleep(100);
    }
}