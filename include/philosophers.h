/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:15 by egache            #+#    #+#             */
/*   Updated: 2025/07/17 19:09:37 by egache           ###   ########.fr       */
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

typedef struct s_monitor
{
	t_philo					*philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						meals;
	int						philo_count;
	bool					all_full;
	pthread_mutex_t			writing;
}							t_monitor;

typedef struct s_philo
{
	pthread_t				thread;
	t_monitor				monitor;
	int						fork_id;
	int						starving;
	bool					alive;
	int						*forks_handled[2];
	bool					full;
	struct s_philo			*next;
}							t_philo;

// philosophers.c
void						init_struct(t_monitor *monitor, t_philo *philo);

// tfbil.c
int							ft_atoi(const char *str);
void						ft_bzero(void *s, size_t n);
void						*ft_calloc(size_t nitems, size_t size);
void						*ft_memset(void *str, int c, size_t n);

// init_philo.c
int							init_philo(t_monitor *monitor, t_philo *philo);
t_philo						*create_philo(int i);
void						add_philo_back(t_philo **philo, t_philo *new);
void						init_thread(t_philo **philo);

// debug.c
void						print_philo(t_philo **philo);
