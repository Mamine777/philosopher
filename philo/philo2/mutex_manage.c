/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:15:05 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/14 19:35:21 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	manage_failed_thread(pthread_mutex_t *mutex, t_table *table)
{
	pthread_mutex_lock(mutex);
	table->stop_simulation = true;
	printf("Failed to create philosopher thread\n");
	pthread_mutex_unlock(mutex);
}

int	philo_takes_forks(t_philosopher *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(first_fork);
	if (log_action(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(first_fork);
		return (1);
	}
	pthread_mutex_lock(second_fork);
	if (log_action(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->table->lock);
	philo->last_meal = get_time();
	philo->count_meals++;
	if (philo->count_meals == philo->schedule.num_of_to_eat)
        philo->table->meals_completed++;
	pthread_mutex_unlock(&philo->table->lock);
	u_got_knocked_out(philo->schedule.eat_time);
	if (log_action(philo, "is eating"))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return (1);
	}
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	return (0);
}
