/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teatime <teatime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:15:47 by egache            #+#    #+#             */
/*   Updated: 2025/09/02 00:18:41 by teatime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool philo_is_alive_and_hungry(t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->death_check);
	pthread_mutex_lock(&monitor->full_check);
	if (monitor->alive == true && monitor->all_full == false)
	{
		pthread_mutex_unlock(&monitor->full_check);
		pthread_mutex_unlock(&monitor->death_check);
		return (true);
	}
	pthread_mutex_unlock(&monitor->full_check);
	pthread_mutex_unlock(&monitor->death_check);
	return (false);
}

bool ft_usleep(t_monitor *monitor, int duration)
{
	long start;

	start = ft_time(monitor);
	while ((ft_time(monitor) - start) < duration)
	{
		if (philo_is_alive_and_hungry(monitor) == false)
			return (false);
		usleep(200);
	}
	return (true);
}
