/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:29:19 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/20 15:49:06 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->table->forks[philo->left_fork]));
	log_action(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(&(philo->table->forks[philo->right_fork]));
	log_action(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(&(philo->table->meal_check));
	log_action(philo, philo->id, "is eating");
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(philo->table->meal_check));
	u_got_knocked_out(philo->schedule->eat_time, philo);
	philo->x_meals++;
	pthread_mutex_unlock(&(philo->table->forks[philo->left_fork]));
	pthread_mutex_lock(&(philo->table->forks[philo->right_fork]));
}

void	rest_actions(t_philo *philo)
{
	log_action(philo, philo->id, "is sleeping");
	u_got_knocked_out(philo->schedule->sleep_time, philo);
	log_action(philo, philo->id, "is thinking");
}
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

void	guard_death(t_table *table)
{
	t_philo	*philo;
	int		i;

	philo = table->philos;
	while (!table->all_ate)
	{
		i = -1;
		while (++i, i < table->num_of_philos && !table->stop_simulation)
		{
			pthread_mutex_lock(&(table->meal_check));
			if (get_time() - philo[i].last_meal > table->schedule.time_to_die)
			{
				log_action(philo, i, "has died");
				break ;
			}
			pthread_mutex_unlock(&(table->meal_check));
			usleep(100);
		}
		if (table->stop_simulation)
			break ;
		while (table->schedule.num_of_to_eat != -1 && i < table->num_of_philos && philo[i].x_meals >= table->schedule.num_of_to_eat)
			i++;
		if (i == table->schedule.num_of_to_eat)
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
			return (1);
		philo[i].last_meal = get_time();
	}
	guard_death(table);
	destroy(table);
	return (0);
}
