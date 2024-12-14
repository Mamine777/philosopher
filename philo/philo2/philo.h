/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:38:53 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/14 19:34:44 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_schedule
{
	long				eat_time;
	long				sleep_time;
	unsigned long long	time_to_die;
	long				num_of_to_eat;
}						t_schedule;

typedef struct s_philosopher
{
	int					id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	long				start;
	long				last_meal;
	int					count_meals;
	t_schedule			schedule;
	struct s_table		*table;
}						t_philosopher;

typedef struct s_table
{
	pthread_mutex_t		forks[200];
	pthread_t			threads[200];
	t_philosopher		philo[200];
	pthread_mutex_t		lock;
	pthread_mutex_t		print_lock;
	long				num_philosophers;
	bool				stop_simulation;
	int					meals_completed;
	t_schedule			schedule;
}						t_table;

void					err_exit(const char *str);
int						ft_atoi(const char *str);
int						init_philo(t_table *table);
void					manage_failed_thread(pthread_mutex_t *mutex,
							t_table *table);
int						create_threads(t_table *table);
void					*simulation(void *arg);
uint64_t				get_time(void);
void					u_got_knocked_out(long long ms);
int						log_action(t_philosopher *philo, const char *action);
void					*guard_the_simulation(void *arg);
void					fill_table(t_table *table, char **av);
int						philo_takes_forks(t_philosopher *philo);
#endif