/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:13:26 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/27 03:19:03 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

int	init_a_mutex(pthread_mutex_t mutex)
{
	if (pthread_mutex_init(&mutex, NULL) != 0)
	{
		// if (pthread_mutex_destroy(&(mutex)) != 0)
		// 	return (perror("philo: pthread_mutex_destroy"), FAILURE);
		return (perror("philo: pthread_mutex_init"), FAILURE);
	}
	return (SUCCESS);
}

int	init_phi(t_phi *phi, t_philo *philo, char **argv)
{
	(*phi).philo = philo;
	(*phi).nb_philo = ft_atoll(argv[1]);
	if (argv[5])
		(*phi).must_eat = ft_atoll(argv[5]);
	else
		(*phi).must_eat = -1;
	(*phi).is_dead = 0;
	if (init_a_mutex((*phi).m_print) == FAILURE
		|| init_a_mutex((*phi).m_dead) == FAILURE
		|| init_a_mutex((*phi).m_meal) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	init_forks(pthread_mutex_t *fork, int nb_philo)
{
	int	i;
	int	fail;

	i = 0;
	fail = 0;
	while (i < nb_philo)
	{
		if (init_a_mutex(fork[i]) == FAILURE)
			fail++;
		i++;
	}
	if (!fail)
		return (SUCCESS);
	return (FAILURE);
}

void	init_input(t_philo *philo, char **argv)
{
	(*philo).time_to_die = ft_atoll(argv[2]);
	(*philo).time_to_eat = ft_atoll(argv[3]);
	(*philo).time_to_sleep = ft_atoll(argv[4]);
}

// (*phi).philo[i] = (t_philo){0};
void	init_philo(t_phi *phi, t_philo *philo, pthread_mutex_t *fork, char **av)
{
	int	i;

	i = 0;
	while (i <= (*phi).nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].start = gettime_ms();
		philo[i].last_meal = gettime_ms();
		init_input(&philo[i], av);
		philo[i].nb_meal = 0;
		philo[i].eating = 0;
		philo[i].dead = &((*phi).is_dead);
		philo[i].m_print = &((*phi).m_print);
		philo[i].m_dead = &((*phi).m_dead);
		philo[i].m_meal = &((*phi).m_meal);
		philo[i].right_fork = &(fork[i]);
		if (i == 0)
			philo[i].left_fork = &(fork[(*phi).nb_philo - 1]);
		else
			philo[i].left_fork = &(fork[i - 1]);
		i++;
	}
}
