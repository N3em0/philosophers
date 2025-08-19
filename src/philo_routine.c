/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:27:09 by egache            #+#    #+#             */
/*   Updated: 2025/08/19 15:53:59 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_logs(t_philo *philo, t_monitor *monitor, int philo_id, char *log)
{
	(void)philo;
	pthread_mutex_lock(&monitor->death_check);
	pthread_mutex_lock(&monitor->full_check);
	if (monitor->alive == false || monitor->all_full == true)
	{
		pthread_mutex_unlock(&monitor->full_check);
		pthread_mutex_unlock(&monitor->death_check);
		return (1);
	}
	pthread_mutex_unlock(&monitor->full_check);
	pthread_mutex_unlock(&monitor->death_check);
	if (monitor->alive == true && monitor->all_full == false)
	{
		pthread_mutex_lock(&monitor->writing);
		printf(log, (timetime(monitor) - monitor->start_time), philo_id);
		pthread_mutex_unlock(&monitor->writing);
		return (0);
	}
	else
	{
		return (1);
	}
}

int	philo_forks(t_philo *philo, t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->death_check);
	pthread_mutex_lock(&monitor->full_check);
	if (monitor->alive == false || monitor->all_full == true)
	{
		pthread_mutex_unlock(&monitor->full_check);
		pthread_mutex_unlock(&monitor->death_check);
		return (1);
	}
	pthread_mutex_unlock(&monitor->full_check);
	pthread_mutex_unlock(&monitor->death_check);
	philo->l_fork = philo->fork_id;
	philo->r_fork = philo->next->fork_id;
	if (philo->fork_id % 2 != 0)
	{
		philo->l_fork = philo->next->fork_id;
		philo->r_fork = philo->fork_id;
	}
	if (philo->forks_handled[0] != philo->fork_id)
	{
		pthread_mutex_lock(&philo->monitor->forks[philo->l_fork - 1]);
		philo->forks_handled[0] = philo->l_fork;
		if (monitor->alive == true && monitor->all_full == false)
		{
			if (philo_logs(philo, monitor, philo->fork_id,
					"%ld %d has taken a fork\n") == 1)
			{
				pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
				return (1);
			}
		}
	}
	pthread_mutex_lock(&monitor->death_check);
	pthread_mutex_lock(&monitor->full_check);
	if (monitor->alive == false || monitor->all_full == true)
	{
		pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
		pthread_mutex_unlock(&monitor->full_check);
		pthread_mutex_unlock(&monitor->death_check);
		return (1);
	}
	pthread_mutex_unlock(&monitor->full_check);
	pthread_mutex_unlock(&monitor->death_check);
	if (philo->next->fork_id != philo->fork_id)
	{
		pthread_mutex_lock(&philo->monitor->forks[philo->r_fork - 1]);
		philo->forks_handled[1] = philo->r_fork;
		philo->has_forks = true;
		if (monitor->alive == true && monitor->all_full == false)
		{
			if (philo_logs(philo, monitor, philo->fork_id,
					"%ld %d has taken a fork\n") == 1)
			{
				pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
				pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
				return (1);
			}
		}
		return (0);
	}
	pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
	return (1);
}

bool	ft_usleep(t_monitor *monitor, int duration)
{
	int		elapsed;
	long	start;

	elapsed = 0;
	start = timetime(monitor);
	while ((timetime(monitor) - start) < duration / 1000)
	{
		pthread_mutex_lock(&monitor->death_check);
		pthread_mutex_lock(&monitor->full_check);
		if (monitor->alive == false || monitor->all_full == true)
		{
			pthread_mutex_unlock(&monitor->full_check);
			pthread_mutex_unlock(&monitor->death_check);
			return (false);
		}
		pthread_mutex_unlock(&monitor->death_check);
		pthread_mutex_unlock(&monitor->full_check);
		usleep(100);
	}
	return (true);
}

int	philo_eating(t_philo *philo, t_monitor *monitor)
{
	if (philo->has_forks)
	{
		if (monitor->meal_countdown == true)
		{
			pthread_mutex_lock(&philo->monitor->meals_count);
			if (philo->meals_count < monitor->meals_needed)
				philo->meals_count++;
			else
			{
				pthread_mutex_lock(&monitor->full_check);
				philo->full = true;
				pthread_mutex_unlock(&monitor->full_check);
			}
			pthread_mutex_unlock(&philo->monitor->meals_count);
		}
		if (monitor->alive == true && monitor->all_full == false)
		{
			if (philo_logs(philo, monitor, philo->fork_id,
					"%ld %d is eating\n"))
			{
				pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
				pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
				return (1);
			}
		}
		pthread_mutex_lock(&philo->monitor->last_meal);
		philo->last_meal = timetime(monitor);
		pthread_mutex_unlock(&philo->monitor->last_meal);
		if (ft_usleep(monitor, monitor->time_to_eat * 1000) == false)
		{
			pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
			pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
			return (1);
		}
		philo->has_forks = false;
		philo->forks_handled[0] = -1;
		philo->forks_handled[1] = -1;
		pthread_mutex_lock(&monitor->death_check);
		pthread_mutex_lock(&monitor->full_check);
		if (monitor->alive == false || monitor->all_full == true)
		{
			pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
			pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
			pthread_mutex_unlock(&monitor->full_check);
			pthread_mutex_unlock(&monitor->death_check);
			return (1);
		}
		pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
		pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
		pthread_mutex_unlock(&monitor->full_check);
		pthread_mutex_unlock(&monitor->death_check);
	}
	return (0);
}

int	philo_sleeping(t_philo *philo, t_monitor *monitor)
{
	if (are_all_full(&philo, monitor) == true || monitor->alive == false)
		return (1);
	if (monitor->alive == true && monitor->all_full == false)
	{
		if (philo_logs(philo, monitor, philo->fork_id,
				"%ld %d is sleeping\n") == 1)
			return (1);
	}
	if (monitor->alive == true && monitor->all_full == false)
	{
		if (ft_usleep(monitor, monitor->time_to_sleep * 1000) == false)
			return (1);
	}
	return (0);
}

int	philo_thinking(t_philo *philo, t_monitor *monitor)
{
	if (are_all_full(&philo, monitor) == true || monitor->alive == false)
		return (1);
	if (monitor->alive == true && monitor->all_full == false)
	{
		if (philo_logs(philo, monitor, philo->fork_id,
				"%ld %d is thinking\n") == 1)
			return (1);
	}
	usleep(1);
	return (0);
}
