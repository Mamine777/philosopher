/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:32:52 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/07 20:02:38 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct t_time_value
{
	time_t		tv_sec;
	suseconds_t	tv_usec;
}				t_time;

typedef struct t_philosopher
{
	int			philos;
	int			phlo_num;
	int			total_fork;
}				t_philosopher;

typedef struct t_schedule
{
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_think;
}	t_schedule;