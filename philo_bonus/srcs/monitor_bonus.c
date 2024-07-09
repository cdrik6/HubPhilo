/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 22:59:31 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/09 05:07:39 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	is_a_dead(t_phi *phi)
{
	int	i;

	i = 0;
	while (i < (*phi).nb_philo)
	{
		if (is_to_die(phi, &((*phi).philos[i])) == 1)
		{
			print_log(phi, &((*phi).philos[i]), DIED);
			sem_wait((*phi).s_dead);
			*((*phi).philos[i].dead) = 1;
			sem_post((*phi).s_dead);
			return (1);
		}
		i++;
	}
	return (0);
}

// int	is_all_over(t_phi *phi)
// {
// 	int	i;

// 	if ((*phi).must_eat == -1)
// 		return (0);
// 	i = 0;
// 	while (i < (*phi).nb_philo)
// 	{
// 		pthread_mutex_lock(&((*phi).m_meal));
// 		if ((*phi).philos[i].nb_meal < (*phi).must_eat)
// 			return (pthread_mutex_unlock(&((*phi).m_meal)), 0);
// 		pthread_mutex_unlock(&((*phi).m_meal));
// 		i++;
// 	}
// 	pthread_mutex_lock(&((*phi).m_dead));
// 	(*phi).is_dead = 1;
// 	pthread_mutex_unlock(&((*phi).m_dead));
// 	return (1);
// }

void	monitor(t_phi *phi)
{
	// int	ready;
	// ready = 0;
	// while (ready != (*phi).nb_philo)
	// {
	// 	usleep(100);
	// 	pthread_mutex_lock(&((*phi).m_dead));
	// 	ready = (*phi).ready;
	// 	pthread_mutex_unlock(&((*phi).m_dead));
	// 	//printf("%d\n", ready);
	// }
	while (1)
	{
		// if (is_a_dead(phi) == 1 || is_all_over(phi) == 1)
		if (is_a_dead(phi) == 1)
			break ;
		// usleep(10);
	}
}

// printf("%d", (gettime_ms() - (*philo).last_meal) > (*philo).time_to_die);
int	is_to_die(t_phi *phi, t_philo *philo)
{
	sem_wait((*phi).s_meal);
	if ((gettime_ms() - (*philo).last_meal) > (*phi).time_to_die)
	{
		sem_post((*phi).s_meal);
		return (1);
	}
	sem_post((*phi).s_meal);
	return (0);
}

int	is_dead(t_phi *phi, t_philo *philo)
{
	sem_wait((*phi).s_dead);
	if (*((*philo).dead) == 1)
	{
		sem_post((*phi).s_dead);
		return (1);
	}
	sem_post((*phi).s_dead);
	return (0);
}
