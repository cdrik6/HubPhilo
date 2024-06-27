/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:58:12 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/27 04:15:43 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

// void	create_thread_manager(t_phi *phi)
// {
// 	if (pthread_create(&((*phi).philo[0].thread), NULL, &manager, &(*phi)) != 0)
// 	{
// 		perror("philo: pthread_create");
// 		destroy_mutex(phi);
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(&((*phi).philo[0].mutex));
// 		((*phi).ready)++;
// 		pthread_mutex_unlock(&((*phi).philo[0].mutex));
// 		// printf("ici %d\n", (*phi).ready);
// 	}
// }

int	create_thread(t_phi *phi)
{
	int	i;

	i = 0;
	while (i < (*phi).nb_philo)
	{
		if (pthread_create(&((*phi).philo[i].thread), NULL, &routine,
				&((*phi).philo[i])) != 0)
		{
			perror("philo: pthread_create");
			//destroy_mutex(phi);
		}
		// else
		// {
		// 	pthread_mutex_lock(&((*phi).philo[0].mutex));
		// 	((*phi).ready)++;
		// 	pthread_mutex_unlock(&((*phi).philo[0].mutex));
		// 	// printf("la %d\n", (*phi).ready);
		// }
		i++;
	}
	return (SUCCESS);
}

void	join_thread(t_phi *phi)
{
	int	i;

	i = 0;
	while (i < (*phi).nb_philo)
	{
		if (pthread_join((*phi).philo[i].thread, NULL) != 0)
		{
			perror("philo: pthread_join");
			//destroy_mutex(phi);
		}
		i++;
	}
}

void	destroy_mutex(t_phi *phi, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < (*phi).nb_philo)
	{
		if (pthread_mutex_destroy(&(fork[i])) != 0)
			perror("philo: pthread_mutex_destroy");
		i++;
	}
	pthread_mutex_destroy(&((*phi).m_print));
	pthread_mutex_destroy(&((*phi).m_dead));
	pthread_mutex_destroy(&((*phi).m_meal));
	// if (pthread_mutex_destroy(&((*phi).m_ready)) != 0)
	// 		perror("philo: pthread_mutex_destroy");
}
