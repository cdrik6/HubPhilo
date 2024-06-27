/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 22:59:31 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/27 23:51:58 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

int	is_a_dead(t_phi *phi)
{
	int	i;

	i = 0;
	while (i < (*phi).nb_philo)
	{
		if (is_to_die(&((*phi).philo[i])) == 1)
		{
			print_log(&((*phi).philo[i]), DIED);
			pthread_mutex_lock(&((*phi).m_dead));
			*((*phi).philo[i].dead) = 1;
			pthread_mutex_unlock(&((*phi).m_dead));
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_all_over(t_phi *phi)
{
	int	i;

	if ((*phi).must_eat == -1)
		return (0);
	i = 0;
	while (i < (*phi).nb_philo)
	{
		pthread_mutex_lock(&((*phi).m_meal));
		if ((*phi).philo[i].nb_meal < (*phi).must_eat)
			return (pthread_mutex_unlock(&((*phi).m_meal)), 0);
		pthread_mutex_unlock(&((*phi).m_meal));
		i++;
	}
	// i = 0;
	// while (i < (*phi).nb_philo)
	// {
	// 	pthread_mutex_lock(&((*phi).philo[i].m_is_over));
	// 	(*phi).philo[i].is_over = 1;
	// 	pthread_mutex_unlock(&((*phi).philo[i].m_is_over));
	// 	i++;
	// }
	return (1);
}

void	monitor(t_phi *phi)
{
	while (1)
	{
		if (is_a_dead(phi) == 1 || is_all_over(phi) == 1)
			break ;
	}
}

int	is_to_die(t_philo *philo)
{
	pthread_mutex_lock((*philo).m_meal);
	if ((gettime_ms() - (*philo).last_meal) > (*philo).time_to_die)
	{
		pthread_mutex_unlock((*philo).m_meal);
		return (1);
	}
	pthread_mutex_unlock((*philo).m_meal);
	return (0);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock((*philo).m_dead);
	if (*((*philo).dead) == 1)
	{
		pthread_mutex_unlock((*philo).m_dead);
		return (1);
	}
	pthread_mutex_unlock((*philo).m_dead);
	return (0);
}

// int		ready;
// ready = 0;
// while (ready != (*phi).nb_philo + 1)
// {
// 	usleep(100);
// 	pthread_mutex_lock(&((*phi).philo[0].mutex));
// 	ready = (*phi).ready;
// 	pthread_mutex_unlock(&((*phi).philo[0].mutex));
// 	// printf("%d\n", ready);
// }
