/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:31:18 by egache            #+#    #+#             */
/*   Updated: 2025/08/20 14:42:59 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_philo(int i)
{
	t_philo			*new;

	new = ft_calloc(1, sizeof(t_philo));
	if (!new)
		return (NULL);
	new->fork_id = i + 1;
	new->full = false;
	new->has_forks = false;
	return (new);
}

void	add_philo_back(t_philo **philo, t_philo *new)
{
	t_philo	*tmp;

	if (*philo == NULL || (*philo)->next == NULL)
	{
		*philo = new;
		(*philo)->next = *philo;
		(*philo)->next->monitor = (*philo)->monitor;
		return ;
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
