/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:40:26 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/14 19:35:07 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_table *table)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&table->lock, NULL))
		return (1);
	while (++i < table->num_philosophers)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (1);
	}
	i = -1;
	while (++i < table->num_philosophers)
	{
		table->philo[i].id = i + 1;
		table->philo[i].count_meals = 0;
		table->philo[i].last_meal = get_time();
		table->philo[i].start = get_time();
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1)
			% table->num_philosophers];
		table->philo[i].table = table;
	}
	if (create_threads(table))
		return (1);
	return (0);
}

void	fill_table(t_table *table, char **av)
{
	if (!av[1] || !av[2] || !av[3] || !av[4])
	{
		printf("Error: Missing input arguments\n");
		exit(1);
	}
	pthread_mutex_init(&table->print_lock, NULL);
	table->num_philosophers = ft_atoi(av[1]);
	table->schedule.time_to_die = ft_atoi(av[2]);
	table->schedule.eat_time = ft_atoi(av[3]);
	table->schedule.sleep_time = ft_atoi(av[4]);
	table->meals_completed = 0;
	table->stop_simulation = false;
	if (av[5])
		table->schedule.num_of_to_eat = ft_atoi(av[5]);
	else
	{
		table->schedule.num_of_to_eat = -1;	
	}
	if (table->num_philosophers <= 0 || table->schedule.time_to_die <= 0
		|| table->schedule.eat_time <= 0 || table->schedule.sleep_time <= 0)
	{
		printf("Error: Invalid input values\n");
		exit(1);
	}
}