/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:28:53 by egache            #+#    #+#             */
/*   Updated: 2025/08/19 15:50:36 by egache           ###   ########.fr       */
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
		printf("%ld %d died\n", (timetime(monitor) - monitor->start_time),
			philo->fork_id);
		pthread_mutex_unlock(&philo->monitor->writing);
		pthread_mutex_unlock(&philo->monitor->last_meal);
		return (false);
	}
	pthread_mutex_unlock(&monitor->death_check);
	pthread_mutex_unlock(&philo->monitor->last_meal);
	return (true);
}

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
// 		//printf(" philo[%d] node |||| philo[%d] address : %p\n",philo->fork_id,
			//current->fork_id, current);
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
// 	//printf(" philo[%d] node |||| philo[%d] address : %p\n",philo->fork_id,
		//current->fork_id, current);
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
