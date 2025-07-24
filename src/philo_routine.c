/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:27:09 by egache            #+#    #+#             */
/*   Updated: 2025/07/24 21:27:35 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_forks(t_philo *philo, t_monitor *monitor)
{
	(void)monitor;
	pthread_mutex_lock(&philo->monitor->own_fork);
	philo->forks_handled[0] = philo->fork_id;
	pthread_mutex_lock(&philo->monitor->writing);
	printf("(%ld) | philo [%d] has taken a fork\n", timetime(monitor),
		philo->fork_id);
	pthread_mutex_unlock(&philo->monitor->writing);
	pthread_mutex_lock(&philo->monitor->other_fork);
	philo->forks_handled[1] = philo->next->fork_id;
	philo->has_forks = true;
	pthread_mutex_lock(&philo->monitor->writing);
	printf("(%ld) | philo [%d] has taken a fork\n", timetime(monitor),
		philo->fork_id);
	pthread_mutex_unlock(&philo->monitor->writing);
	return (0);
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
		philo->has_forks = false;
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
