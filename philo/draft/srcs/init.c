/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:13:26 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/26 21:50:36 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

void	init_phi(t_phi *phi, char **argv)
{
	(*phi).nb_philo = ft_atoll(argv[1]);
	if (argv[5])
		(*phi).must_eat = ft_atoll(argv[5]);
	else
		(*phi).must_eat = -1;
	(*phi).time_to_die = ft_atoll(argv[2]);
	(*phi).time_to_eat = ft_atoll(argv[3]);
	(*phi).time_to_sleep = ft_atoll(argv[4]);
	(*phi).dead = 0;
	(*phi).over = 0;
}

int	init_mutex(t_phi *phi)
{
	int	i;

	(*phi).forks = ft_calloc((*phi).nb_philo, sizeof(pthread_mutex_t));
	if ((*phi).forks)
		return (FAILURE);
	i = 0;
	while (i < (*phi).nb_philo)
	{
		if (pthread_mutex_init(&((*phi).forks[i]), NULL) != 0)
			return (perror("philo: pthread_mutex_init"), FAILURE);
		i++;
	}
	if (pthread_mutex_init(&((*phi).m_print), NULL) != 0)
		return (perror("philo: pthread_mutex_init"), FAILURE);
	if (pthread_mutex_init(&((*phi).m_meal), NULL) != 0)
		return (perror("philo: pthread_mutex_init"), FAILURE);
	if (pthread_mutex_init(&((*phi).m_dead), NULL) != 0)
		return (perror("philo: pthread_mutex_init"), FAILURE);
	if (pthread_mutex_init(&((*phi).m_over), NULL) != 0)
		return (perror("philo: pthread_mutex_init"), FAILURE);
	return (SUCCESS);
}

void	create_thread(t_phi *phi)
{
	int	i;

	i = 1;
	// i = 0;
	while (i <= (*phi).nb_philo)
	{
		if (pthread_create(&((*phi).philo[i].thread), NULL, &routine,
				&((*phi).philo[i])) != 0)
		{
			perror("philo: pthread_create");
			destroy_mutex(phi);
		}
		else
		{
			pthread_mutex_lock(&((*phi).philo[0].mutex));
			((*phi).ready)++;
			pthread_mutex_unlock(&((*phi).philo[0].mutex));
			// printf("la %d\n", (*phi).ready);
		}
		i++;
	}
}

void	join_thread(t_phi *phi)
{
	int	i;

	i = 0;
	while (i <= (*phi).nb_philo)
	{
		if (pthread_join((*phi).philo[i].thread, NULL) != 0)
		{
			perror("philo: pthread_join");
			destroy_mutex(phi);
		}
		i++;
	}
}

// perror("philo: pthread_mutex_destroy");
void	destroy_mutex(t_phi *phi)
{
	int	i;

	i = 0;
	while (i < (*phi).nb_philo)
	{
		pthread_mutex_destroy(&((*phi).forks[i]));
		i++;
	}
	pthread_mutex_destroy(&((*phi).m_print));
	pthread_mutex_destroy(&((*phi).m_meal));
	pthread_mutex_destroy(&((*phi).m_dead));
	pthread_mutex_destroy(&((*phi).m_over));
}
