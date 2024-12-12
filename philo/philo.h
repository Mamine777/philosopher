/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:45:22 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/12 17:16:32 by mokariou         ###   ########.fr       */
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
	long			time_to_die;
	long			num_of_to_eat;
}					t_schedule;

typedef struct s_philosopher
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal;
	int				did_he_eat;// bool
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
	t_philosopher	philo[200];
	t_schedule		schedule;
	int				stop_simulation;
	pthread_mutex_t	lock;
}					t_table;

/// error_checking
void				err_exit(const char *str);
///*****utils
int					ft_atoi(const char *str);
long			get_time(void);
void				u_got_knocked_out(long long ms);

/// main
void				init_philo(t_table *table);
void				fill_table(t_table *table, char **av);
#endif