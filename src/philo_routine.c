/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:27:09 by egache            #+#    #+#             */
/*   Updated: 2025/07/31 02:54:47 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_logs(t_monitor *monitor, t_philo *philo, int philo_id, char *log)
{
	if (is_alive(philo, monitor) == true)
	{
		pthread_mutex_lock(&monitor->writing);
		printf(log, (timetime(monitor) - monitor->start_time), philo_id);
		pthread_mutex_unlock(&monitor->writing);
		return (0);
	}
	pthread_mutex_unlock(&monitor->death_check);
	return (1);
}

int	philo_forks(t_philo *philo, t_monitor *monitor)
{
	philo->l_fork = philo->fork_id;
	philo->r_fork = philo->next->fork_id;
	if (philo->fork_id % 2 != 0)
	{
		philo->l_fork = philo->next->fork_id;
		philo->r_fork = philo->fork_id;
	}
	if (philo->forks_handled[0] != philo->fork_id)
	{
		pthread_mutex_lock(&monitor->death_check);
		if (monitor->alive == false)
		{
			pthread_mutex_unlock(&monitor->death_check);
			return (1);
		}
		pthread_mutex_unlock(&monitor->death_check);
		pthread_mutex_lock(&philo->monitor->forks[philo->l_fork - 1]);
		philo->forks_handled[0] = philo->l_fork;
		if (philo_logs(monitor, philo, philo->fork_id, "%ld %d has taken a fork\n") == 1)
		{
			pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
			return (1);
		}
	}
	if (&philo->next->fork_id != &philo->fork_id)
	{
		pthread_mutex_lock(&monitor->death_check);
		if (monitor->alive == false)
		{
			pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
			pthread_mutex_unlock(&monitor->death_check);
			return (1);
		}
		pthread_mutex_unlock(&monitor->death_check);
		pthread_mutex_lock(&philo->monitor->forks[philo->r_fork - 1]);
		philo->forks_handled[1] = philo->r_fork;
		philo->has_forks = true;
		if (philo_logs(monitor, philo, philo->fork_id, "%ld %d has taken a fork\n") == 1)
		{
			pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
			pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
			return (1);
		}
		return (0);
	}
	pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
	return (1);
}

int	philo_eating(t_philo *philo, t_monitor *monitor)
{
	if (philo->has_forks)
	{
		if (philo_logs(monitor, philo, philo->fork_id, "%ld %d is eating\n") == 1)
		{
			pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
			pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
			return (1);
		}
		usleep(monitor->time_to_eat * 1000);
		pthread_mutex_lock(&philo->monitor->last_meal);
		philo->last_meal = timetime(monitor);
		pthread_mutex_unlock(&philo->monitor->last_meal);
		philo->has_forks = false;
		philo->forks_handled[0] = -1;
		philo->forks_handled[1] = -1;
		pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
		pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
	}
	return (0);
}

int	philo_sleeping(t_philo *philo, t_monitor *monitor)
{
	if (philo_logs(monitor, philo, philo->fork_id, "%ld %d is sleeping\n") == 1)
		return (1);
	usleep(monitor->time_to_sleep * 1000);
	return (0);
}

int	philo_thinking(t_philo *philo, t_monitor *monitor)
{
	if (philo_logs(monitor, philo, philo->fork_id, "%ld %d is thinking\n") == 1)
		return (1);
	usleep(monitor->time_to_sleep * 1000);
	return (0);
}
