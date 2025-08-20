/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:28:53 by egache            #+#    #+#             */
/*   Updated: 2025/08/20 18:17:39 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	monitoring(t_philo **philo, t_monitor *monitor)
{
	t_philo	*current;

	current = *philo;
	while (1)
	{
		if (is_alive(current, monitor) == false)
			return (1);
		if (are_all_full(&current, monitor) == true)
			return (1);
		current = current->next;
		usleep(10);
	}
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
	(*philo)->monitor->all_full = true;
	pthread_mutex_unlock(&monitor->full_check);
	return (true);
}

bool	is_alive(t_philo *philo, t_monitor *monitor)
{
	pthread_mutex_lock(&philo->monitor->last_meal);
	pthread_mutex_lock(&monitor->death_check);
	if (time_to_x(monitor, monitor->time_to_die) > philo->last_meal
		&& monitor->alive == true)
	{
		monitor->alive = false;
		pthread_mutex_unlock(&monitor->death_check);
		pthread_mutex_lock(&philo->monitor->writing);
		printf("%ld %d died\n", (ft_time(monitor) - monitor->start_time),
			philo->fork_id);
		pthread_mutex_unlock(&philo->monitor->writing);
		pthread_mutex_unlock(&philo->monitor->last_meal);
		return (false);
	}
	pthread_mutex_unlock(&monitor->death_check);
	pthread_mutex_unlock(&philo->monitor->last_meal);
	return (true);
}
