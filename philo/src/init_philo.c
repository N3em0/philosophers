/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teatime <teatime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:31:18 by egache            #+#    #+#             */
/*   Updated: 2025/09/02 00:08:50 by teatime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo *create_philo(int i, t_monitor **monitor)
{
	t_philo *new;

	new = ft_calloc(1, sizeof(t_philo));
	if (!new)
		return (NULL);
	new->fork_id = i + 1;
	new->full = false;
	new->has_forks = false;
	if (new->fork_id == (*monitor)->philo_count && new->fork_id % 2 != 0)
	{
		new->l_fork = 1;
		new->r_fork = new->fork_id;
	}
	else if (new->fork_id == (*monitor)->philo_count && new->fork_id % 2 == 0)
	{
		new->l_fork = new->fork_id;
		new->r_fork = 1;
	}
	else if (new->fork_id % 2 != 0)
	{
		new->l_fork = new->fork_id + 1;
		new->r_fork = new->fork_id;
	}
	else
	{
		new->l_fork = new->fork_id;
		new->r_fork = new->fork_id + 1;
	}
	// printf("philo count : %d\n", (*monitor)->philo_count);
	// printf("fork id : %d || l_fork : %d\n", new->fork_id, new->l_fork);
	// printf("fork id : %d || r_fork : %d\n", new->fork_id, new->r_fork);
	return (new);
}

void add_philo_back(t_philo **philo, t_philo *new)
{
	t_philo *tmp;

	if (*philo == NULL || (*philo)->next == NULL)
	{
		*philo = new;
		(*philo)->next = *philo;
		(*philo)->next->monitor = (*philo)->monitor;
		return;
	}
	tmp = *philo;
	while (tmp->next != *philo && tmp->next != NULL)
	{
		(*philo)->next->monitor = (*philo)->monitor;
		tmp = tmp->next;
	}
	tmp->next = new;
	new->next = *philo;
}
