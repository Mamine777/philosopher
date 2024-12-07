/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:33:42 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/07 17:27:06 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				x = 0;
pthread_mutex_t	mutex;
void	*print6(void)
{
	x++;
	return (NULL);
}

void	*print(void *arg)
{
	int	i;

	i = 0;
	while (i < 100000)
	{
		pthread_mutex_lock(&mutex);
		x++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return (NULL);
}
void	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return ;
	printf("%ld seconds;\n", time.tv_sec);
	printf("%d micro seconds;\n", time.tv_usec);
	printf("years since 1972 : %ld\n", time.tv_sec / 60 / 60 / 24 / 356);
}

uint16_t	convert_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return (uint32_t)((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	main(int ac, char **av)
{
	uint16_t	start;
	uint16_t	now;

	start = convert_time();
	usleep(5000000);
	now = convert_time();
	// pthread_t	t1[4];
	// int			i;

	// i = 0;
	// pthread_mutex_init(&mutex, NULL);
	// while (i < 56)
	// {
	// 	pthread_create(&t1[i], NULL, &print, NULL);
	// 	printf("thread number : %d\n", i);
	// 	pthread_join(t1[i], NULL);
	// 	i++;
	// }
	// // pthread_create(&t2, NULL, &print, NULL);
	// // pthread_create(&t3, NULL, &print, NULL);
	// // pthread_create(&t4, NULL, &print, NULL);
	// // pthread_join(t2, NULL);
	// // pthread_join(t3, NULL);
	// // pthread_join(t4, NULL);
	// pthread_mutex_destroy(&mutex);
	// printf("%d\n", x);
	printf("%d milliseconds passed since the start", now - start);
}

// typedef struct t_time
// {
// 	struct t_time sec;
// 	struct t_time
// };
