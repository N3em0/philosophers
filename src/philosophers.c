/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:42 by egache            #+#    #+#             */
/*   Updated: 2025/07/31 02:16:14 by egache           ###   ########.fr       */
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
		if (is_alive(philo, philo->monitor) == true)
		{
			if (philo_forks(philo, philo->monitor) == 0)
			{
				philo_eating(philo, philo->monitor);
				philo_sleeping(philo, philo->monitor);
				philo_thinking(philo, philo->monitor);
			}
			else
				return (NULL);
		}
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
	if (argc == 6)
		monitor->meals = ft_atoi(argv[5]);
	ft_initialisation(&monitor, &philo);
}

// void	*philo_routine(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)(arg);
// 	while (1)
// 	{
// 		pthread_mutex_lock(&philo->monitor->last_meal);
// 		philo->last_meal = timetime(philo->monitor);
// 		printf("last_meal de philo %d : %ld\n", philo->fork_id,
// 			philo->last_meal);
// 		pthread_mutex_unlock(&philo->monitor->last_meal);
// 		pthread_mutex_lock(&philo->monitor->own_fork);
// 		pthread_mutex_lock(&philo->monitor->other_fork);
// 		pthread_mutex_lock(&philo->monitor->writing);
// 		gettimeofday(&philo->monitor->tv, NULL);
// 		philo->forks_handled[0] = philo->fork_id;
// 		philo->forks_handled[1] = philo->next->fork_id;
// 		printf("philo %d fork %d et fork %d\n", philo->fork_id,
// 			philo->forks_handled[0], philo->forks_handled[1]);
// 		printf("heure : %ld\n", (philo->monitor->tv.tv_sec * 1000)
// 			+ (philo->monitor->tv.tv_usec / 1000));
// 		usleep(50000);
// 		pthread_mutex_unlock(&philo->monitor->own_fork);
// 		pthread_mutex_unlock(&philo->monitor->other_fork);
// 		pthread_mutex_unlock(&philo->monitor->writing);
// 	}
// 	return (NULL);
// }
