/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:28:53 by egache            #+#    #+#             */
/*   Updated: 2025/07/24 21:36:05 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool is_alive(t_philo *philo, t_monitor *monitor)
{
	pthread_mutex_lock(&philo->monitor->last_meal);
	if (time_to_x(monitor, monitor->time_to_die) > philo->last_meal)
		monitor->alive = false;
	pthread_mutex_unlock(&philo->monitor->last_meal);
	return (monitor->alive);
}
