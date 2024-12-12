/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:05:19 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/12 15:26:23 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*routine(void *arg)
// {
// 	t_philosopher	*philo;

// 	philo = (t_philosopher *)arg;
// 	while (!philo->table->stop_simulation)
// 	{
// 		printf("Philosopher %d is thinking\n", philo->id);
// 		// Lock the forks in a consistent order
// 		if (philo->id % 2 == 0)
// 		{
// 			pthread_mutex_lock(philo->right_fork);
// 			printf("Philosopher %d has taken the right fork\n", philo->id);
// 			pthread_mutex_lock(philo->left_fork);
// 			printf("Philosopher %d has taken the left fork\n", philo->id);
// 		}
// 		else
// 		{
// 			pthread_mutex_lock(philo->left_fork);
// 			printf("Philosopher %d has taken the left fork\n", philo->id);
// 			pthread_mutex_lock(philo->right_fork);
// 			printf("Philosopher %d has taken the right fork\n", philo->id);
// 		}
// 		// Eating
// 		printf("Philosopher %d is eating\n", philo->id);
// 		u_got_knocked_out(philo->eat_time);
// 		pthread_mutex_lock(&philo->table->lock);
// 		philo->last_meal = get_time();
// 		philo->count_meals++;
// 		pthread_mutex_unlock(&philo->table->lock);
// 		// Release forks
// 		pthread_mutex_unlock(philo->left_fork);
// 		pthread_mutex_unlock(philo->right_fork);
// 		// Sleeping
// 		printf("Philosopher %d is sleeping\n", philo->id);
// 		u_got_knocked_out(philo->sleep_time);
// 	}
// 	return (NULL);
// }

void	*routine(void *arg)
{
	t_philosopher	*philo;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
		u_got_knocked_out(10);
	while (1)
	{
		pthread_mutex_lock(&philo->table->lock);
		if (!philo->table->stop_simulation)
		{
			pthread_mutex_unlock(&philo->table->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->lock);
		printf("philosopher %d is thinking\n", philo->id);
		if (philo->id % 2 == 0)
		{
			first_fork = philo->right_fork;
			second_fork = philo->left_fork;
		}
		else
		{
			first_fork = philo->left_fork;
			second_fork = philo->right_fork;
		}
		pthread_mutex_lock(first_fork);
		printf("philosopher %d has taken a fork\n", philo->id);
		pthread_mutex_lock(second_fork);
		printf("philosopher %d has taken a fork\n", philo->id);
		printf("philosopher %d is eating\n", philo->id);
		u_got_knocked_out(philo->eat_time);
		pthread_mutex_lock(&philo->table->lock);
		philo->last_meal = get_time();
		philo->count_meals++;
		pthread_mutex_unlock(&philo->table->lock);
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		printf("philosopher %d is sleeping\n", philo->id);
		u_got_knocked_out(philo->sleep_time);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;
	int		all_ate;

	table = (t_table *)arg;
	while (1)
	{
		all_ate = 1;
		i = -1;
		while (++i < table->num_philosophers)
		{
			pthread_mutex_lock(&table->lock);
			if ((get_time()
					- table->philo[i].last_meal) >= table->schedule.time_to_die)
			{
				table->stop_simulation = 1;
				printf("Philosopher %d has died\n", table->philo[i].id);
				pthread_mutex_unlock(&table->lock);
				return (NULL);
			}
			if (table->schedule.num_of_to_eat > 0
				&& table->philo[i].count_meals < table->schedule.num_of_to_eat)
				all_ate = 0;
			pthread_mutex_unlock(&table->lock);
		}
		if (all_ate)
		{
			pthread_mutex_lock(&table->lock);
			table->stop_simulation = 1;
			pthread_mutex_unlock(&table->lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

static void	create_threads(t_table *table)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	if (pthread_create(&monitor, NULL, monitor_routine, table))
		return ;
	while (++i < table->num_philosophers)
	{
		if (pthread_create(&table->threads[i], NULL, routine,
				&table->philo[i]) != 0)
		{
			printf("Failed to create philosopher thread");
			pthread_mutex_lock(&table->lock);
			table->stop_simulation = 1;
			pthread_mutex_unlock(&table->lock);
			break ;
		}
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
	pthread_mutex_destroy(&table->lock);
}

void	init_philo(t_table *table)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&table->lock, NULL))
		return ;
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
		table->philo[i].last_meal = get_time();
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1)
			% table->num_philosophers];
		table->philo[i].table = table;
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
		table->schedule.num_of_to_eat = ft_atoi(av[5]);
	else
		table->schedule.num_of_to_eat = -1;
	if (table->num_philosophers <= 0 || table->schedule.time_to_die <= 0
		|| table->schedule.eat_time <= 0 || table->schedule.sleep_time <= 0)
	{
		printf("Error: Invalid input values\n");
		exit(1);
	}
}
