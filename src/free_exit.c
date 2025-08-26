/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:08:13 by egache            #+#    #+#             */
/*   Updated: 2025/08/26 18:17:35 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	join_thread(t_philo **philo)
{
	t_philo	*current;

	current = *philo;
	while (current->next != NULL && current->next != *philo)
	{
		if (pthread_join(current->thread, NULL))
			return (1);
		current = current->next;
	}
	if (pthread_join(current->thread, NULL))
		return (1);
	return (0);
}

static void	free_list(t_philo **philo)
{
	t_philo	*current;
	t_philo	*next;

	if (!philo)
		return ;
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

void	destroy_mutex(t_monitor *monitor)
{
	int	i;

	pthread_mutex_destroy(&monitor->writing);
	pthread_mutex_destroy(&monitor->elapsed);
	pthread_mutex_destroy(&monitor->start);
	pthread_mutex_destroy(&monitor->death_check);
	pthread_mutex_destroy(&monitor->meals_count);
	pthread_mutex_destroy(&monitor->full_check);
	pthread_mutex_destroy(&monitor->time);
	i = 0;
	while (i < monitor->philo_count)
	{
		pthread_mutex_destroy(&monitor->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&monitor->last_meal);
}

void	free_exit(t_philo **philo, t_monitor *monitor, int state)
{
	destroy_mutex(monitor);
	free_list(philo);
	if (monitor)
	{
		free(monitor->forks);
		free(monitor);
		monitor = NULL;
	}
	if (state)
		printf("Error\n");
	return ;
}
