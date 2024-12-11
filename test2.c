/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:23:22 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/10 18:27:52 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philosopher
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				eat_time;
	int				sleep_time;
}					t_philosopher;

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	printf("philosopher %d took right fork\n", philo->id);
	printf("philosopher %d took left  fork\n", philo->id);
	//
	printf("philosopher %d is eating\n", philo->id);
	usleep(philo->eat_time);
	//
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	printf("philosopher %d is sleeping\n", philo->id);
	usleep(philo->sleep_time);
	printf("philosopher %d is thinking\n", philo->id);
	usleep(1000);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philosopher	philo[250];
	pthread_t		threads[250];
	pthread_mutex_t	forks[250];
	int				num_philosophers;
	int				eat_numms;
	int				sleep_nummms;

	if (ac != 4)
	{
		return (printf("this some bullstuff\n"), 1);
	}
	num_philosophers = atoi(av[1]);
	eat_numms = atoi(av[2]) * 1000;
	sleep_nummms = atoi(av[3]) * 1000;
	for (int i = 0; i < num_philosophers; i++)
	{
		pthread_mutex_init(&forks[i], NULL);
	}
	for (int j = 0; j < num_philosophers; j++)
	{
		philo[j].id = j + 1;
		philo[j].eat_time = eat_numms;
		philo[j].sleep_time = sleep_nummms;
		philo[j].left_fork = &forks[j];
		philo[j].right_fork = &forks[(j + 1) % num_philosophers];
		pthread_create(&threads[j], NULL, routine, &philo[j]);
	}
	for (int g = 0; g < num_philosophers; g++)
	{
		pthread_join(threads[g], NULL);
	}
	for (int k = 0; k < num_philosophers; k++)
	{
		pthread_mutex_destroy(&forks[k]);
	}
	return (0);
}
