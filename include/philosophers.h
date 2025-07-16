/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:15 by egache            #+#    #+#             */
/*   Updated: 2025/07/16 17:45:06 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_monitor	t_monitor;
typedef struct s_philo		t_philo;

typedef struct s_philo
{
	pthread_t				thread;
	t_monitor				*monitor;
	int						fork_id;
	int						starving;
	bool					alive;
	int						*forks_handled[2];
	bool					full;
	struct s_philo			*next;
}							t_philo;

typedef struct s_monitor
{
	t_philo					*philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						meals;
	int						philo_count;
	bool					all_full;
}							t_monitor;

// philosophers.c

// tfbil.c

int							ft_atoi(const char *str);
void						ft_bzero(void *s, size_t n);
void						*ft_calloc(size_t nitems, size_t size);
void						*ft_memset(void *str, int c, size_t n);
