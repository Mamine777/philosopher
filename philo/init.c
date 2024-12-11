/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:05:19 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/11 17:07:17 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		pthread_mutex_lock(table->philo->right_fork);
		printf("philosopher %d has taken a fork\n", table->philo->id);
		pthread_mutex_lock(table->philo->left_fork);
		printf("philosopher %d has taken a fork\n", table->philo->id);
		printf("philosopher %d is eating\n", table->philo->id);
		u_got_knocked_out(table->philo->eat_time);
		table->philo->last_meal = get_time();
		if (get_time() - table->philo->last_meal >= table->schedule.time_to_die)
		{
			printf("philosopher %d have died\n", table->philo->id);
			pthread_mutex_unlock(table->philo->right_fork);
			pthread_mutex_unlock(table->philo->left_fork);
			break ;
		}
		pthread_mutex_unlock(table->philo->right_fork);
		pthread_mutex_unlock(table->philo->left_fork);
		printf("philosopher %d is sleeping\n", table->philo->id);
		u_got_knocked_out(table->philo->sleep_time);
		printf("philosopher %d is thinking\n", table->philo->id);
	}
	return (NULL);
}

static void	create_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philosophers)
	{
		pthread_create(&table->threads[i], NULL, &routine, &table->philo[i]);
	}
	i = -1;
	while (++i < table->num_philosophers)
	{
		pthread_join(table->threads[i], NULL);
	}
	i = -1;
	while (++i < table->num_philosophers)
	{
		pthread_mutex_destroy(&table->forks[i]);
	}
}

void	init_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philosophers)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return ;
	}
	i = -1;
	while (++i < table->num_philosophers)
	{
		table->philo[i].id = i + 1;
		table->philo[i].time_to_die = table->schedule.time_to_die;
		table->philo[i].eat_time = table->schedule.eat_time;
		table->philo[i].sleep_time = table->schedule.sleep_time;
		table->philo[i].num_of_to_eat = table->schedule.num_of_to_eat;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[i + 1
			% table->num_philosophers];
		table->philo[i].start_simulation = get_time();
	}
	create_threads(table);
}

void	fill_table(t_table *table, char **av)
{
	table->num_philosophers = ft_atoi(av[1]);
	table->schedule.time_to_die = ft_atoi(av[2]) * 1e3;
	table->schedule.eat_time = ft_atoi(av[3]) * 1e3;
	table->schedule.sleep_time = ft_atoi(av[4]) * 1e3;
	if (av[5])
		table->schedule.num_of_to_eat = ft_atoi(av[5]) * 1e3;
	else
		table->schedule.num_of_to_eat = -1;
}
