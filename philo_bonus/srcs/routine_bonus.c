/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:32:11 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/14 04:16:19 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	routine(t_phi *phi, t_philo *philo)
{
	// if ((*philo).nb_philo == 1)
	// 	eating_alone(philo);
	// else
	// {
	// while (1)
	if ((*philo).id % 2 == 0)
		dead_msleep((*phi).time_to_eat, philo);
		//ft_msleep(1);
	while (is_dead(philo) == 0)
	{		
		eating(phi, philo);
		sleeping(phi, philo);
		thinking(philo);
	}
}

void	eating(t_phi *phi, t_philo *philo)
{
	sem_wait((*phi).s_forks);
	if (is_dead(philo) == 0)
	{
		print_log(philo, FORKING);
		if (is_dead(philo) == 0)
			sem_wait((*phi).s_forks);
		if (is_dead(philo) == 0)
			print_log(philo, FORKING);
		if (is_dead(philo) == 0)
		{
			print_log(philo, EATING);
			sem_wait((*phi).s_meal);
			(*philo).nb_meal++;
			(*philo).last_meal = gettime_ms();
			sem_post((*phi).s_meal);
			dead_msleep((*phi).time_to_eat, philo);
			sem_post((*phi).s_forks);
		}
	}
	sem_post((*phi).s_forks);
}

void	sleeping(t_phi *phi, t_philo *philo)
{
	if (is_dead(philo) == 0)
	{
		print_log(philo, SLEEPING);
		dead_msleep((*phi).time_to_sleep, philo);
	}
}

void	thinking(t_philo *philo)
{
	if (is_dead(philo) == 0)
	{
		print_log(philo, THINKING);
		dead_msleep((*philo).time_to_eat - (*philo).time_to_sleep + 1, philo);
	}
	// ft_msleep(1);
}

// int	is_dead(t_phi *phi, t_philo *philo)
// {
// 	sem_wait((*phi).s_dead);
// 	if ((gettime_ms() - (*philo).last_meal) > (*phi).time_to_die)
// 	{
// 		sem_post((*phi).s_dead);
// 		print_log(phi, philo, DIED);
// 		return (1);
// 	}
// 	sem_post((*phi).s_dead);
// 	return (0);
// }
