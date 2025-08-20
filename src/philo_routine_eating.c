/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_eating.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:12:04 by egache            #+#    #+#             */
/*   Updated: 2025/08/20 18:12:31 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_countdown(t_philo *philo, t_monitor *monitor)
{
	if (monitor->meal_countdown == true)
	{
		pthread_mutex_lock(&monitor->meals_count);
		if (philo->meals_count < monitor->meals_needed)
			philo->meals_count++;
		else
		{
			pthread_mutex_lock(&monitor->full_check);
			philo->full = true;
			pthread_mutex_unlock(&monitor->full_check);
		}
		pthread_mutex_unlock(&philo->monitor->meals_count);
	}
}

void	philo_update_last_meal(t_philo *philo, t_monitor *monitor)
{
	pthread_mutex_lock(&philo->monitor->last_meal);
	philo->last_meal = ft_time(monitor);
	pthread_mutex_unlock(&philo->monitor->last_meal);
}
