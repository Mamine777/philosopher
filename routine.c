/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:29:19 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/20 19:24:18 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*threads(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->id % 2 == 0)
		usleep(15000);
	while (!table->stop_simulation)
	{
		take_forks(philo);
		if (table->all_ate)
			break ;
		rest_actions(philo);
	}
	return (NULL);
}

static void	check_philos_death(t_table *table)
{
	t_philo	*philo;
	int		i;

	philo = table->philos;
	i = -1;
	while (++i < table->num_of_philos && !table->stop_simulation)
	{
		pthread_mutex_lock(&(table->meal_check));
		if (get_time() - philo[i].last_meal > table->schedule.time_to_die)
		{
			log_action(philo, i, "has died");
			table->stop_simulation = 1;
			pthread_mutex_unlock(&(table->meal_check));
			break ;
		}
		pthread_mutex_unlock(&(table->meal_check));
		usleep(100);
	}
}

void	guard_death(t_table *table)
{
	int	i;

	while (!table->all_ate)
	{
		check_philos_death(table);
		if (table->stop_simulation)
			break ;
		i = 0;
		while (table->schedule.num_of_to_eat != -1 && i < table->num_of_philos
			&& table->philos[i].x_meals >= table->schedule.num_of_to_eat)
			i++;
		if (i == table->num_of_philos)
			table->all_ate = 1;
	}
}

void	destroy(t_table *table)
{
	int	i;

	i = -1;
	while (++i, i < table->num_of_philos)
	{
		pthread_join(table->philos[i].thread_id, NULL);
	}
	i = -1;
	while (++i < table->num_of_philos)
		pthread_mutex_destroy(&(table->forks[i]));
	pthread_mutex_destroy(&(table->print));
	pthread_mutex_destroy(&(table->meal_check));
}

int	routine(t_table *table)
{
	t_philo	*philo;
	int		i;

	table->first_timestamp = get_time();
	philo = table->philos;
	i = -1;
	while (++i, i < table->num_of_philos)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, threads, &(philo[i])))
		{
			table->stop_simulation = 1;
			while (--i >= 0)
				pthread_join(philo[i].thread_id, NULL);
			return (1);
		}
		philo[i].last_meal = get_time();
	}
	guard_death(table);
	destroy(table);
	return (0);
}
