/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:28:53 by egache            #+#    #+#             */
/*   Updated: 2025/07/30 01:18:28 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// bool is_alive(t_philo *philo, t_monitor *monitor)
// {
// 	pthread_mutex_lock(&philo->monitor->last_meal);
// 	if (time_to_x(monitor, monitor->time_to_die) > philo->last_meal)
// 	{
// 		monitor->alive = false;
// 		pthread_mutex_lock(&philo->monitor->writing);
// 		printf("(%ld) | philo [%d] has died and last meal was %ld\n", timetime(monitor),
// 		philo->fork_id, philo->last_meal);
// 		pthread_mutex_unlock(&philo->monitor->writing);
// 		exit(0);
// 	}
// 	pthread_mutex_unlock(&philo->monitor->last_meal);
// 	return (monitor->alive);
// }

/*
CAN WORK IF LAST_MEAL IS SET UP FOR EVERYTHREAD BEFORE DOIN THIS FUNCTION :

- NEED START MUTEX SO EVERY THREAD START AT THE SAME TIME

*/


// bool	is_alive(t_philo *philo, t_monitor *monitor)
// {
// 	t_philo	*current;

// 	current = philo;
// 	while (current->next != NULL && current->next != philo)
// 	{
// 		//printf(" philo[%d] node |||| philo[%d] address : %p\n",philo->fork_id, current->fork_id, current);
// 		pthread_mutex_lock(&current->monitor->last_meal);
// 		if (time_to_x(monitor, monitor->time_to_die) > current->last_meal)
// 		{
// 			monitor->alive = false;
// 			pthread_mutex_lock(&current->monitor->writing);
// 			printf("(%ld) | philo [%d] has died and last meal was %ld\n",
// 				timetime(monitor), current->fork_id, current->last_meal);
// 			pthread_mutex_unlock(&current->monitor->writing);
// 			pthread_mutex_unlock(&current->monitor->last_meal);
// 			exit(0);
// 		}
// 		pthread_mutex_unlock(&current->monitor->last_meal);
// 		current = current->next;
// 	}
// 	//printf(" philo[%d] node |||| philo[%d] address : %p\n",philo->fork_id, current->fork_id, current);
// 	pthread_mutex_lock(&current->monitor->last_meal);
// 	if (time_to_x(monitor, monitor->time_to_die) > current->last_meal)
// 	{
// 		monitor->alive = false;
// 		pthread_mutex_lock(&current->monitor->writing);
// 		printf("(%ld) | philo [%d] has died and last meal was %ld\n",
// 			timetime(monitor), current->fork_id, current->last_meal);
// 		pthread_mutex_unlock(&current->monitor->writing);
// 		pthread_mutex_unlock(&current->monitor->last_meal);
// 		exit(0);
// 	}
// 	pthread_mutex_unlock(&current->monitor->last_meal);
// 	return (monitor->alive);
// }
