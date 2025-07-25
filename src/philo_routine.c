/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:27:09 by egache            #+#    #+#             */
/*   Updated: 2025/07/25 01:14:17 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_forks(t_philo *philo, t_monitor *monitor)
{
	(void)monitor;
	if (philo->forks_handled[0] != philo->fork_id)
	{
		pthread_mutex_lock(&philo->monitor->own_fork);
		philo->forks_handled[0] = philo->fork_id;
		pthread_mutex_lock(&philo->monitor->writing);
		printf("(%ld) | philo [%d] has taken a fork\n", timetime(monitor),
			philo->fork_id);
		pthread_mutex_unlock(&philo->monitor->writing);
	}
	if (&philo->next->fork_id != &philo->fork_id)
	{
		pthread_mutex_lock(&philo->monitor->other_fork);
		philo->forks_handled[1] = philo->next->fork_id;
		philo->has_forks = true;
		pthread_mutex_lock(&philo->monitor->writing);
		printf("(%ld) | philo [%d] has taken a fork\n", timetime(monitor),
			philo->fork_id);
		pthread_mutex_unlock(&philo->monitor->writing);
		return (0);
	}
	pthread_mutex_unlock(&philo->monitor->own_fork);
	return (1);
}

int	philo_eating(t_philo *philo, t_monitor *monitor)
{
	(void)monitor;
	if (philo->has_forks)
	{
		pthread_mutex_lock(&philo->monitor->writing);
		printf("(%ld) | philo [%d] is eating\n", timetime(monitor),
			philo->fork_id);
		pthread_mutex_unlock(&philo->monitor->writing);
		usleep(monitor->time_to_eat * 1000);
		pthread_mutex_lock(&philo->monitor->last_meal);
		philo->last_meal = timetime(monitor);
		pthread_mutex_unlock(&philo->monitor->last_meal);
		philo->has_forks = false;
		philo->forks_handled[0] = -1;
		philo->forks_handled[1] = -1;
		pthread_mutex_unlock(&philo->monitor->own_fork);
		pthread_mutex_unlock(&philo->monitor->other_fork);
	}
	return (0);
}

int	philo_sleeping(t_philo *philo, t_monitor *monitor)
{
	(void)monitor;
	pthread_mutex_lock(&philo->monitor->writing);
	printf("(%ld) | philo [%d] is sleeping\n", timetime(monitor),
		philo->fork_id);
	pthread_mutex_unlock(&philo->monitor->writing);
	usleep(monitor->time_to_sleep * 1000);
	return (0);
}

int	philo_thinking(t_philo *philo, t_monitor *monitor)
{
	(void)monitor;
	pthread_mutex_lock(&philo->monitor->writing);
	printf("(%ld) | philo [%d] is thinking\n", timetime(monitor),
		philo->fork_id);
	pthread_mutex_unlock(&philo->monitor->writing);
	usleep(monitor->time_to_sleep * 1000);
	return (0);
}
