/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:21:30 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/20 14:29:02 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_table	table;
	if (ac == 5 || ac == 6)
	{
		if (fill_table(&table, av))
			return (printf("wrong argument\n"), 1);
		if (routine(&table))
			return (1);
	}
	else
		return (printf("not the mount of args asked for, argc : %d\n", ac), 1);
}