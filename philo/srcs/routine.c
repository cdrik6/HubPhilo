/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:32:11 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/03 00:36:53 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

// void	eat_alone(t_philo *philo)
// {
// 	// ft_msleep((*philo).time_to_die);
// 	// print_log(philo, DIED);
// }

// philo = phi.philo[i]
void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if ((*philo).nb_philo == 1)
	{
		// eat_alone(philo);
		pthread_mutex_lock((*philo).right_fork);
		print_log(philo, FORKING);
		pthread_mutex_unlock((*philo).right_fork);
	}
	else
	{
		// if ((*philo).id % 2 == 0 && (*philo).nb_philo != 3)
		if ((*philo).id % 2 == 0)
			ft_msleep(1);
		// if ((*philo).id == (*philo).nb_philo)
		// 	ft_msleep(1);
		// if ((*philo).id % 3 == 0)
		// 	ft_msleep((*philo).time_to_eat + 1);
		while (is_dead(philo) == 0)
		{
			if ((*philo).nb_philo != 3)
			{
				if ((*philo).id % 2 == 0)
					eating_even(philo);
				else
					eating_odd(philo);
			}
			else
				eating_even(philo);
			sleeping(philo);
			thinking(philo);
		}
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
	// if ((*philo).nb_philo == 3)
	// 	// ft_msleep(119);
	// 	ft_msleep((*philo).time_to_eat - (*philo).time_to_sleep);
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
