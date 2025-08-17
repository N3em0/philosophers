/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teatime <teatime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:27:09 by egache            #+#    #+#             */
/*   Updated: 2025/08/17 23:31:39 by teatime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int philo_logs(t_monitor *monitor, int philo_id, char *log)
{
	pthread_mutex_lock(&monitor->death_check);
	pthread_mutex_lock(&monitor->full_check);
	if (monitor->alive == true && monitor->all_full == false)
	{
		pthread_mutex_unlock(&monitor->full_check);
		pthread_mutex_unlock(&monitor->death_check);
		pthread_mutex_lock(&monitor->writing);
		printf(log, (timetime(monitor) - monitor->start_time), philo_id);
		pthread_mutex_unlock(&monitor->writing);
		return (0);
	}
	pthread_mutex_unlock(&monitor->full_check);
	pthread_mutex_unlock(&monitor->death_check);
	return (1);
}

int philo_forks(t_philo *philo, t_monitor *monitor)
{
	philo->l_fork = philo->fork_id;
	philo->r_fork = philo->next->fork_id;
	if (philo->fork_id % 2 != 0)
	{
		philo->l_fork = philo->next->fork_id;
		philo->r_fork = philo->fork_id;
	}
	if (philo->forks_handled[0] != philo->l_fork)
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
		pthread_mutex_lock(&philo->monitor->forks[philo->l_fork - 1]);
		philo->forks_handled[0] = philo->l_fork;
		if (philo_logs(monitor, philo->fork_id, "%ld %d has taken a fork\n") == 1)
		{
			pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
			return (1);
		}
	}
	if (philo->next->fork_id != philo->fork_id)
	{
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
		pthread_mutex_lock(&philo->monitor->forks[philo->r_fork - 1]);
		philo->forks_handled[1] = philo->r_fork;
		philo->has_forks = true;
		if (philo_logs(monitor, philo->fork_id, "%ld %d has taken a fork\n") == 1)
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

// bool ft_usleep(t_monitor *monitor, int duration)
// {
// 	int elapsed;
// 	// int sleep_time;

// 	elapsed = 0;
// 	// sleep_time = 0;
// 	while (elapsed < duration)
// 	{
// 		pthread_mutex_lock(&monitor->death_check);
// 		pthread_mutex_lock(&monitor->full_check);
// 		if (monitor->alive == false || monitor->all_full == true)
// 		{
// 			pthread_mutex_unlock(&monitor->full_check);
// 			pthread_mutex_unlock(&monitor->death_check);
// 			return (false);
// 		}
// 		pthread_mutex_unlock(&monitor->death_check);
// 		pthread_mutex_unlock(&monitor->full_check);
// 		// if (duration - elapsed >= 100)
// 		// 	sleep_time = 100;
// 		// else if ((duration - elapsed) >= 10)
// 		// 	sleep_time = 10;
// 		// else if ((duration - elapsed) >= 1)
// 		// 	sleep_time = 1;
// 		// usleep(sleep_time);
// 		// elapsed += (sleep_time);
// 		usleep(duration / 10);
// 		elapsed += duration / 10;
// 	}
// 	return (true);
// }

bool ft_usleep(t_monitor *monitor, int duration)
{
	int slept = 0;
	int chunk = 5000;
	int sleep_time;
	int rest;
	while (slept < duration)
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
		rest = duration - slept;
		if (rest < chunk)
			sleep_time = rest;
		else
			sleep_time = chunk;

		usleep(sleep_time);
		slept += sleep_time;
	}
	return true;
}

int philo_eating(t_philo *philo, t_monitor *monitor)
{
	if (philo->has_forks)
	{
		if (philo_logs(monitor, philo->fork_id, "%ld %d is eating\n"))
		{
			pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
			pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
			return (1);
		}
		// faire une fonction
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
		// pour tout ca
		pthread_mutex_lock(&philo->monitor->last_meal);
		philo->last_meal = timetime(monitor);
		pthread_mutex_unlock(&philo->monitor->last_meal);
		if (ft_usleep(monitor, monitor->time_to_eat * 1000) == false)
		{
			pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
			pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
			return (1);
		}
		// usleep(monitor->time_to_eat * 1000);
		philo->has_forks = false;
		philo->forks_handled[0] = -1;
		philo->forks_handled[1] = -1;
		pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
		pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
	}
	return (0);
}

int philo_sleeping(t_philo *philo, t_monitor *monitor)
{
	if (philo_logs(monitor, philo->fork_id, "%ld %d is sleeping\n") == 1)
		return (1);
	if (ft_usleep(monitor, monitor->time_to_sleep * 1000) == false)
		return (1);
	// usleep(monitor->time_to_sleep * 1000);
	return (0);
}

int philo_thinking(t_philo *philo, t_monitor *monitor)
{
	if (philo_logs(monitor, philo->fork_id, "%ld %d is thinking\n") == 1)
		return (1);
	usleep(1);
	return (0);
}
