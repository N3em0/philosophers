/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teatime <teatime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:27:09 by egache            #+#    #+#             */
/*   Updated: 2025/09/02 00:25:34 by teatime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int philo_logs(t_monitor *monitor, int philo_id, char *log)
{
	if (philo_is_alive_and_hungry(monitor) == true)
	{
		pthread_mutex_lock(&monitor->writing);
		printf(log, (ft_time(monitor) - monitor->start_time), philo_id);
		pthread_mutex_unlock(&monitor->writing);
		return (0);
	}
	return (1);
}

int philo_forks(t_philo *philo, t_monitor *monitor)
{
	while (philo_is_alive_and_hungry(monitor) == true)
	{
		pthread_mutex_lock(&monitor->forks_taken[philo->l_fork - 1]);
		pthread_mutex_lock(&monitor->forks_taken[philo->r_fork - 1]);
		if (monitor->fork_taken[philo->l_fork - 1] == false && monitor->fork_taken[philo->r_fork - 1] == false)
		{
			monitor->fork_taken[philo->l_fork - 1] = true;
			monitor->fork_taken[philo->r_fork - 1] = true;
			pthread_mutex_unlock(&monitor->forks_taken[philo->l_fork - 1]);
			pthread_mutex_unlock(&monitor->forks_taken[philo->r_fork - 1]);
			break;
		}
		pthread_mutex_unlock(&monitor->forks_taken[philo->l_fork - 1]);
		pthread_mutex_unlock(&monitor->forks_taken[philo->r_fork - 1]);
		usleep(5);
	}
	pthread_mutex_lock(&monitor->forks[philo->l_fork - 1]);
	pthread_mutex_lock(&monitor->forks[philo->r_fork - 1]);
	if (philo_left_fork(philo, monitor) || philo_right_fork(philo, monitor))
		return (1);
	return (0);
}

int philo_eating(t_philo *philo, t_monitor *monitor)
{
	philo_countdown(philo, monitor);
	if (philo_logs(monitor, philo->fork_id, "%ld %d is eating\n") == 1)
	{
		pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
		pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
		return (1);
	}
	philo_update_last_meal(philo, monitor);
	if (ft_usleep(monitor, monitor->time_to_eat) == false)
	{
		pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
		pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
		return (1);
	}
	pthread_mutex_lock(&monitor->forks_taken[philo->l_fork - 1]);
	pthread_mutex_lock(&monitor->forks_taken[philo->r_fork - 1]);
	monitor->fork_taken[philo->l_fork - 1] = false;
	monitor->fork_taken[philo->r_fork - 1] = false;
	pthread_mutex_unlock(&monitor->forks_taken[philo->l_fork - 1]);
	pthread_mutex_unlock(&monitor->forks_taken[philo->r_fork - 1]);
	pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
	pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
	if (philo_is_alive_and_hungry(monitor) == false)
		return (1);
	return (0);
}

int philo_sleeping(t_philo *philo, t_monitor *monitor)
{
	if (philo_logs(monitor, philo->fork_id, "%ld %d is sleeping\n") == 1)
		return (1);
	if (ft_usleep(monitor, monitor->time_to_sleep) == false)
		return (1);
	return (0);
}

int philo_thinking(t_philo *philo, t_monitor *monitor)
{
	if (philo_logs(monitor, philo->fork_id,
				   "%ld %d is thinking\n") == 1)
		return (1);
	return (0);
}
