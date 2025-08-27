/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 23:10:13 by egache            #+#    #+#             */
/*   Updated: 2025/08/27 14:12:51 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_initialisation(t_monitor **monitor, t_philo **philo)
{
	(*monitor)->alive = true;
	(*monitor)->all_full = false;
	if (init_mutex(*monitor))
		return (1);
	(*monitor)->start_time = ft_time(*monitor);
	if (init_philo(monitor, philo))
		return (1);
	if (init_thread(philo))
		return (1);
	return (0);
}

int	init_data(t_monitor *monitor, int argc, char **argv)
{
	monitor->philo_count = ft_atoi(argv[1]);
	monitor->time_to_die = ft_atoi(argv[2]);
	monitor->time_to_eat = ft_atoi(argv[3]);
	monitor->time_to_sleep = ft_atoi(argv[4]);
	monitor->meal_countdown = false;
	monitor->mutex_are_init = false;
	if (argc == 6)
	{
		monitor->meal_countdown = true;
		monitor->meals_needed = ft_atoi(argv[5]);
		if (monitor->meals_needed <= 0)
			return (1);
	}
	if (monitor->philo_count <= 0 || monitor->philo_count > 200
		|| monitor->time_to_die <= 0 || monitor->time_to_eat <= 0
		|| monitor->time_to_sleep <= 0)
		return (1);
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
		new->last_meal = new->monitor->start_time;
		new->meals_count = 0;
		add_philo_back(philo, new);
		i++;
	}
	return (0);
}

int	init_mutex(t_monitor *monitor)
{
	int	i;

	i = 0;
	monitor->forks = malloc(monitor->philo_count * sizeof(pthread_mutex_t));
	if (!monitor->forks)
		return (1);
	pthread_mutex_init(&monitor->start, NULL);
	pthread_mutex_init(&monitor->time, NULL);
	pthread_mutex_init(&monitor->elapsed, NULL);
	pthread_mutex_init(&monitor->writing, NULL);
	pthread_mutex_init(&monitor->death_check, NULL);
	pthread_mutex_init(&monitor->full_check, NULL);
	pthread_mutex_init(&monitor->meals_count, NULL);
	pthread_mutex_init(&monitor->last_meal, NULL);
	while (i < monitor->philo_count)
	{
		pthread_mutex_init(&monitor->forks[i], NULL);
		i++;
	}
	monitor->mutex_are_init = true;
	return (0);
}

int	init_thread(t_philo **philo)
{
	t_philo	*current;

	current = *philo;
	pthread_mutex_lock(&(*philo)->monitor->start);
	while (current->next != NULL && current->next != *philo)
	{
		if (pthread_create(&current->thread, NULL, philo_routine, current))
		{
			pthread_mutex_unlock(&(*philo)->monitor->start);
			return (1);
		}
		current = current->next;
	}
	// if (pthread_create(&current->thread, NULL, philo_routine, current))
	// {
		pthread_mutex_unlock(&(*philo)->monitor->start);
		return (1);
	// }
	pthread_mutex_unlock(&(*philo)->monitor->start);
	current = *philo;
	if (monitoring(philo, (*philo)->monitor) == 1)
		return (join_thread(philo));
	return (0);
}
