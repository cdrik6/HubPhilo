/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:32:11 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/09 04:54:00 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	routine(t_phi *phi, t_philo *philo)
{
	// if ((*philo).nb_philo == 1)
	// 	eating_alone(philo);
	// else
	// {
	while (is_dead(phi, philo) == 0)
	{
		eating(phi, philo);
		sleeping(phi, philo);
		thinking(phi, philo);
	}
	// }
	// printf("sizeof(t_philo) = %ld\n", sizeof(t_philo));
	// sem_wait((*phi).s_print);
	// printf("id = %d\n", (*philo).id);
	// sem_post((*phi).s_print);
	// print_log(phi, philo, DIED);
	free((*phi).philos);
	exit(OK);
}

void	eating(t_phi *phi, t_philo *philo)
{
	sem_wait((*phi).s_forks);
	print_log(phi, philo, FORKING);
	sem_wait((*phi).s_forks);
	print_log(phi, philo, FORKING);
	print_log(phi, philo, EATING);
	sem_wait((*phi).s_meal);
	(*philo).nb_meal++;
	(*philo).last_meal = gettime_ms();
	sem_post((*phi).s_meal);
	ft_msleep((*phi).time_to_eat);
	sem_post((*phi).s_forks);
	sem_post((*phi).s_forks);
}

void	sleeping(t_phi *phi, t_philo *philo)
{
	print_log(phi, philo, SLEEPING);
	ft_msleep((*phi).time_to_sleep);
}

void	thinking(t_phi *phi, t_philo *philo)
{
	print_log(phi, philo, THINKING);
	// ft_msleep((*phi).time_to_eat - (*phi).time_to_sleep + 1);
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
