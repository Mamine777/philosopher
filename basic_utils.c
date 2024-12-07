/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:47:17 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/07 19:57:12 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_all_num(char *c)
{
	if ((c <= '0' && c >= '9') || c != '-' || c != '+')
		return (1);
	return (0);
}
int	ft_atoi(void *content)
{
	while (*content)
		if (is_all_num((char)content++))
			return (0);
}