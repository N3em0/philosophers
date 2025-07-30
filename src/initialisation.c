/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 23:10:13 by egache            #+#    #+#             */
/*   Updated: 2025/07/30 00:44:36 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_initialisation(t_monitor **monitor, t_philo **philo)
{
	(*monitor)->alive = true;
	(*monitor)->all_full = false;
	init_philo(monitor, philo);
	init_mutex(*monitor);
	init_thread(philo);
	return (0);
}

int	init_philo(t_monitor **monitor, t_philo **philo)
{
	int		i;
	t_philo	*new;

	i = 0;
	*philo = NULL;
	while (i < (*monitor)->philo_count)
	{
		new = create_philo(i);
		if (!new)
			return (1);
		new->monitor = (*monitor);
		add_philo_back(philo, new);
		i++;
	}
	return (0);
}

int	init_mutex(t_monitor *monitor)
{
	int	i;

	i = 0;
	pthread_mutex_init(&monitor->writing, NULL);
	pthread_mutex_init(&monitor->start, NULL);
	printf("philo_count : %d\n", monitor->philo_count);
	monitor->forks = malloc(monitor->philo_count * sizeof(pthread_mutex_t));
	while (i < monitor->philo_count)
	{
		pthread_mutex_init(&monitor->forks[i], NULL);
		i++;
	}
	// pthread_mutex_init(&monitor->own_fork, NULL);
	// pthread_mutex_init(&monitor->other_fork, NULL);
	pthread_mutex_init(&monitor->last_meal, NULL);
	return (0);
}

int	init_thread(t_philo **philo)
{
	t_philo	*current;

	current = *philo;
	while (current->next != NULL && current->next != *philo)
	{
		pthread_create(&current->thread, NULL, philo_routine, current);
		current = current->next;
	}
	pthread_create(&current->thread, NULL, philo_routine, current);
	current = *philo;
	while (current->next != NULL && current->next != *philo)
	{
		pthread_join(current->thread, NULL);
		current = current->next;
	}
	pthread_join(current->thread, NULL);
	return (0);
}
