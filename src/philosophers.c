/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:42 by egache            #+#    #+#             */
/*   Updated: 2025/07/23 19:29:52 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)(arg);
	//pthread_mutex_lock(&philo->monitor->start);
	//pthread_mutex_unlock(&philo->monitor->start);
	pthread_mutex_lock(&philo->monitor->writing);
	printf("salut je suis le philo %d\n", philo->fork_id);
	pthread_mutex_unlock(&philo->monitor->writing);
	return (NULL);

}

void	init_thread(t_philo **philo)
{
	t_philo	*current;

	current = *philo;
	// printf("\n-------------------------------------\ninit_thread\n-------------------------------------\n\n");
	// printf("philo->monitor adrs                : %p\n\n", (*philo)->monitor);
	//pthread_mutex_lock(&(*philo)->monitor->start);
	while (current->next != NULL && current->next != *philo)
	{
		// printf("current->fork_id : %d / ", current->fork_id);
		// printf("current->monitor->writing adrs : %p / ", &current->monitor->writing);
		// printf("current->monitor adrs : %p\n\n", current->monitor);
		pthread_create(&current->thread, NULL, philo_routine,
			current);
		pthread_join(current->thread, NULL);
		current = current->next;
	}
	// printf("current->fork_id : %d / ", current->fork_id);
	// printf("current->monitor->writing adrs : %p / ", &current->monitor->writing);
	// printf("current->monitor adrs : %p\n\n", current->monitor);
	pthread_create(&current->thread, NULL, philo_routine, current);
	pthread_join(current->thread, NULL);
	//pthread_mutex_unlock(&(*philo)->monitor->start);

}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_monitor *monitor;

	philo = NULL;
	monitor = ft_calloc(1, sizeof(t_monitor));
	if (argc < 5 || argc > 6)
		return (1);
	monitor->philo_count = ft_atoi(argv[1]);
	monitor->time_to_die = ft_atoi(argv[2]);
	monitor->time_to_eat = ft_atoi(argv[3]);
	monitor->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		monitor->meals = ft_atoi(argv[5]);
	init_philo(&monitor, &philo);
	usleep(50000);
}
