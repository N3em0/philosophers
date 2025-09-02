/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:15:47 by egache            #+#    #+#             */
/*   Updated: 2025/09/02 19:48:13 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_sim_running(t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->start);
	if (monitor->sim_running == true)
	{
		pthread_mutex_unlock(&monitor->start);
		return (true);
	}
	pthread_mutex_unlock(&monitor->start);
	return (false);
}

bool	ft_usleep(t_monitor *monitor, int duration)
{
	long	start;
	long	elapsed;
	int		sleep_time;

	start = ft_time(monitor);
	while ((elapsed = ft_time(monitor) - start) < duration)
	{
		if (is_sim_running(monitor) == false)
			return (false);
		if (duration - elapsed > 10)
			sleep_time = 1000;
		else
			sleep_time = 100;
		usleep(sleep_time);
	}
	return (true);
}
// bool	ft_usleep(t_monitor *monitor, int duration)
// {
// 	long	start;

// 		start = ft_time(monitor);
// 	while ((ft_time(monitor) - start) < duration)
// 	{
// 		if (is_sim_running(monitor) == false)
// 			return (false);
// 		usleep(100);
// 	}
// 	return (true);
// }
