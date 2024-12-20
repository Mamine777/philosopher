/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:44:50 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/20 15:05:46 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_table *table)
{
	int	i;

	i = -1;
	while (++i, i < table->num_of_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (1);
	}
	if (pthread_mutex_init(&(table->print), NULL))
		return (1);
	if (pthread_mutex_init(&(table->meal_check), NULL))
		return (1);
	return (0);
}
int	init_philo(t_table *table)
{
	int	i;

	if (init_mutex(table))
		return (1);
	i = -1;
	while (++i ,i < table->num_of_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].x_meals = 0;
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = (i + 1) % table->num_of_philos;
		table->philos[i].last_meal = 0;
		table->philos[i].table = table;
	}
	return (0);
}

int	fill_table(t_table *table, char **av)
{
	if (!av[1] || !av[2] || !av[3] || !av[4])
		return (1);
	table->num_of_philos = ft_atoi(av[1]);
	table->schedule.time_to_die = ft_atoi(av[2]);
	table->schedule.eat_time = ft_atoi(av[3]);
	table->schedule.sleep_time = ft_atoi(av[4]);
	table->all_ate = 0;
	table->stop_simulation = 0;
	if (table->num_of_philos < 2 || table->schedule.time_to_die < 0
		|| table->schedule.eat_time < 0 || table->schedule.sleep_time < 0
		|| table->num_of_philos > 200)
		return (1);
	if (av[5])
	{
		table->schedule.num_of_to_eat = ft_atoi(av[5]);
		if (table->schedule.num_of_to_eat <= 0)
			return (1);
	}
	else
		table->schedule.num_of_to_eat = -1;
	if (init_philo(table))
		return (1);
	return (0);
}
