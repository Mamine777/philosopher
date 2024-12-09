/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:32:32 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/09 16:17:48 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	simulation(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
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
			handle_thread(&table->philo[i].thread_id, start_equaz,
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
