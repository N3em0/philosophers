/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:15 by egache            #+#    #+#             */
/*   Updated: 2025/07/31 01:54:24 by egache           ###   ########.fr       */
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
	struct timeval			tv;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						meals;
	int						philo_count;
	long					set_time;
	long					start_time;
	bool					all_full;
	bool					alive;
	pthread_mutex_t			writing;
	pthread_mutex_t			start;
	pthread_mutex_t			*forks;
	pthread_mutex_t			last_meal;
	pthread_mutex_t			death_check;
}							t_monitor;

typedef struct s_philo
{
	pthread_t				thread;
	t_monitor				*monitor;
	int						fork_id;
	int						l_fork;
	int						r_fork;
	long					last_meal;
	int						forks_handled[2];
	bool					has_forks;
	bool					full;
	struct s_philo			*next;
}							t_philo;

// philosophers.c
void						*philo_routine(void *arg);

// initialisation.c
int							ft_initialisation(t_monitor **monitor,
								t_philo **philo);
int							init_philo(t_monitor **monitor, t_philo **philo);
int							init_mutex(t_monitor *monitor);
int							init_thread(t_philo **philo);

// philo_routine.c
int							philo_forks(t_philo *philo, t_monitor *monitor);
int							philo_eating(t_philo *philo, t_monitor *monitor);
int							philo_sleeping(t_philo *philo, t_monitor *monitor);
int							philo_thinking(t_philo *philo, t_monitor *monitor);

// timetime.c
long						time_to_x(t_monitor *monitor, int x);
long						timetime(t_monitor *monitor);

// monitoring.c
int							monitoring(t_philo **philo, t_monitor *monitor);
bool						is_alive(t_philo *philo, t_monitor *monitor);

// tfbil.c
int							ft_atoi(const char *str);
void						ft_bzero(void *s, size_t n);
void						*ft_calloc(size_t nitems, size_t size);
void						*ft_memset(void *str, int c, size_t n);

// init_philo.c
t_philo						*create_philo(int i);
void						add_philo_back(t_philo **philo, t_philo *new);

// debug.c
void						print_philo(t_philo **philo);
