/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:58:12 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/01 22:44:08 by caguillo         ###   ########.fr       */
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

// while (i < (*phi).nb_philo)
int	join_thread(t_phi *phi, int issue_id)
{
	int	i;
	int	max;

	if (issue_id == 0)
		max = (*phi).nb_philo;
	else
		max = issue_id - 1;
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

// mut_id == 0
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

// mut_id != 0
// received id where init_mutex failed, so destroy until id excluded
// if mut_id = 1 means init[0] failed, the first to be init, so destroy nothing
// if mut_id = nb_philo means init[nb-1] failed, so destroy til init[nb-2]
// if mut_id = nb_philo + 1 means init[print] failed, so destroy til init[nb-1]
// if mut_id = nb_philo + 2 means init[dead] failed, so destroy til init[print]
// if mut_id = nb_philo + 3 means init[meal] failed, so destroy til init[dead]
int	destroy_mutex_id(t_phi *phi, pthread_mutex_t *forks, int mut_id)
{
	int	i;

	i = 0;
	if (mut_id <= (*phi).nb_philo + 1)
	{
		while (i < mut_id - 1)
		{
			if (destroy_a_mutex(&forks[i]) == KO)
				return (KO);
			i++;
		}
		return (KO);
	}
	if (mut_id == (*phi).nb_philo + 2)
		return (destroy_a_mutex(&(*phi).m_print), destroy_mutex_id(phi, forks,
				(*phi).nb_philo + 1));
	if (mut_id == (*phi).nb_philo + 3)
		return (destroy_a_mutex(&(*phi).m_dead), destroy_mutex_id(phi, forks,
				(*phi).nb_philo + 2));
	return (KO);
}
