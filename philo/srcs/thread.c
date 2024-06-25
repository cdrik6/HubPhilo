/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:13:26 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/26 00:05:55 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

int	init_mutex(t_phi *phi)
{
	if (pthread_mutex_init((*phi).forks, NULL) != 0)
		return (perror("philo: pthread_mutex_init"), FAILURE);
	if (pthread_mutex_init(&((*phi).m_print), NULL) != 0)
		return (perror("philo: pthread_mutex_init"), FAILURE);
	if (pthread_mutex_init(&((*phi).m_meal), NULL) != 0)
		return (perror("philo: pthread_mutex_init"), FAILURE);
	if (pthread_mutex_init(&((*phi).m_dead), NULL) != 0)
		return (perror("philo: pthread_mutex_init"), FAILURE);
	if (pthread_mutex_init(&((*phi).m_over), NULL) != 0)
		return (perror("philo: pthread_mutex_init"), FAILURE);
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

void	destroy_mutex(t_phi *phi)
{
	int	i;

	i = 0;
	while (i <= (*phi).nb_philo)
	{
		if (pthread_mutex_destroy(&((*phi).philo[i].mutex)) != 0)
			perror("philo: pthread_mutex_destroy");
		pthread_mutex_destroy(&((*phi).philo[i].m_starting));
		pthread_mutex_destroy(&((*phi).philo[i].m_print));
		pthread_mutex_destroy(&((*phi).philo[i].m_is_dead));
		pthread_mutex_destroy(&((*phi).philo[i].m_is_over));
		pthread_mutex_destroy(&((*phi).philo[i].m_meal));
		pthread_mutex_destroy(&((*phi).philo[i].m_forks));
		i++;
	}
	// if (pthread_mutex_destroy(&((*phi).m_ready)) != 0)
	// 		perror("philo: pthread_mutex_destroy");
}
