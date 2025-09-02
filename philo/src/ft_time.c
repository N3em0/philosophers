/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:41:39 by egache            #+#    #+#             */
/*   Updated: 2025/09/02 18:37:23 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

typedef struct timeval	t_timeval;

long	ft_time(t_monitor *monitor)
{
	if (monitor->start_time == 0)
	{
		gettimeofday(&monitor->tv, NULL);
		monitor->start_time = (monitor->tv.tv_sec * 1000) + (monitor->tv.tv_usec / 1000);
		//printf("start_time : %ld", monitor->start_time);
	}
	gettimeofday(&monitor->tv, NULL);
	//printf("time : %ld\n", (monitor->tv.tv_sec * 1000) + (monitor->tv.tv_usec / 1000) - monitor->start_time);
	return ((monitor->tv.tv_sec * 1000) + (monitor->tv.tv_usec / 1000) - monitor->start_time);
}

long	time_to_x(t_monitor *monitor, int x)
{
	pthread_mutex_lock(&monitor->time);
	gettimeofday(&monitor->tv, NULL);
	pthread_mutex_unlock(&monitor->time);
	return (ft_time(monitor) - x);
}
