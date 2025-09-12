/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teatime <teatime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:41:39 by egache            #+#    #+#             */
/*   Updated: 2025/09/12 14:59:19 by teatime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

typedef struct timeval t_timeval;

int ft_time(t_monitor *monitor)
{
	if (monitor->start_time == 0)
	{
		pthread_mutex_lock(&monitor->time);
		gettimeofday(&monitor->tv, NULL);
		pthread_mutex_unlock(&monitor->time);
		monitor->start_time = (monitor->tv.tv_sec * 1000) + (monitor->tv.tv_usec / 1000);
	}
	pthread_mutex_lock(&monitor->time);
	gettimeofday(&monitor->tv, NULL);
	pthread_mutex_unlock(&monitor->time);
	return ((monitor->tv.tv_sec * 1000) + (monitor->tv.tv_usec / 1000) - monitor->start_time);
}
