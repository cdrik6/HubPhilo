/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:58:12 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/28 01:07:23 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

int	create_thread(t_phi *phi)
{
	int	i;

	i = 0;
	while (i < (*phi).nb_philo)
	{
		if (pthread_create(&((*phi).philo[i].thread), NULL, &routine,
				&((*phi).philo[i])) != 0)
			return (perror("philo: pthread_create"), FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	join_thread(t_phi *phi)
{
	int	i;

	i = 0;
	while (i < (*phi).nb_philo)
	{
		if (pthread_join((*phi).philo[i].thread, NULL) != 0)
			return (perror("philo: pthread_join"), FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	destroy_a_mutex(pthread_mutex_t mutex)
{
	if (pthread_mutex_destroy(&(mutex)) != 0)
		return (perror("philo: pthread_mutex_destroy"), FAILURE);
	return (SUCCESS);
}

// if (pthread_mutex_destroy(&((*phi).m_ready)) != 0)
// 		perror("philo: pthread_mutex_destroy");
int	destroy_mutex(t_phi *phi, pthread_mutex_t *fork)
{
	int	i;
	int	fail;

	fail = 0;
	i = 0;
	while (i < (*phi).nb_philo)
	{
		if (destroy_a_mutex(fork[i]) == FAILURE)
			fail++;
		i++;
	}
	if (destroy_a_mutex((*phi).m_print) == FAILURE)
		fail++;
	if (destroy_a_mutex((*phi).m_dead) == FAILURE)
		fail++;
	if (destroy_a_mutex((*phi).m_meal) == FAILURE)
		fail++;
	if (!fail)
		return (SUCCESS);
	return (FAILURE);
}
