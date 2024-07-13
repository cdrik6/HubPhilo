/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:32:11 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/13 22:59:32 by caguillo         ###   ########.fr       */
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
		ft_msleep((*phi).time_to_eat);
	while (is_dead(philo) == 0)
	{
		// sem_wait((*phi).s_print);
		// printf("dead %d = %d\n", (*philo).id, *(*phi).philos[(*philo).id	//
		//		- 1].dead);
		// sem_post((*phi).s_print);
		eating(phi, philo);
		sleeping(phi, philo);
		thinking(philo);
	}
}

void	eating(t_phi *phi, t_philo *philo)
{
	sem_wait((*phi).s_forks);
	print_log(philo, FORKING);
	if (is_dead(philo) == 0)
	{
		sem_wait((*phi).s_forks);
		print_log(philo, FORKING);
		print_log(philo, EATING);
		sem_wait((*phi).s_meal);
		(*philo).nb_meal++;
		(*philo).last_meal = gettime_ms();
		sem_post((*phi).s_meal);
		ft_msleep((*phi).time_to_eat);
		sem_post((*phi).s_forks);
	}
	sem_post((*phi).s_forks);
	
}

void	sleeping(t_phi *phi, t_philo *philo)
{
	if (is_dead(philo) == 0)
	{
		print_log(philo, SLEEPING);
		ft_msleep((*phi).time_to_sleep);
	}
}

void	thinking(t_philo *philo)
{
	if (is_dead(philo) == 0)
	{
		print_log(philo, THINKING);
		ft_msleep((*philo).time_to_eat - (*philo).time_to_sleep + 1);
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
