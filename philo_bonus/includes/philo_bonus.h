/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:22:06 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/16 23:56:57 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h> // For O_* constants
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
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
# define DIED "died"
# define S_FORKS "/s_forks"
# define S_PRINT "/s_print"
# define S_DEAD "/s_dead"
# define S_MEAL "/s_meal"
# define S_STOP "/s_stop"

typedef struct s_philo
{
	pid_t		pid;
	pthread_t	thread;
	int			id;
	time_t		start;
	time_t		last_meal;
	int			nb_meal;
	//
	int			nb_philo;
	time_t		time_to_die;
	time_t		time_to_eat;
	time_t		time_to_sleep;
	int			must_eat;
	int			dead;
	//
	sem_t		**s_forks;
	sem_t		**s_print;
	sem_t		**s_dead;
	sem_t		**s_meal;
	sem_t		**s_stop;
}				t_philo;

// pid_t	*phi_pid;
// time_t = unsigned long
typedef struct s_phi
{
	t_philo		*philos;
	//
	// pthread_t	thread;
	//
	int			nb_philo;
	time_t		time_to_die;
	time_t		time_to_eat;
	time_t		time_to_sleep;
	int			must_eat;
	//int			is_dead;
	time_t		start;
	//
	sem_t		*s_forks;
	sem_t		*s_print;
	sem_t		*s_dead;
	sem_t		*s_meal;
	sem_t		*s_stop;
	// pid_t *pid;
}				t_phi;

// main.c
// main
// int			philosopher(t_phi *phi, t_philo *philos,
// pthread_mutex_t *forks,				char **argv);
int				check_args(int argc, char **argv);
// void		free_phi(t_philo *philos, pthread_mutex_t *forks);
int				wait_dead(t_phi phi);

// init.c
int				init_phi(t_phi *phi, t_philo *philos, char **argv);
int				init_sem(t_phi *phi);
int				create_philos(t_phi *phi);
void			init_philo(t_phi *phi, pid_t pid, int i);
// int			init_forks(pthread_mutex_t *fork, int nb_philo);
void			is_a_dead(t_phi *phi);

// tools.c
long			gettime_ms(void);
void			print_log(t_philo *philo, char *str);
void			ft_msleep(long ms);
void			dead_msleep(long ms, t_philo *philo);
// void		eating_alone(t_philo *philo);

// utils.c
void			putstr_fd(char *str, int fd);
int				is_space(char c);
long long		ft_atoll(char *str);
long long		check_limit(int sign, unsigned long long nbr);
void			*ft_calloc(size_t nb_elem, size_t size_elem);

// thread.c
int				create_thread(t_philo *philo);
// int			create_thread(t_phi *phi);
// int			join_thread(t_phi *phi, int issue_id);
// int			destroy_a_mutex(pthread_mutex_t *mutex);
// int			destroy_mutex(t_phi *phi,
// pthread_mutex_t *fork);
// int			destroy_mutex_id(t_phi *phi,
// pthread_mutex_t *forks, int mut_id);

// routine.c
void			routine(t_phi *phi, t_philo *philo);
void			eating(t_phi *phi, t_philo *philo);
void			sleeping(t_phi *phi, t_philo *philo);
void			thinking(t_philo *philo);
// int				is_dead(t_phi *phi, t_philo *philo);
// void		eating_even(t_philo *philo);
// void		eating_odd(t_philo *philo);
// void		sleeping(t_philo *philo);
// void		thinking(t_philo *philo);

// monitor.c
int	is_over(t_philo *philo);
void			*monitor(void *data);
int				is_to_die(t_philo *philo);
// int				is_a_dead(t_phi *phi);
// int			is_all_over(t_phi *phi);
// void			monitor(t_phi *phi);
//  int				is_to_die(t_phi *phi, t_philo *philo);
int				is_dead(t_philo *philo);

#endif
