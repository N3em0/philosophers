/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_forks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:09:58 by egache            #+#    #+#             */
/*   Updated: 2025/09/12 16:47:15 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	forks_availability(t_philo *philo, t_monitor *monitor)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&monitor->forks_taken[philo->l_fork - 1]);
	if (monitor->fork_taken[philo->l_fork - 1] == false)
		monitor->fork_taken[philo->l_fork - 1] = true;
	pthread_mutex_unlock(&monitor->forks_taken[philo->l_fork - 1]);
	pthread_mutex_lock(&monitor->forks_taken[philo->r_fork - 1]);
	if (monitor->fork_taken[philo->r_fork - 1] == false)
	{
		monitor->fork_taken[philo->r_fork - 1] = true;
		if (monitor->fork_taken[philo->l_fork - 1] == true)
			ret = true;
	}
	pthread_mutex_unlock(&monitor->forks_taken[philo->r_fork - 1]);
	return (ret);
}

int	philo_left_fork(t_philo *philo, t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->forks[philo->l_fork - 1]);
	if (is_sim_running(monitor) == true)
	{
		if (philo_logs(monitor, philo->fork_id,
				"%d %d has taken a fork\n") == 1)
		{
			pthread_mutex_unlock(&monitor->forks[philo->l_fork - 1]);
			return (1);
		}
		return (0);
	}
	pthread_mutex_unlock(&monitor->forks[philo->l_fork - 1]);
	return (1);
}

int	philo_right_fork(t_philo *philo, t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->forks[philo->r_fork - 1]);
	if (is_sim_running(monitor) == true)
	{
		if (philo_logs(monitor, philo->fork_id,
				"%d %d has taken a fork\n") == 1)
		{
			pthread_mutex_unlock(&monitor->forks[philo->l_fork - 1]);
			pthread_mutex_unlock(&monitor->forks[philo->r_fork - 1]);
			return (1);
		}
		return (0);
	}
	pthread_mutex_unlock(&monitor->forks[philo->l_fork - 1]);
	pthread_mutex_unlock(&monitor->forks[philo->r_fork - 1]);
	return (1);
}
