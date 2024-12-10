/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:18:07 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/09 20:37:54 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint16_t	convert_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return (uint32_t)((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	think(void)
{
	usleep(rand() % 100000);
}

void	sleep_philo(t_philosopher *philo)
{
	usleep(philo->table->time_to_sleep);
}

void	eat(t_philosopher *philo)
{
	usleep(philo->table->time_to_eat);
}