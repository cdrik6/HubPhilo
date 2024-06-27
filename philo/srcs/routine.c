/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:32:11 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/28 01:30:57 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

// philo = phi.philo[i]
void	*routine(void *data)
{
	t_philo	*philo;

	// int		starting;
	philo = (t_philo *)data;
	if ((*philo).id % 2 == 0)
		ft_msleep(1);
	while (is_dead(philo) == 0)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (data);
}

void	eating(t_philo *philo)
{
	if (is_dead(philo) == 0)
	{
		//
		pthread_mutex_lock((*philo).left_fork);
		print_log(philo, FORKING);
		//
		pthread_mutex_lock((*philo).right_fork);
		print_log(philo, FORKING);
		//
		(*philo).eating = 1;
		print_log(philo, EATING);
		//
		pthread_mutex_lock((*philo).m_meal);
		(*philo).nb_meal++;
		(*philo).last_meal = gettime_ms();
		pthread_mutex_unlock((*philo).m_meal);
		//
		ft_msleep((*philo).time_to_eat);
		(*philo).eating = 0;
		pthread_mutex_unlock((*philo).right_fork);
		pthread_mutex_unlock((*philo).left_fork);
		//
	}
}

void	sleeping(t_philo *philo)
{
	if (is_dead(philo) == 0)
	{
		print_log(philo, SLEEPING);
		ft_msleep((*philo).time_to_sleep);
	}
}

void	thinking(t_philo *philo)
{
	if (is_dead(philo) == 0)
	{
		print_log(philo, THINKING);
	}
}

void	alone(t_phi *phi)
{
	// printf("ici\n");
	print_log(&((*phi).philo[0]), FORKING);
	ft_msleep((*phi).philo[0].time_to_die);
	print_log(&((*phi).philo[0]), DIED);
}

// int	is_over(t_philo *philo)
// {
// 	pthread_mutex_lock(&((*philo).m_is_over));
// 	if ((*philo).is_over == 1)
// 	{
// 		pthread_mutex_unlock(&((*philo).m_is_over));
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&((*philo).m_is_over));
// 	return (0);
// }
