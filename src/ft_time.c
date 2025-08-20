/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:41:39 by egache            #+#    #+#             */
/*   Updated: 2025/08/20 15:42:15 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
1 millisecond = 1000 microseconds

time in arguments are in milliseconds -> 400ms = 400 x 1000
*/

long	ft_time(t_monitor *monitor)
{
	long	set_time;

	pthread_mutex_lock(&monitor->time);
	gettimeofday(&monitor->tv, NULL);
	set_time = (monitor->tv.tv_sec * 1000) + (monitor->tv.tv_usec / 1000);
	pthread_mutex_unlock(&monitor->time);
	return (set_time);
}

long	time_to_x(t_monitor *monitor, int x)
{
	pthread_mutex_lock(&monitor->time);
	gettimeofday(&monitor->tv, NULL);
	pthread_mutex_unlock(&monitor->time);
	return ((monitor->tv.tv_sec * 1000) + (monitor->tv.tv_usec / 1000) - x);
}
