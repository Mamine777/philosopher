/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:42:31 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/09 18:13:50 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *mutex, int *dest, int value)
{
	handle_mutex(mutex, LOCK);
	*dest = value;
	handle_mutex(mutex, UNLOCK);
}

int get_bool(pthread_mutex_t *mutex, int *value)
{
	int	ret;

	handle_mutex(mutex, LOCK);
	ret = *value;
	handle_mutex(mutex, UNLOCK);
	return (ret);
}

long get_bool(pthread_mutex_t *mutex, int *value)
{
	int	ret;

	handle_mutex(mutex, LOCK);
	ret = *value;
	handle_mutex(mutex, UNLOCK);
	return (ret);
}

int simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
