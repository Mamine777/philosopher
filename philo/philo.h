/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:45:22 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/14 17:21:41 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_schedule
{
	long			eat_time;
	long			sleep_time;
	long long			time_to_die;
	long			num_of_to_eat;
}					t_schedule;

typedef struct s_philosopher
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long			last_meal;
	int did_he_eat; // bool
	int				count_meals;
	struct s_table	*table;
	//////
	long			eat_time;
	long			sleep_time;
	long			time_to_die;
	long			num_of_to_eat;
}					t_philosopher;

typedef struct s_table
{
	pthread_mutex_t	forks[200];
	pthread_t		threads[200];
	long			num_philosophers;
	int				num_full;
	t_philosopher	philo[200];
	t_schedule		schedule;
	int				stop_simulation;
	pthread_mutex_t	lock;
	pthread_mutex_t	print_lock;
}					t_table;

/// error_checking
void				err_exit(const char *str);
///*****utils
int					ft_atoi(const char *str);
uint64_t			get_time(void);
void				u_got_knocked_out(long long ms);

/// main
void				init_philo(t_table *table);
void				fill_table(t_table *table, char **av);
int					log_action(t_philosopher *philo, const char *action);
int					philo_takes_forks(t_philosopher *philo);
#endif