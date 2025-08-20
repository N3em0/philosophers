/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_forks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:09:58 by egache            #+#    #+#             */
/*   Updated: 2025/08/20 18:10:35 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_left_fork(t_philo *philo, t_monitor *monitor)
{
	if (philo_is_alive_and_hungry(monitor) == true)
	{
		if (philo->forks_handled[0] != philo->fork_id)
		{
			pthread_mutex_lock(&philo->monitor->forks[philo->l_fork - 1]);
			philo->forks_handled[0] = philo->l_fork;
			if (philo_logs(monitor, philo->fork_id,
					"%ld %d has taken a fork\n") == 1)
			{
				pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
				return (1);
			}
		}
		else
		{
			pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
			return (1);
		}
	}
	else
		return (1);
	return (0);
}

int	philo_right_fork(t_philo *philo, t_monitor *monitor)
{
	if (philo_is_alive_and_hungry(monitor) == true)
	{
		if (philo->next->fork_id != philo->fork_id)
		{
			pthread_mutex_lock(&philo->monitor->forks[philo->r_fork - 1]);
			philo->forks_handled[1] = philo->r_fork;
			philo->has_forks = true;
			if (philo_logs(monitor, philo->fork_id,
					"%ld %d has taken a fork\n") == 1)
			{
				pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
				pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
				return (1);
			}
			return (0);
		}
		pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
		return (1);
	}
}
