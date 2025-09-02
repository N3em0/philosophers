/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:56:15 by egache            #+#    #+#             */
/*   Updated: 2025/09/02 20:07:13 by egache           ###   ########.fr       */
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
	int						meals_needed;
	bool					meal_countdown;
	int						philo_count;
	int						thread_created;
	long					set_time;
	long					start_time;
	bool					*fork_taken;
	bool					sim_running;
	pthread_mutex_t			writing;
	pthread_mutex_t			start;
	pthread_mutex_t			*forks;
	pthread_mutex_t			*forks_taken;
	pthread_mutex_t			last_meal;
	pthread_mutex_t			death_check;
	pthread_mutex_t			meals_count;
	pthread_mutex_t			full_check;
	pthread_mutex_t			time;
	bool					mutex_are_init;
}							t_monitor;

typedef struct s_philo
{
	pthread_t				thread;
	t_monitor				*monitor;
	int						fork_id;
	int						l_fork;
	int						r_fork;
	long					last_meal;
	int						meals_count;
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
int							init_data(t_monitor *monitor, int argc,
								char **argv);
int							init_philo(t_monitor **monitor, t_philo **philo);
int							init_mutex(t_monitor *monitor);
int							init_thread(t_philo **philo);

// init_philo.c
t_philo						*create_philo(int i, t_monitor **monitor);
void						add_philo_back(t_philo **philo, t_philo *new);

// philo_routine.c
int							philo_logs(t_monitor *monitor, int philo_id,
								char *log);
int							philo_forks(t_philo *philo, t_monitor *monitor);
int							philo_eating(t_philo *philo, t_monitor *monitor);
int							philo_sleeping(t_philo *philo, t_monitor *monitor);
int							philo_thinking(t_philo *philo, t_monitor *monitor);

// philo_routine_forks.c
int							philo_left_fork(t_philo *philo, t_monitor *monitor);
int							philo_right_fork(t_philo *philo,
								t_monitor *monitor);

// philo_routine_eating.c
void						philo_countdown(t_philo *philo, t_monitor *monitor);
void						philo_update_last_meal(t_philo *philo,
								t_monitor *monitor);

// philo_routine_utils.c
bool						is_sim_running(t_monitor *monitor);
bool						ft_usleep(t_monitor *monitor, int duration);

// ft_time.c
long						time_to_x(t_monitor *monitor, int x);
long						ft_time(t_monitor *monitor);

// monitoring.c
int							monitoring(t_philo **philo, t_monitor *monitor);
bool						is_alive(t_philo *philo, t_monitor *monitor);
bool						are_all_full(t_philo **philo, t_monitor *monitor);

// tfbil.c
int							ft_atoi(const char *str);
void						ft_bzero(void *s, size_t n);
void						*ft_calloc(size_t nitems, size_t size);
void						*ft_memset(void *str, int c, size_t n);

// free_return.c
void						free_return(t_philo **philo, t_monitor *monitor,
								int state);
void						destroy_mutex(t_monitor *monitor);
int							join_thread(t_philo **philo);

// debug.c
void						print_philo(t_philo **philo);
