/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:05:19 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/11 17:56:42 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!table->stop_simulation)
	{
		i = -1;
		while (++i < table->num_philosophers)
		{
			if (get_time() - table->philo[i].last_meal >= table->schedule.time_to_die)
            {
                table->stop_simulation = 1;
                printf("Philosopher %d has died\n", table->philo[i].id);
                return (NULL);
            }
		}
		usleep(1000);
	}
	return (NULL);
}
void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (philo->table->stop_simulation)
	{
		pthread_mutex_lock(philo->right_fork);
		printf("philosopher %d has taken a fork\n", philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("philosopher %d has taken a fork\n", philo->id);
		printf("philosopher %d is eating\n", philo->id);
		u_got_knocked_out(philo->eat_time);
		philo->last_meal = get_time();
		philo->count_meals++;
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		printf("philosopher %d is sleeping\n", philo->id);
		u_got_knocked_out(philo->sleep_time);
		printf("philosopher %d is thinking\n", philo->id);
	}
	return (NULL);
}

static void	create_threads(t_table *table)
{
	int			i;
	pthread_t	monitor;

	i = -1;
    if (pthread_create(&monitor, NULL, monitor_routine, table))
    {
        printf("Error: Failed to create monitor thread\n");
        return;
    }
	while (++i < table->num_philosophers)
	{
		pthread_create(&table->threads[i], NULL, &routine, &table->philo[i]);
	}
	i = -1;
	while (++i < table->num_philosophers)
	{
		pthread_join(table->threads[i], NULL);
	}
	pthread_join(monitor, NULL);
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
		table->philo[i].count_meals = 0;
		table->philo[i].time_to_die = table->schedule.time_to_die;
		table->philo[i].eat_time = table->schedule.eat_time;
		table->philo[i].sleep_time = table->schedule.sleep_time;
		table->philo[i].num_of_to_eat = table->schedule.num_of_to_eat;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1)
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
	table->stop_simulation = 0;
	if (av[5])
		table->schedule.num_of_to_eat = ft_atoi(av[5]) * 1e3;
	else
		table->schedule.num_of_to_eat = -1;
	if (table->num_philosophers <= 0 || table->schedule.time_to_die <= 0
		|| table->schedule.eat_time <= 0 || table->schedule.sleep_time <= 0)
	{
		printf("Error: Invalid input values\n");
		return ;
	}
}