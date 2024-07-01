/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:58:12 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/01 05:41:09 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

// return the id of the philo that fails to be created
// 0 on success of the whole creation
int	create_thread(t_phi *phi)
{
	int	i;
	

	i = 0;
	while (i < (*phi).nb_philo)
	{
		if (pthread_create(&((*phi).philos[i].thread), NULL, &routine,
				&((*phi).philos[i])) != 0)
			return (perror("philo: pthread_create"), i + 1);
		i++;
	}
	return (0);
}

//while (i < (*phi).nb_philo)
int	join_thread(t_phi *phi, int issue_id)
{
	int	i;
	int max;

	if (issue_id == 0)
		max = (*phi).nb_philo;
	else
		max = issue_id -1;
	i = 0;	
	while (i < max)
	{
		if (pthread_join((*phi).philos[i].thread, NULL) != 0)
			return (perror("philo: pthread_join"), KO);
		i++;
	}
	return (OK);
}

int	destroy_a_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(&(*mutex)) != 0)
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
		if (destroy_a_mutex(&forks[i]) == KO)
			fail++;
		i++;
	}
	if (destroy_a_mutex(&(*phi).m_print) == KO)
		fail++;
	if (destroy_a_mutex(&(*phi).m_dead) == KO)
		fail++;
	if (destroy_a_mutex(&(*phi).m_meal) == KO)
		fail++;
	if (!fail)
		return (OK);
	return (KO);
}
