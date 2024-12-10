/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:32:32 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/09 20:54:10 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*simulation(void *data)
{
	t_philosopher	*philo;
	uint32_t		last_meal_time;
	t_table			*table;

	philo = (t_philosopher *)data;
	last_meal_time = convert_time();
	table = philo->table;
	while (1)
	{
		if (last_meal_time + table->time_to_die < convert_time())
			return (NULL);
		think();
		if (philo->id % 2 == 0)
		{
			handle_mutex(&philo->first_fork->fork, LOCK);
			handle_mutex(&philo->second_fork->fork, LOCK);
		}
		else
		{
			handle_mutex(&philo->second_fork->fork, LOCK);
			handle_mutex(&philo->first_fork->fork, LOCK);	
		}
		eat(philo);
		philo->meals_count++;
		last_meal_time = convert_time();
		handle_mutex(&philo->first_fork->fork, UNLOCK);
		handle_mutex(&philo->second_fork->fork, UNLOCK);
		sleep(philo);
	}
	return (NULL);
}

void	start_equaz(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limits_meal == 0)
		return ;
	else if (table->nbr_limits_meal == 1)
		;
	// handle the condition;
	else
	{
		while (++i, i < table->philo_nbr)
		{
			handle_thread(&table->philo[i].thread_id, simulation,
				&table->philo[i], CREATE);
		}
	}
	//threads made succefully
}

int	main(int ac, char **av)
{
	t_table table;
	if (ac == 5 || ac == 6)
	{
		// start
		//  1check the errors && fill the table
		check_table(&table, av);
		// creating the thning
		init_info(&table);
		// start the table and solve the issue
		start_equaz(&table);
	}
	else
		err_exit("No the right input");
}
