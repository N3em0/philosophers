/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:28:53 by egache            #+#    #+#             */
/*   Updated: 2025/09/02 20:10:48 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	monitoring(t_philo **philo, t_monitor *monitor)
{
	t_philo	*current;

	current = *philo;
	while (is_alive(current, monitor) == true)
	{
		if (monitor->meal_countdown == true)
		{
			if (are_all_full(&current, monitor) == true)
				return (1);
		}
		current = current->next;
		usleep(50);
	}
	return (1);
}

bool	are_all_full(t_philo **philo, t_monitor *monitor)
{
	t_philo	*current;

	current = *philo;
	while (current->next != *philo && current->next != NULL)
	{
		pthread_mutex_lock(&monitor->full_check);
		if (current->full == false)
		{
			pthread_mutex_unlock(&monitor->full_check);
			return (false);
		}
		pthread_mutex_unlock(&monitor->full_check);
		current = current->next;
	}
	pthread_mutex_lock(&monitor->full_check);
	if (current->full == false)
	{
		pthread_mutex_unlock(&monitor->full_check);
		return (false);
	}
	pthread_mutex_unlock(&monitor->full_check);
	pthread_mutex_lock(&monitor->start);
	monitor->sim_running = false;
	pthread_mutex_unlock(&monitor->start);
	return (true);
}

bool	is_alive(t_philo *philo, t_monitor *monitor)
{
	pthread_mutex_lock(&philo->monitor->last_meal);
	if (time_to_x(monitor, monitor->time_to_die) > philo->last_meal)
	{
		pthread_mutex_unlock(&philo->monitor->last_meal);
		pthread_mutex_lock(&philo->monitor->start);
		philo->monitor->sim_running = false;
		pthread_mutex_unlock(&philo->monitor->start);
		pthread_mutex_lock(&philo->monitor->writing);
		printf("%ld %d died\n", (ft_time(monitor)),
			philo->fork_id);
		pthread_mutex_unlock(&philo->monitor->writing);
		return (false);
	}
	pthread_mutex_unlock(&philo->monitor->last_meal);
	return (true);
}
