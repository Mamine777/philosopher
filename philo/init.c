/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:05:19 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/13 13:34:12 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philosopher	*philo;
	// pthread_mutex_t	*first_fork;
	// pthread_mutex_t	*second_fork;

	philo = (t_philosopher *)arg;
	while (1)
	{
		if (philo->id % 2 == 0)
			u_got_knocked_out(10);
		pthread_mutex_lock(&philo->table->lock);
		if (philo->table->stop_simulation)
		{
			pthread_mutex_unlock(&philo->table->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->lock);
		// if (philo->id % 2 == 0)
		// {
		// 	first_fork = philo->left_fork;
		// 	second_fork = philo->right_fork;
		// }
		// else
		// {
		// 	first_fork = philo->right_fork;
		// 	second_fork = philo->left_fork;
		// }
		pthread_mutex_lock(philo->right_fork);
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		log_action(philo, "has taken a fork");
		log_action(philo, "is eating");
		pthread_mutex_lock(&philo->table->lock);
		philo->last_meal = get_time();
		philo->count_meals++;
		if (philo->count_meals == philo->num_of_to_eat)
			philo->table->num_full++;
		pthread_mutex_unlock(&philo->table->lock);
		u_got_knocked_out(philo->eat_time);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		log_action(philo, "is sleeping");
		u_got_knocked_out(philo->sleep_time);
		log_action(philo, "is thinking");
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	//int		all_ate;
	int		i;

	table = (t_table *)arg;
	while (1)
	{
		//all_ate = 1;
		i = -1;
		while (++i < table->num_philosophers)
		{
			pthread_mutex_lock(&table->lock);
			if (get_time()
				- table->philo[i].last_meal >= table->schedule.time_to_die)
			{
				write(1,"hello\n",6);
				printf("Philosopher %d has died\n", table->philo[i].id);
				table->stop_simulation = 1;
				pthread_mutex_unlock(&table->lock);
				return (NULL);
			}
			// if (table->schedule.num_of_to_eat != -1
			// 	&& table->philo[i].count_meals <= table->schedule.num_of_to_eat)
			// {
			// 	all_ate = 0;
			// }
			// if (table->schedule.num_of_to_eat != -1)
			// 	all_ate = 0;
			pthread_mutex_unlock(&table->lock);
		}
		// if (table->num_full == table->philo->num_of_to_eat)
		// {
		// 	pthread_mutex_lock(&table->lock);
		// 	table->stop_simulation = 1;
		// 	pthread_mutex_unlock(&table->lock);
		// 	return (NULL);
		// }
		usleep(5000);
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
	pthread_mutex_destroy(&table->print_lock);
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
	pthread_mutex_init(&table->print_lock, NULL);
	table->num_philosophers = ft_atoi(av[1]);
	table->schedule.time_to_die = ft_atoi(av[2]);
	table->schedule.eat_time = ft_atoi(av[3]);
	table->schedule.sleep_time = ft_atoi(av[4]);
	table->stop_simulation = 0;
	if (av[6])
		table->schedule.num_of_to_eat = ft_atoi(av[6]);
	else
		table->schedule.num_of_to_eat = -1;
	table->num_full = 0;
	if (table->num_philosophers <= 0 || table->schedule.time_to_die <= 0
		|| table->schedule.eat_time <= 0 || table->schedule.sleep_time <= 0)
	{
		printf("Error: Invalid input values\n");
		exit(1);
	}
}
