/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:27:40 by egache            #+#    #+#             */
/*   Updated: 2025/07/23 19:17:12 by egache           ###   ########.fr       */
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


/*

proteger pthread -> SI 1 fail : Je quitte tout / ou je fait avec thread en moins (a moi de decider)
utiliser le meme mutex pour creer thread et start routine

*/
