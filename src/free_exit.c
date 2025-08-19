/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:08:13 by egache            #+#    #+#             */
/*   Updated: 2025/08/19 15:50:11 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_list(t_philo **philo)
{
	t_philo	*current;
	t_philo	*next;

	current = *philo;
	while (current->next != *philo && current->next != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(current);
	*philo = NULL;
	return ;
}

void	free_exit(t_philo **philo, t_monitor *monitor, int state)
{
	destroy_mutex(monitor);
	free(monitor->forks);
	free(monitor);
	monitor = NULL;
	free_list(philo);
	exit(state);
}

void	destroy_mutex(t_monitor *monitor)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&monitor->writing);
	pthread_mutex_destroy(&monitor->elapsed);
	pthread_mutex_destroy(&monitor->start);
	pthread_mutex_destroy(&monitor->death_check);
	pthread_mutex_destroy(&monitor->meals_count);
	pthread_mutex_destroy(&monitor->full_check);
	pthread_mutex_destroy(&monitor->time);
	while (i < monitor->philo_count)
	{
		pthread_mutex_destroy(&monitor->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&monitor->last_meal);
}
