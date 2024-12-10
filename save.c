/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 13:59:34 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/09 20:35:14 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*save_malloc(size_t count_bytes)
{
	void	*pd;

	pd = malloc(count_bytes);
	if (!pd)
		err_exit("malloc problem");
	return (pd);
}

static void	handle_mutex_err(int status, t_code code)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (LOCK == code || UNLOCK == code))
		err_exit("The value specified by mutex is not valid .");
	else if (status == EINVAL && INIT == code)
		err_exit("The value specified by attr is not valid .");
	else if (status == EDEADLK)
		err_exit("a dealloc would accure if the thread is blocked for mutex .");
	else if (status == ENOMEM)
		err_exit("The process cant allocate enough memory to create another mutex");
	else if (status == EBUSY)
		err_exit("mutex is locked");
}

// mutex safe containing mutex lock unlock destroy unlock
void	handle_mutex(pthread_mutex_t *mutex, t_code code)
{
	if (code == LOCK)
		pthread_mutex_lock(mutex);
	else if (code == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (code == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (code == DESTROY)
		pthread_mutex_destroy(mutex);
	else
		err_exit("wrong code in handle mutex function");
}

static void	handle_thread_error(int status, t_code code)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		err_exit("NO resources to create another thread");
	else if (status == EPERM)
		err_exit("The caller doesn't have appropiate permission");
	else if (status == EINVAL && code == CREATE)
		err_exit("The specified by attr us invalid");
	else if (status == EINVAL && (code == JOIN || code == DETACH))
		err_exit("The caller doesn't have appropiate permission");
	else if (status == ESRCH)
		err_exit("No thread could be found corresponding to that thread");
	else if (status == EDEADLK)
		err_exit("a deadlock was detected");
}

void	handle_thread(pthread_t *thread, void *(*foo)(void *), void *data, t_code code)
{
	if (code == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), code);
	else if (code == JOIN)
		handle_thread_error(pthread_join(thread, NULL), code);
	else if (code == DETACH)
		handle_thread_error(pthread_detach(*thread), code);
	else 
		err_exit("Wrong code for thread_handle");
}