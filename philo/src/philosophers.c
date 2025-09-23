/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:42 by egache            #+#    #+#             */
/*   Updated: 2025/09/23 15:43:11 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	sleep_if_tteat_superior_ttsleep(t_monitor *monitor)
{
	if (monitor->philo_count % 2 == 1
		&& (monitor->time_to_die - monitor->time_to_eat)
		> (monitor->time_to_eat + monitor->time_to_sleep))
		ft_usleep(monitor, monitor->time_to_eat);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)(arg);
	pthread_mutex_lock(&philo->monitor->start);
	pthread_mutex_unlock(&philo->monitor->start);
	if (philo->fork_id % 2 == 1)
		usleep(philo->monitor->time_to_eat * 10);
	if (philo->monitor->thread_created < philo->monitor->philo_count)
		return (NULL);
	pthread_mutex_lock(&philo->monitor->last_meal);
	philo->last_meal = ft_time(philo->monitor);
	pthread_mutex_unlock(&philo->monitor->last_meal);
	while (is_sim_running(philo->monitor))
	{
		if (philo_forks(philo, philo->monitor) == 1)
			break ;
		if (philo_eating(philo, philo->monitor) == 1)
			break ;
		if (philo_sleeping(philo, philo->monitor) == 1)
			break ;
		if (philo_thinking(philo, philo->monitor) == 1)
			break ;
		sleep_if_tteat_superior_ttsleep(philo->monitor);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_monitor	*monitor;

	if (argc < 5 || argc > 6)
		return (1);
	philo = NULL;
	monitor = ft_calloc(1, sizeof(t_monitor));
	if (!monitor)
	{
		printf("Error\n");
		return (1);
	}
	if (init_data(monitor, argc, argv))
	{
		free(monitor);
		printf("Error\n");
		return (1);
	}
	if (ft_initialisation(&monitor, &philo))
	{
		free_return(&philo, monitor, EXIT_FAILURE);
		return (1);
	}
	free_return(&philo, monitor, EXIT_SUCCESS);
	return (0);
}
