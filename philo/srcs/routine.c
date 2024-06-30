/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:32:11 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/30 03:34:10 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

// philo = phi.philo[i]
void	*routine(void *data)
{
	t_philo	*philo;
	//int nb_philo = 3;

	philo = (t_philo *)data;
	if ((*philo).id % 2 == 0)
		ft_msleep(1);
	// if ((*philo).id % 3 == 0)
	// 	ft_msleep((*philo).time_to_eat + 1);	
	while (is_dead(philo) == 0)
	{
		if ((*philo).id % 2 == 0)
			eating_even(philo);
		else
			eating_odd(philo);		
		sleeping(philo);
		thinking(philo);
	}
	return (data);
}

void	eating_even(t_philo *philo)
{
	// if (is_dead(philo) == 0)
	// {
		//
		pthread_mutex_lock((*philo).left_fork);
		print_log(philo, FORKING);
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
	// }
}

void	eating_odd(t_philo *philo)
{
	// if (is_dead(philo) == 0)
	// {
		//
		pthread_mutex_lock((*philo).right_fork);
		print_log(philo, FORKING);
		pthread_mutex_lock((*philo).left_fork);
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
		pthread_mutex_unlock((*philo).left_fork);
		pthread_mutex_unlock((*philo).right_fork);
		//
	// }
}

void	sleeping(t_philo *philo)
{
	// if (is_dead(philo) == 0)
	// {
		print_log(philo, SLEEPING);
		ft_msleep((*philo).time_to_sleep);
	// }
}

void	thinking(t_philo *philo)
{
	// if (is_dead(philo) == 0)
	// {
		print_log(philo, THINKING);
		usleep(500);
		//ft_msleep((*philo).time_to_eat - (*philo).time_to_sleep);
	//  }
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
