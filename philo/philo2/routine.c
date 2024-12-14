/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:59:45 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/14 19:35:57 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*guard_the_simulation(void *arg)
{
	t_table				*table;
	int					i;
	unsigned long long	current_time;

	table = (t_table *)arg;
	while (1)
	{
		i = -1;
		while (++i < table->num_philosophers)
		{
			pthread_mutex_lock(&table->lock);
			current_time = get_time();
			if ((current_time
					- table->philo[i].last_meal) > table->schedule.time_to_die)
			{
				log_action(&table->philo[i], "has died");
				table->stop_simulation = true;
				pthread_mutex_unlock(&table->lock);
				return (NULL);
			}
			pthread_mutex_unlock(&table->lock);
			pthread_mutex_lock(&table->lock);
			if (table->meals_completed == table->schedule.num_of_to_eat)
			{
				exit(1);
				table->stop_simulation = true;
				pthread_mutex_unlock(&table->lock);
				return (NULL);
			}
			pthread_mutex_unlock(&table->lock);
			pthread_mutex_lock(&table->lock);
			if (table->stop_simulation)
			{
				pthread_mutex_unlock(&table->lock);
				return (NULL);
			}
			pthread_mutex_unlock(&table->lock);
		}
		usleep(1000);
	}
	return (NULL);
}

void	*simulation(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
		usleep(15000);
	while (1)
	{
		pthread_mutex_lock(&philo->table->lock);
		if (philo->table->stop_simulation == true)
		{
			pthread_mutex_unlock(&philo->table->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->lock);
		if (philo_takes_forks(philo))
			break ;
		if (log_action(philo, "is sleeping"))
			break ;
		u_got_knocked_out(philo->schedule.sleep_time);
		if (log_action(philo, "is thinking"))
			break ;
	}
	return (NULL);
}
