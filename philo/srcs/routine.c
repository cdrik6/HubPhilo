/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:32:11 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/06 01:04:33 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

// eat_alone(philo);
void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if ((*philo).nb_philo == 1)
		eating_alone(philo);
	else
	{
		if ((*philo).id % 2 == 0)
			ft_msleep(1);
			//usleep(500);
			
		while (is_dead(philo) == 0)
		{
			// if ((*philo).nb_philo != 3)
			// {
				
				//if ((*philo).id % 2 == 0 || (*philo).id == 1)
				if ((*philo).id % 2 == 0)
					eating_even(philo);
				else
					eating_odd(philo);
			// }
			// else
			// 	eating_even(philo);
			sleeping(philo);
			thinking(philo);
		}
	}
	return (data);
}
// if ((*philo).id == (*philo).nb_philo)
// 	usleep(500);
// usleep(500);
// if ((*philo).id % 2 == 0 && (*philo).nb_philo != 3)
// if ((*philo).id % 2 == 0 || (*philo).id == (*philo).nb_philo)
// if ((*philo).id % 3 == 0)
// 	ft_msleep((*philo).time_to_eat + 1);

void	eating_odd(t_philo *philo)
{
	pthread_mutex_lock((*philo).left_fork);
	print_log(philo, FORKING_L);
	pthread_mutex_lock((*philo).right_fork);
	print_log(philo, FORKING_R);
	// pthread_mutex_lock((*philo).m_meal);
	// (*philo).eating = 1;
	// pthread_mutex_unlock((*philo).m_meal);
	print_log(philo, EATING);
	pthread_mutex_lock((*philo).m_meal);
	(*philo).nb_meal++;
	(*philo).last_meal = gettime_ms();
	pthread_mutex_unlock((*philo).m_meal);
	ft_msleep((*philo).time_to_eat);
	// pthread_mutex_lock((*philo).m_meal);
	// (*philo).eating = 0;
	// pthread_mutex_unlock((*philo).m_meal);
	
	pthread_mutex_unlock((*philo).right_fork);
	pthread_mutex_unlock((*philo).left_fork);
}

void	eating_even(t_philo *philo)
{
	pthread_mutex_lock((*philo).right_fork);	
	print_log(philo, FORKING_R);
	pthread_mutex_lock((*philo).left_fork);
	print_log(philo, FORKING_L);
	// pthread_mutex_lock((*philo).m_meal);
	// (*philo).eating = 1;
	// pthread_mutex_unlock((*philo).m_meal);
	
	print_log(philo, EATING);
	pthread_mutex_lock((*philo).m_meal);
	(*philo).nb_meal++;
	(*philo).last_meal = gettime_ms();
	pthread_mutex_unlock((*philo).m_meal);
	ft_msleep((*philo).time_to_eat);
	
	// pthread_mutex_lock((*philo).m_meal);
	// (*philo).eating = 0;
	// pthread_mutex_unlock((*philo).m_meal);
	pthread_mutex_unlock((*philo).left_fork);
	pthread_mutex_unlock((*philo).right_fork);
}

void	sleeping(t_philo *philo)
{
	print_log(philo, SLEEPING);
	ft_msleep((*philo).time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_log(philo, THINKING);
	ft_msleep((*philo).time_to_eat - (*philo).time_to_sleep + 1);
	//ft_msleep(1);
	
	// if ((*philo).nb_philo == 3)	
	// 	ft_msleep((*philo).time_to_eat - (*philo).time_to_sleep + 1);
	 	//ft_msleep(119);
	// ft_msleep((*philo).time_to_eat - (*philo).time_to_sleep);
}

