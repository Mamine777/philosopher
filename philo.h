/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:32:52 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/09 13:07:41 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_code;

typedef struct t_forks
{
	pthread_mutex_t fork;
	int				fork_id;// which fork the philo have taken
}	t_forks;

typedef struct t_philosopher
{
	int			id;
	long long	meals_count;
	int			full_bool;//bool is the philo have eaten the max of the meals
	long long	last_meal_time; // time past from the last meal for each philo
	t_forks		*first_fork;
	t_forks		*second_fork;
	pthread_t	thread_id;// for each philo
	t_table		*table;
}				t_philosopher;

typedef struct t_table
{
	long	philo_nbr;
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_die;
	long	nbr_limits_meal;// if flag is -1 means we dont have the argument
	long	start_of_simulation;
	int		end_simulation; // philo dies
	t_forks		*forks;
	t_philosopher	*philo;
}					t_table;

//error checking && safe checking
void	*save_malloc(size_t count_bytes);
void	err_exit(char *arg);
void	handle_mutex(pthread_mutex_t *mutex, t_code code);
void	handle_thread(pthread_t *thread, void *(*foo)(void *), void *data, t_code code);
//*****//parsing
void	check_table(t_table *table, char **av);
//*****//
void	init_info(t_table *table);
#endif