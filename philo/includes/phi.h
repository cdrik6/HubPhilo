/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:22:06 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/27 04:12:15 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHI_H
# define PHI_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef MAX_PHILO
#  define MAX_PHILO 200
# endif
# define SUCCESS 0
# define FAILURE 1
# define NBM 3
# define ERR_ARG "philo: wrong number of arguments\n"
# define USAGE \
	"Usage: ./philo number_of_philosophers time_to_die (ms) \
	time_to_eat (ms) time_to_sleep (ms) \
	[number_of_times_each_philosopher_must_eat]\n"
# define MIN_NBP "philo: number of philosophers should be at least 1\n"
# define MAX_NBP "philo: number of philosophers should be no more than 200\n"
# define ERR_TTD "philo: time to die should be a positive number\n"
# define ERR_TTE "philo: time to eat should be a positive number\n"
# define ERR_TTS "philo: time to sleep should be a positive number\n"
# define ERR_TME "philo: number_of_times_each_philosopher_must_eat should be positive\n"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define FORKING "has taken a fork"
# define DIED "died"

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	long			start;
	long			last_meal;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal;
	int				eating;
	int				*dead;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*m_print;
	pthread_mutex_t	*m_dead;
	pthread_mutex_t	*m_meal;
	// int				is_over;
	// pthread_mutex_t	m_is_over;
}					t_philo;

typedef struct s_phi
{
	t_philo			*philo;
	int				nb_philo;
	int				must_eat;
	int				is_dead;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_meal;
	// int				ready;
}					t_phi;

// main.c
int					check_args(int argc, char **argv);
int					check_argv(char **argv);

// init.c
int					init_a_mutex(pthread_mutex_t mutex);
int					init_phi(t_phi *phi, t_philo *philo, char **argv);
int					init_forks(pthread_mutex_t *fork, int nb_philo);
void				init_input(t_philo *philo, char **argv);
void				init_philo(t_phi *phi, t_philo *philo,
						pthread_mutex_t *fork, char **av);

// tools.c
void				putstr_fd(char *str, int fd);
int					is_space(char c);
long long			ft_atoll(char *str);
void				ft_msleep(long ms);
void				print_log(t_philo *philo, char *str);
// void				print_log(long timestamp_ms, int philo_id, char *str);
long				gettime_ms(void);
// long				get_ms(t_philo philo);

// thread.c
// void				init_mutex(t_phi *phi);
// void				create_thread_manager(t_phi *phi);
// int					manager(t_phi *phi);
int					create_thread(t_phi *phi);
void				join_thread(t_phi *phi);
void	destroy_mutex(t_phi *phi, pthread_mutex_t *fork);

// routine.c
void				*routine(void *data);
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);
void				alone(t_phi *phi);
// int					is_over(t_philo *philo);

// monitor.c
int					is_a_dead(t_phi *phi);
int					is_all_over(t_phi *phi);
void				monitor(t_phi *phi);
int					is_to_die(t_philo *philo);
int					is_dead(t_philo *philo);

// // forks.c
// void				allocate_forks(t_phi *phi);
// void				even_allocation(t_phi *phi);
// int					is_last(t_phi *phi);
// void				odd_allocation(t_phi *phi);

#endif