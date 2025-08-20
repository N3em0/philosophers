/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:15:47 by egache            #+#    #+#             */
/*   Updated: 2025/08/20 18:17:42 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	philo_is_alive_and_hungry(t_monitor *monitor)
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

bool	ft_usleep(t_monitor *monitor, int duration)
{
	int		elapsed;
	long	start;

	elapsed = 0;
	start = ft_time(monitor);
	while ((ft_time(monitor) - start) < duration / 1000)
	{
		if (philo_is_alive_and_hungry(monitor) == false)
			return (false);
		usleep(100);
	}
	return (true);
}
