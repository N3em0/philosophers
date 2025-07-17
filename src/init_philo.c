/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:31:18 by egache            #+#    #+#             */
/*   Updated: 2025/07/17 19:33:07 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philo(t_monitor *monitor, t_philo *philo)
{
	int		i;
	t_philo	*new;

	i = 0;
	while (i < monitor->philo_count)
	{
		new = create_philo(i);
		//printf("\n--------\nfork_id in init_philo : %d\n----------\n", new->fork_id);
		if (!new)
			return (1);
		add_philo_back(&philo, new);
		i++;
	}
	pthread_mutex_init(&monitor->writing, NULL);
	//printf("\n--------\nphilo->monitor->writing address : %p\n--------\n", &philo->monitor.writing);
	print_philo(&philo);
	init_thread(&philo);
	return (0);
}

t_philo	*create_philo(int i)
{
	t_philo			*new;
	struct timeval	tv;

	new = ft_calloc(1, sizeof(t_philo));
	if (!new)
		return (NULL);
	new->fork_id = i + 1;
	new->alive = true;
	new->starving = gettimeofday(&tv, NULL);
	return (new);
}

void	add_philo_back(t_philo **philo, t_philo *new)
{
	t_philo	*tmp;

	if ((*philo)->next == NULL)
	{
		*philo = new;
		(*philo)->next = *philo;
		//printf("\n--------\nphilo first node address add_philo_back : %p\n--------\n", *philo);
		return ;
	}
	//printf("\n--------\nphilo first node address add_philo_back : %p\n--------\n", *philo);
	tmp = *philo;
	while (tmp->next != *philo && tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->next = *philo;
}
