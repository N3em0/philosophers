/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:42 by egache            #+#    #+#             */
/*   Updated: 2025/08/08 19:11:56 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
1 millisecond = 1000 microseconds

time in arguments are in milliseconds. So 400ms = 400 x 1000
*/

long	timetime(t_monitor *monitor)
{
	long	set_time;

	gettimeofday(&monitor->tv, NULL);
	set_time = (monitor->tv.tv_sec * 1000) + (monitor->tv.tv_usec / 1000);
	return (set_time);
}

long	time_to_x(t_monitor *monitor, int x)
{
	gettimeofday(&monitor->tv, NULL);
	return ((monitor->tv.tv_sec * 1000) + (monitor->tv.tv_usec / 1000) - x);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)(arg);
	pthread_mutex_lock(&philo->monitor->start);
	pthread_mutex_unlock(&philo->monitor->start);
	pthread_mutex_lock(&philo->monitor->last_meal);
	philo->last_meal = timetime(philo->monitor);
	pthread_mutex_unlock(&philo->monitor->last_meal);
	while (1)
	{
		if (philo_forks(philo, philo->monitor) == 1)
			break ;
		if (philo_eating(philo, philo->monitor) == 1)
			break ;
		if (philo_sleeping(philo, philo->monitor) == 1)
			break ;
		if (philo_thinking(philo, philo->monitor) == 1)
			break ;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_monitor	*monitor;

	philo = NULL;
	monitor = ft_calloc(1, sizeof(t_monitor));
	if (argc < 5 || argc > 6)
		return (1);
	monitor->philo_count = ft_atoi(argv[1]);
	monitor->time_to_die = ft_atoi(argv[2]);
	monitor->time_to_eat = ft_atoi(argv[3]);
	monitor->time_to_sleep = ft_atoi(argv[4]);
	monitor->start_time = timetime(monitor);
	monitor->must_do = false;
	if (argc == 6)
	{
		monitor->must_do = true;
		monitor->meals_needed = ft_atoi(argv[5]);
	}
	ft_initialisation(&monitor, &philo);
	return (0);
}
