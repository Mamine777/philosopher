/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 13:48:57 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/09 20:08:00 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// assign forks
static void	set_forks(t_philosopher *philo, t_forks *forks, int pos)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	if (philo->id % 2)
	{
		philo->first_fork = &forks[pos];
		philo->second_fork = &forks[(pos + 1) % philo_nbr];
	}
}

static void	init_philo(t_table *table)
{
	int				i;
	t_philosopher	*philo;

	i = -1;
	while (++i, i < table->philo_nbr)
	{
		philo = table->philo + i;
		philo->id = i + 1;
		philo->full_bool = 0;
		philo->meals_count = 0;
		philo->table = table;
		set_forks(philo, philo->table->forks, i);
	}
}

void	init_info(t_table *table)
{
	int	i;

	table->end_simulation = 0;
	table->all_threads_ready = 0;
	table->philo = save_malloc(table->philo_nbr);
	handle_mutex(&table->table_mutex, INIT);
	table->forks = save_malloc(sizeof(t_forks) * table->philo_nbr);
	i = -1;
	while (++i, i < table->philo_nbr)
	{
		handle_mutex(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i; // set number to each fork
	}
	init_philo(table);
}
