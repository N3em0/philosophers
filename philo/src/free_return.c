/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_return.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teatime <teatime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:08:13 by egache            #+#    #+#             */
/*   Updated: 2025/09/01 23:15:24 by teatime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int join_thread(t_philo **philo)
{
	t_philo *current;
	int i;

	i = 1;
	current = *philo;
	while (current->next != NULL && current->next != *philo && i < (*philo)->monitor->thread_created)
	{
		pthread_join(current->thread, NULL);
		i++;
		current = current->next;
	}
	pthread_join(current->thread, NULL);
	return (0);
}

static void free_list(t_philo **philo)
{
	t_philo *current;
	t_philo *next;

	if (!*philo)
		return;
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

void destroy_mutex(t_monitor *monitor)
{
	int i;

	if (monitor->mutex_are_init == true)
	{
		pthread_mutex_destroy(&monitor->start);
		pthread_mutex_destroy(&monitor->time);
		pthread_mutex_destroy(&monitor->writing);
		pthread_mutex_destroy(&monitor->death_check);
		pthread_mutex_destroy(&monitor->full_check);
		pthread_mutex_destroy(&monitor->meals_count);
		pthread_mutex_destroy(&monitor->last_meal);
		i = 0;
		while (i < monitor->philo_count)
		{
			pthread_mutex_destroy(&monitor->forks[i]);
			pthread_mutex_destroy(&monitor->forks_taken[i]);
			i++;
		}
	}
}

void free_return(t_philo **philo, t_monitor *monitor, int state)
{
	join_thread(philo);
	destroy_mutex(monitor);
	free_list(philo);
	if (monitor)
	{
		free(monitor->fork_taken);
		free(monitor->forks);
		free(monitor);
		monitor = NULL;
	}
	if (state)
		printf("Error\n");
	return;
}
