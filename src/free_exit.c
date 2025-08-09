/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teatime <teatime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:08:13 by egache            #+#    #+#             */
/*   Updated: 2025/08/09 16:58:09 by teatime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void free_list(t_philo **philo)
{
	t_philo *current;
	t_philo *next;

	current = *philo;
	while (current->next != *philo && current->next != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(current);
	*philo = NULL;
	return;
}

void free_exit(t_philo **philo, t_monitor *monitor, int state)
{
	destroy_mutex(*philo, monitor);
	free(monitor->forks);
	free(monitor);
	monitor = NULL;
	free_list(philo);
	exit(state);
}

void destroy_mutex(t_philo *philo, t_monitor *monitor)
{
	int i;

	i = 0;
	(void)philo;
	pthread_mutex_destroy(&monitor->writing);
	pthread_mutex_destroy(&monitor->start);
	pthread_mutex_destroy(&monitor->death_check);
	pthread_mutex_destroy(&monitor->meals_count);
	pthread_mutex_destroy(&monitor->is_full);
	pthread_mutex_destroy(&monitor->time);
	while (i < monitor->philo_count)
	{
		pthread_mutex_destroy(&monitor->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&monitor->last_meal);
}
