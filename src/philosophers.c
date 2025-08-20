/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:42 by egache            #+#    #+#             */
/*   Updated: 2025/08/20 16:33:56 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)(arg);
	pthread_mutex_lock(&philo->monitor->start);
	pthread_mutex_unlock(&philo->monitor->start);
	pthread_mutex_lock(&philo->monitor->last_meal);
	philo->last_meal = ft_time(philo->monitor);
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
	if (!monitor)
		free_exit(NULL, NULL, EXIT_FAILURE);
	if (argc < 5 || argc > 6)
		free_exit(NULL, NULL, EXIT_FAILURE);
	monitor->philo_count = ft_atoi(argv[1]);
	monitor->time_to_die = ft_atoi(argv[2]);
	monitor->time_to_eat = ft_atoi(argv[3]);
	monitor->time_to_sleep = ft_atoi(argv[4]);
	monitor->meal_countdown = false;
	if (argc == 6)
	{
		monitor->meal_countdown = true;
		monitor->meals_needed = ft_atoi(argv[5]);
	}
	if (monitor->philo_count < 0 || monitor->philo_count >= 200
		|| monitor->time_to_die < 0 || monitor->time_to_eat < 0
		|| monitor->time_to_sleep < 0 || monitor->meals_needed < 0)
		free_exit(NULL, monitor, EXIT_FAILURE);
	ft_initialisation(&monitor, &philo);
	free_exit(&philo, monitor, EXIT_SUCCESS);
}
