/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:42 by egache            #+#    #+#             */
/*   Updated: 2025/07/17 20:06:33 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)(arg);
	printf("caca\n");
	//pthread_mutex_lock(&philo->monitor.writing);
	printf("salut je suis %d\n", philo->fork_id);
	//pthread_mutex_unlock(&philo->monitor.writing);
	return (NULL);
	//thread_exit("bobo\n");

}

void	init_thread(t_philo **philo)
{
	t_philo	*current;

	current = *philo;
	//printf("philo simple address in init_thread : %p\n", *philo);
	while (current->next != *philo && current->next != NULL)
	{
		//printf("current->fork_id : %d\n", current->fork_id);
		pthread_create(&current->thread, NULL, philo_routine,
			&current->fork_id);
		current = current->next;
	}
	//printf("current->fork_id : %d\n", current->fork_id);
	pthread_create(&current->thread, NULL, philo_routine, &current->fork_id);
}

void	init_struct(t_monitor *monitor, t_philo *philo)
{
	ft_bzero(monitor, sizeof(t_monitor));
	(void)philo;
	// ft_bzero(philo, sizeof(t_philo));
}

int	main(int argc, char **argv)
{
	t_philo		*philo;

	philo = ft_calloc(1, sizeof(t_philo));
	//printf("\n--------\nphilo simple address in main : %p\n--------\n", philo);
	// init_struct(&philo->monitor, philo);
	if (argc < 5 || argc > 6)
		return (1);
	philo->monitor.philo_count = ft_atoi(argv[1]);
	philo->monitor.time_to_die = ft_atoi(argv[2]);
	philo->monitor.time_to_eat = ft_atoi(argv[3]);
	philo->monitor.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->monitor.meals = ft_atoi(argv[5]);
	init_philo(&philo->monitor, philo);
}
