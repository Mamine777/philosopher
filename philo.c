/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:32:32 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/09 15:17:09 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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