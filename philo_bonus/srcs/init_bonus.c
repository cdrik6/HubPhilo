/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:13:26 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/07 04:21:39 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	init_a_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		return (perror("philo: pthread_mutex_init"), KO);
	return (OK);
}

int	init_phi(t_phi *phi, t_philo *philos, pthread_mutex_t *forks, char **argv)
{
	int	mut_id;

	mut_id = 0;
	(*phi).philos = philos;
	(*phi).forks = forks;
	(*phi).nb_philo = ft_atoll(argv[1]);
	if (argv[5])
		(*phi).must_eat = ft_atoll(argv[5]);
	else
		(*phi).must_eat = -1;
	(*phi).is_dead = 0;
	// (*phi).ready = 0;
	mut_id = init_forks((*phi).forks, (*phi).nb_philo);
	if (mut_id != 0)
		return (mut_id);
	if (init_a_mutex(&(*phi).m_print) == KO)
		return ((*phi).nb_philo + 1);
	if (init_a_mutex(&(*phi).m_dead) == KO)
		return ((*phi).nb_philo + 2);
	if (init_a_mutex(&(*phi).m_meal) == KO)
		return ((*phi).nb_philo + 3);
	return (0);
}

// in fail case, return philo id
// 0 if no fail
int	init_forks(pthread_mutex_t *forks, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (init_a_mutex(&forks[i]) == KO)
			return (i + 1);
		i++;
	}
	return (0);
}

// (*phi).philo[i] = (t_philo){0};
// no need to initialize thread before send it to pthread_create
void	init_philos(t_phi *phi, t_philo *philos, pthread_mutex_t *forks,
		char **argv)
{
	int	i;

	i = 0;
	while (i < (*phi).nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].start = gettime_ms();
		philos[i].last_meal = gettime_ms();
		philos[i].nb_philo = ft_atoll(argv[1]);
		philos[i].time_to_die = ft_atoll(argv[2]);
		philos[i].time_to_eat = ft_atoll(argv[3]);
		philos[i].time_to_sleep = ft_atoll(argv[4]);
		philos[i].nb_meal = 0;
		//philos[i].eating = 0;		
		philos[i].dead = &((*phi).is_dead);
		philos[i].m_print = &((*phi).m_print);
		philos[i].m_dead = &((*phi).m_dead);
		philos[i].m_meal = &((*phi).m_meal);
		philos[i].right_fork = &(forks[i]);
		if (i == 0)
			philos[i].left_fork = &(forks[(*phi).nb_philo - 1]);
		else
			philos[i].left_fork = &(forks[i - 1]);
		i++;
	}
}

// init_input(&philos[i], argv);
// void	init_input(t_philo *philo, char **argv)
// {
// 	(*philo).time_to_die = ft_atoll(argv[2]);
// 	(*philo).time_to_eat = ft_atoll(argv[3]);
// 	(*philo).time_to_sleep = ft_atoll(argv[4]);
// }

