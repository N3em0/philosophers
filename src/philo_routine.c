/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:27:09 by egache            #+#    #+#             */
/*   Updated: 2025/08/08 21:00:57 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_logs(t_monitor *monitor, t_philo *philo, int philo_id, char *log)
{
	(void)philo;
	pthread_mutex_lock(&monitor->death_check);
	pthread_mutex_lock(&monitor->is_full);
	if (monitor->alive == true && monitor->all_full == false)
	{
		pthread_mutex_unlock(&monitor->is_full);
		pthread_mutex_unlock(&monitor->death_check);
		pthread_mutex_lock(&monitor->writing);
		printf(log, (timetime(monitor) - monitor->start_time), philo_id);
		pthread_mutex_unlock(&monitor->writing);
		return (0);
	}
	pthread_mutex_unlock(&monitor->is_full);
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
		pthread_mutex_lock(&monitor->is_full);
		if (monitor->alive == false || monitor->all_full == true)
		{
			pthread_mutex_unlock(&monitor->is_full);
			pthread_mutex_unlock(&monitor->death_check);
			return (1);
		}
		pthread_mutex_unlock(&monitor->is_full);
		pthread_mutex_unlock(&monitor->death_check);
		pthread_mutex_lock(&philo->monitor->forks[philo->l_fork - 1]);
		philo->forks_handled[0] = philo->l_fork;
		if (philo_logs(monitor, philo, philo->fork_id, "%ld %d has taken a fork\n") == 1)
		{
			pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
			return (1);
		}
	}
	if (philo->next->fork_id != philo->fork_id)
	{
		pthread_mutex_lock(&monitor->death_check);
		pthread_mutex_lock(&monitor->is_full);
		if (monitor->alive == false || monitor->all_full == true)
		{
			pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
			pthread_mutex_unlock(&monitor->is_full);
			pthread_mutex_unlock(&monitor->death_check);
			return (1);
		}
		pthread_mutex_unlock(&monitor->is_full);
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

bool	u_sleep(t_philo *philo, t_monitor *monitor, int duration)
{
	/* FAIRE :
		- Si Duration - elapsed > 100 -> usleep(100)
		- Si Duration - elapsed > 10 && < 100 -> usleep(10)
		- Si Duration - elapsed > 1 && < 10 -> usleep(1)


		Faire 2 boucles distinctes (if nb_meals or not)
	*/

	int	elapsed;

	(void)philo;
	elapsed = 0;
	while (elapsed < duration)
	{
		pthread_mutex_lock(&monitor->death_check);
		pthread_mutex_lock(&monitor->is_full);
		if (monitor->alive == false || monitor->all_full == true)
		{
			pthread_mutex_unlock(&monitor->is_full);
			pthread_mutex_unlock(&monitor->death_check);
			return (false);
		}
		pthread_mutex_unlock(&monitor->death_check);
		pthread_mutex_unlock(&monitor->is_full);
		usleep(duration / 10);
		elapsed += (duration / 10);
		//printf("duration : %d\n", duration / 1000);
		//printf("elapsed : %d\n", elapsed);
	}
	return (true);
}

int	philo_eating(t_philo *philo, t_monitor *monitor)
{
	if (philo->has_forks)
	{
		if (philo_logs(monitor, philo, philo->fork_id, "%ld %d is eating\n"))
		{
			pthread_mutex_unlock(&philo->monitor->forks[philo->l_fork - 1]);
			pthread_mutex_unlock(&philo->monitor->forks[philo->r_fork - 1]);
			return (1);
		}
		// faire une fonction
		if (monitor->must_do == true)
		{
			pthread_mutex_lock(&philo->monitor->meals_count);
			if (philo->meals_count < monitor->meals_needed)
				philo->meals_count++;
			else
			{
				pthread_mutex_lock(&monitor->is_full);
				philo->full = true;
				pthread_mutex_unlock(&monitor->is_full);
			}
			pthread_mutex_unlock(&philo->monitor->meals_count);
		}
		// pour tout ca
		pthread_mutex_lock(&philo->monitor->last_meal);
		philo->last_meal = timetime(monitor);
		pthread_mutex_unlock(&philo->monitor->last_meal);
		if (u_sleep(philo, monitor, monitor->time_to_eat * 1000) == false)
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

int	philo_sleeping(t_philo *philo, t_monitor *monitor)
{
	if (philo_logs(monitor, philo, philo->fork_id, "%ld %d is sleeping\n") == 1)
		return (1);
	if (u_sleep(philo, monitor, monitor->time_to_sleep * 1000) == false)
		return (1);
	// usleep(monitor->time_to_sleep * 1000);
	return (0);
}

int	philo_thinking(t_philo *philo, t_monitor *monitor)
{
	if (philo_logs(monitor, philo, philo->fork_id, "%ld %d is thinking\n") == 1)
		return (1);
	usleep(10);
	return (0);
}
