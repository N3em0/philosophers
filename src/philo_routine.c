/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:27:09 by egache            #+#    #+#             */
/*   Updated: 2025/08/20 18:16:15 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_logs(t_monitor *monitor, int philo_id, char *log)
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

int	philo_forks(t_philo *philo, t_monitor *monitor)
{
	if (philo_is_alive_and_hungry(monitor) == true)
	{
		philo->l_fork = philo->fork_id;
		philo->r_fork = philo->next->fork_id;
		if (philo->fork_id % 2 != 0)
		{
			philo->l_fork = philo->next->fork_id;
			philo->r_fork = philo->fork_id;
		}
		if (philo_left_fork(philo, monitor))
			return (1);
		if (philo_right_fork(philo, monitor))
			return (1);
	}
	return (0);
}

int	philo_eating(t_philo *philo, t_monitor *monitor)
{
	if (philo->has_forks)
	{
		philo_countdown(philo, monitor);
		if (philo_logs(monitor, philo->fork_id, "%ld %d is eating\n") == 1)
		{
			pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
			pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
			return (1);
		}
		philo_update_last_meal(philo, monitor);
		if (ft_usleep(monitor, monitor->time_to_eat * 1000) == false)
		{
			pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
			pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
			return (1);
		}
		philo->has_forks = false;
		philo->forks_handled[0] = -1;
		philo->forks_handled[1] = -1;
		pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
		pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
		if (philo_is_alive_and_hungry(monitor) == false)
			return (1);
	}
	return (0);
}

int	philo_sleeping(t_philo *philo, t_monitor *monitor)
{
	if (philo_logs(monitor, philo->fork_id, "%ld %d is sleeping\n") == 1)
		return (1);
	if (ft_usleep(monitor, monitor->time_to_sleep * 1000) == false)
		return (1);
	return (0);
}

int	philo_thinking(t_philo *philo, t_monitor *monitor)
{
	if (philo_is_alive_and_hungry(monitor) == true)
	{
		if (philo_logs(monitor, philo->fork_id,
				"%ld %d is thinking\n") == 1)
			return (1);
		usleep(1);
		return (0);
	}
	return (1);
}
