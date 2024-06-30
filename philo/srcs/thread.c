/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:58:12 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/29 22:49:36 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

int	create_thread(t_phi *phi)
{
	int	i;

	i = 0;
	while (i < (*phi).nb_philo)
	{
		if (pthread_create(&((*phi).philos[i].thread), NULL, &routine,
				&((*phi).philos[i])) != 0)
			return (perror("philo: pthread_create"), KO);
		i++;
	}
	return (OK);
}

int	join_thread(t_phi *phi)
{
	int	i;

	i = 0;
	while (i < (*phi).nb_philo)
	{
		if (pthread_join((*phi).philos[i].thread, NULL) != 0)
			return (perror("philo: pthread_join"), KO);
		i++;
	}
	return (OK);
}

int	destroy_a_mutex(pthread_mutex_t mutex)
{
	if (pthread_mutex_destroy(&(mutex)) != 0)
		return (perror("philo: pthread_mutex_destroy"), KO);
	return (OK);
}

// if (pthread_mutex_destroy(&((*phi).m_ready)) != 0)
// 		perror("philo: pthread_mutex_destroy");
int	destroy_mutex(t_phi *phi, pthread_mutex_t *forks)
{
	int	i;
	int	fail;

	fail = 0;
	i = 0;
	while (i < (*phi).nb_philo)
	{
		if (destroy_a_mutex(forks[i]) == KO)
			fail++;
		i++;
	}
	if (destroy_a_mutex((*phi).m_print) == KO)
		fail++;
	if (destroy_a_mutex((*phi).m_dead) == KO)
		fail++;
	if (destroy_a_mutex((*phi).m_meal) == KO)
		fail++;
	if (!fail)
		return (OK);
	return (KO);
}
