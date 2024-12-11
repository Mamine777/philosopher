/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:33:42 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/10 16:17:46 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
// int				x = 0;
// pthread_mutex_t	mutex;
// void	*print6(void)
// {
// 	x++;
// 	return (NULL);
// }

// void	*print(void *arg)
// {
// 	int	i;

// 	i = 0;
// 	while (i < 100000)
// 	{
// 		pthread_mutex_lock(&mutex);
// 		x++;
// 		pthread_mutex_unlock(&mutex);
// 		i++;
// 	}
// 	return (NULL);
// }
// void	get_time(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL))
// 		return ;
// 	printf("%ld seconds;\n", time.tv_sec);
// 	printf("%d micro seconds;\n", time.tv_usec);
// 	printf("years since 1972 : %ld\n", time.tv_sec / 60 / 60 / 24 / 356);
// }

// uint16_t	convert_time(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL))
// 		return (0);
// 	return (uint32_t)((time.tv_sec * 1000) + (time.tv_usec / 1000));
// }
// pthread_mutex_t	right_fork;
// pthread_mutex_t	left_fork;

// typedef	struct t_philosopher
// {
// 	int	id;
// 	int	time_to_sleep;
// 	int	time_to_eat;
// 	int	nbr_philos;
// 	pthread_mutex_t	forks[250]
// 	pthread_mutex_t	right_fork;
// 	pthread_mutex_t	left_fork;
// }	t_philo;

// void	*print(void *arg)
// {
// 	int	philo_num = *(int *)arg;
// 		pthread_mutex_lock(&right_fork);
// 		pthread_mutex_lock(&left_fork);
// 		printf("Philosopher number %d took right fork\n", philo_num);
// 		printf("Philosopher number %d took left fork\n", philo_num);
// 		printf("Philosopher number %d has eaten\n", philo_num);
// 		usleep(3000);
// 		printf("Philosopher number %d is sleeping\n", philo_num);
// 		pthread_mutex_unlock(&right_fork);
// 		pthread_mutex_unlock(&left_fork);
// 		usleep(1000);

// 	return (NULL);
// }


// int	main(int ac, char **av)
// {
// 	pthread_t		t1[250];
// 	t_philo			philo[250];

// 	if (ac == 4)
// 	{
// 		int nbr_philos = atoi(av[1]);
// 		int	time_to_eat = atoi(av[2]);
// 		int	time_to_eat =  atoi(av[3]);

// 		for (int i = 0; i < philo->nbr_philos; i++)
// 		{
// 			pthread_mutex_init(&philo->forks[i], NULL);
// 		}
// 		for (int j = 0; j < philo->nbr_philos)
// 		{
// 			philo[i].id = 
// 		}
// 	}







	
// 	pthread_mutex_init(&right_fork, NULL);
// 	pthread_mutex_init(&left_fork, NULL);
// 	for (int i = 0; i < philo_nbr; i++)
// 	{
// 		philo_id[i] = malloc(sizeof(int));
// 		if (!philo_id[i])
// 			return (0);
// 		*philo_id[i] = i + 1;
// 		pthread_create(&t1[i], NULL, &print, philo_id[i]);
// 	}
// 	for (int j = 0; j < philo_nbr; j++)
// 	{
// 		pthread_join(t1[j], NULL);
// 		free(philo_id[j]);
// 	}
// 	pthread_mutex_destroy(&right_fork);
// 	pthread_mutex_destroy(&left_fork);
// 	return (0);
// }


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philosopher
{
	int             id;
	int             eat_time;
	int             sleep_time;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
}               t_philosopher;

void    *philosopher_routine(void *arg)
{
	t_philosopher *philo = (t_philosopher *)arg;

	for (int i = 0; i < 100; i++)
	{
		// Try to pick up the forks
		pthread_mutex_lock(philo->right_fork);
		printf("Philosopher %d took the right fork\n", philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("Philosopher %d took the left fork\n", philo->id);

		// Simulate eating
		printf("Philosopher %d is eating\n", philo->id);
		usleep(philo->eat_time);

		// Put down the forks
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		// Simulate sleeping
		printf("Philosopher %d is sleeping\n", philo->id);
		usleep(philo->sleep_time);

		// Simulate thinking
		printf("Philosopher %d is thinking\n", philo->id);
		usleep(1000);
	}

	return (NULL);
}

int main(int ac, char **av)
{
	if (ac != 4)
	{
		printf("Usage: %s <number_of_philosophers> <eat_time> <sleep_time>\n", av[0]);
		return (1);
	}

	int num_philosophers = atoi(av[1]);
	int eat_time = atoi(av[2]) * 1000; // Convert milliseconds to microseconds
	int sleep_time = atoi(av[3]) * 1000; // Convert milliseconds to microseconds

	if (num_philosophers < 1 || num_philosophers > 250)
	{
		printf("Number of philosophers must be between 1 and 250\n");
		return (1); 
	}

	pthread_t       threads[250];
	t_philosopher   philosophers[250];
	pthread_mutex_t forks[250];

	// Initialize forks
	for (int i = 0; i < num_philosophers; i++)
		pthread_mutex_init(&forks[i], NULL);

	// Initialize philosophers
	for (int i = 0; i < num_philosophers; i++)
	{
		philosophers[i].id = i + 1;
		philosophers[i].eat_time = eat_time;
		philosophers[i].sleep_time = sleep_time;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % num_philosophers]; // Circular array for forks

		pthread_create(&threads[i], NULL, philosopher_routine, &philosophers[i]);
	}

	// Wait for all threads to finish
	for (int i = 0; i < num_philosophers; i++)
		pthread_join(threads[i], NULL);

	// Destroy forks
	for (int i = 0; i < num_philosophers; i++)
		pthread_mutex_destroy(&forks[i]);

	return (0);
}
