/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_forks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teatime <teatime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:09:58 by egache            #+#    #+#             */
/*   Updated: 2025/09/11 17:36:51 by teatime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int philo_left_fork(t_philo *philo, t_monitor *monitor)
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

int philo_right_fork(t_philo *philo, t_monitor *monitor)
{
	if (is_sim_running(monitor) == true)
	{
		pthread_mutex_lock(&monitor->forks[philo->r_fork - 1]);
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
