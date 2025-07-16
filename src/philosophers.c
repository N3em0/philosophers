/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:42 by egache            #+#    #+#             */
/*   Updated: 2025/07/16 18:38:41 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_philo(t_philo **philo)
{
	t_philo	*current;

	current = (*philo);
	printf("philo first node address print_philo : %p\n", *philo);
	printf("---Philo[%d]---\n", (*philo)->fork_id);
	while (current->next != *philo && current->next != NULL)
	{
		current = current->next;
		printf("---Philo[%d]---\n", current->fork_id);
	}
}

t_philo	*create_philo(int i)
{
	t_philo			*new;
	struct timeval	tv;

	new = ft_calloc(1, sizeof(t_philo));
	if (!new)
		return (NULL);
	new->fork_id = i + 1;
	printf("fork_id : %d\n", new->fork_id);
	new->alive = true;
	new->starving = gettimeofday(&tv, NULL);
	return (new);
}

void	add_philo_back(t_philo **philo, t_philo *new)
{
	t_philo	*tmp;

	if ((*philo)->next == NULL)
	{
		printf("hihi\n");
		*philo = new;
		(*philo)->next = *philo;
		return ;
	}
	printf("philo first node address add_philo_back : %p\n", *philo);
	tmp = *philo;
	while (tmp->next != *philo && tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->next = *philo;
}

int	init_philo(t_monitor *monitor, t_philo *philo)
{
	int		i;
	t_philo	*new;

	i = 0;
	while (i < monitor->philo_count)
	{
		new = create_philo(i);
		printf("fork_id in init_philo : %d\n", new->fork_id);
		if (!new)
			return (1);
		add_philo_back(&philo, new);
		i++;
	}
	print_philo(&philo);
	return (0);
}

void	init_struct(t_monitor *monitor, t_philo *philo)
{
	ft_bzero(monitor, sizeof(t_monitor));
	ft_bzero(philo, sizeof(t_philo));
}

int	main(int argc, char **argv)
{
	t_monitor	monitor;
	t_philo		philo;

	init_struct(&monitor, &philo);
	if (argc < 5 || argc > 6)
		return (1);
	monitor.philo_count = ft_atoi(argv[1]);
	monitor.time_to_die = ft_atoi(argv[2]);
	monitor.time_to_eat = ft_atoi(argv[3]);
	monitor.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		monitor.meals = ft_atoi(argv[5]);
	init_philo(&monitor, &philo);
}
