/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:41:39 by egache            #+#    #+#             */
/*   Updated: 2025/09/12 16:39:24 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_time(t_monitor *monitor)
{
	if (monitor->start_time == 0)
	{
		pthread_mutex_lock(&monitor->time);
		gettimeofday(&monitor->tv, NULL);
		pthread_mutex_unlock(&monitor->time);
		monitor->start_time = (monitor->tv.tv_sec * 1000) + (monitor->tv.tv_usec
				/ 1000);
	}
	pthread_mutex_lock(&monitor->time);
	gettimeofday(&monitor->tv, NULL);
	pthread_mutex_unlock(&monitor->time);
	return ((monitor->tv.tv_sec * 1000) + (monitor->tv.tv_usec / 1000)
		- monitor->start_time);
}
