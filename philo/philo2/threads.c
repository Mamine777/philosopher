/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:31:30 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/14 17:41:44 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_table *table)
{
	pthread_t	routine;
	int				i;

	if (table->num_philosophers == 1)
		return (log_action(table->philo, "has died"), 1);
	if (pthread_create(&routine, NULL, &guard_the_simulation, table))
		return (1);
	i = -1;
	while (++i < table->num_philosophers)
	{
		if (pthread_create(&table->threads[i], NULL,&simulation, &table->philo[i]))
		{
			manage_failed_thread(&table->lock, table);
			return (1);
		}
	}
	i = -1;
	while (++i < table->num_philosophers)
	{
		if (pthread_join(table->threads[i], NULL))
			return (1);
	}
	if (pthread_join(routine, NULL))
		return (1);
	i = -1;
	while (++i < table->num_philosophers)
	{
		pthread_mutex_destroy(&table->forks[i]);
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->lock);
	return (1);
}