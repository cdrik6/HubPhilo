/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:22:06 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/07 04:16:20 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef MAX_PHILO
#  define MAX_PHILO 200
# endif
# define OK 0
# define KO 1
# define NBM 3
# define ERR_ARG "philo: wrong number of arguments\n"
# define USAGE \
	"Usage: ./philo number_of_philosophers time_to_die (ms) \
	time_to_eat (ms) time_to_sleep (ms) \
	[number_of_times_each_philosopher_must_eat]\n"
# define MIN_NBP "philo: invalid number_of_philosophers\n"
# define MAX_NBP "philo: invalid number_of_philosophers\n"
# define ERR_TTD "philo: invalid time_to_die\n"
# define ERR_TTE "philo: invalid time_to_eat\n"
# define ERR_TTS "philo: invalid time_to_sleep\n"
# define ERR_TME "philo: invalid number_of_times_each_philosopher_must_eat\n"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define FORKING "has taken a fork"
# define FORKING_L "has taken a fork left"
# define FORKING_R "has taken a fork right"
# define DIED "died"

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	long			start;
	long			last_meal;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal;
	// int				eating;
	int				*dead;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*m_print;
	pthread_mutex_t	*m_dead;
	pthread_mutex_t	*m_meal;
}					t_philo;

typedef struct s_phi
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				nb_philo;
	int				must_eat;
	int				is_dead;
	// int				ready;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_meal;
}					t_phi;

// main.c
// main
int					philosopher(t_phi *phi, t_philo *philos,
						pthread_mutex_t *forks, char **argv);
int					check_args(int argc, char **argv);
void				free_phi(t_philo *philos, pthread_mutex_t *forks);

// init.c
int					init_a_mutex(pthread_mutex_t *mutex);
int					init_phi(t_phi *phi, t_philo *philos,
						pthread_mutex_t *forks, char **argv);
int					init_forks(pthread_mutex_t *fork, int nb_philo);
void				init_philos(t_phi *phi, t_philo *philo,
						pthread_mutex_t *fork, char **argv);

// tools.c
long				gettime_ms(void);
void				print_log(t_philo *philo, char *str);
void				ft_msleep(long ms);
void				eating_alone(t_philo *philo);

// utils.c
void				putstr_fd(char *str, int fd);
int					is_space(char c);
long long			ft_atoll(char *str);
long long			check_limit(int sign, unsigned long long nbr);
void				*ft_calloc(size_t nb_elem, size_t size_elem);

// thread.c
int					create_thread(t_phi *phi);
int					join_thread(t_phi *phi, int issue_id);
int					destroy_a_mutex(pthread_mutex_t *mutex);
int					destroy_mutex(t_phi *phi, pthread_mutex_t *fork);
int					destroy_mutex_id(t_phi *phi, pthread_mutex_t *forks,
						int mut_id);

// routine.c
void				*routine(void *data);
void				eating_even(t_philo *philo);
void				eating_odd(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);

// monitor.c
int					is_a_dead(t_phi *phi);
int					is_all_over(t_phi *phi);
void				monitor(t_phi *phi);
int					is_to_die(t_philo *philo);
int					is_dead(t_philo *philo);

// draft
// int ft_atoi(char *str);
// void				init_input(t_philo *philo, char **argv);
// int				init_phi(t_phi *phi, t_philo *philo, char **argv);
// void				alone(t_phi *phi);

#endif