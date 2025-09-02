/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:27:09 by egache            #+#    #+#             */
/*   Updated: 2025/09/02 20:14:25 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_logs(t_monitor *monitor, int philo_id, char *log)
{
	if (is_sim_running(monitor) == true)
	{
		pthread_mutex_lock(&monitor->writing);
		printf(log, (ft_time(monitor)), philo_id);
		pthread_mutex_unlock(&monitor->writing);
		return (0);
	}
	return (1);
}

bool	forks_availability(t_philo *philo, t_monitor *monitor)
{
		bool ret;

		ret = false;
		pthread_mutex_lock(&monitor->forks_taken[philo->l_fork - 1]);
		pthread_mutex_lock(&monitor->forks_taken[philo->r_fork - 1]);
		if (monitor->fork_taken[philo->l_fork - 1] == false
			&& monitor->fork_taken[philo->r_fork - 1] == false)
		{
			ret = true;
			monitor->fork_taken[philo->l_fork - 1] = true;
			monitor->fork_taken[philo->r_fork - 1] = true;
		}
		pthread_mutex_unlock(&monitor->forks_taken[philo->r_fork - 1]);
		pthread_mutex_unlock(&monitor->forks_taken[philo->l_fork - 1]);
		return(ret);
}

int	philo_forks(t_philo *philo, t_monitor *monitor)
{
	if (philo->fork_id == philo->next->fork_id)
		return (1);
	while (is_sim_running(monitor) == true)
	{
		if (forks_availability(philo, monitor) == true)
		{
			pthread_mutex_lock(&monitor->forks[philo->l_fork - 1]);
			pthread_mutex_lock(&monitor->forks[philo->r_fork - 1]);
			if (philo_left_fork(philo, monitor) || philo_right_fork(philo, monitor))
				return (1);
			return (0);
		}
		usleep(5);
	}
	return (1);
	}

int	philo_eating(t_philo *philo, t_monitor *monitor)
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
	if (is_sim_running(monitor) == false)
		return (1);
	return (0);
}

int	philo_sleeping(t_philo *philo, t_monitor *monitor)
{
	if (philo_logs(monitor, philo->fork_id, "%ld %d is sleeping\n") == 1)
		return (1);
	if (ft_usleep(monitor, monitor->time_to_sleep) == false)
		return (1);
	if (is_sim_running(monitor) == false)
		return (1);
	return (0);
}

int	philo_thinking(t_philo *philo, t_monitor *monitor)
{
	if (philo_logs(monitor, philo->fork_id, "%ld %d is thinking\n") == 1)
		return (1);
	//usleep(1);
	// if (is_sim_running(monitor) == false)
	// 	return (1);
	return (0);
}
