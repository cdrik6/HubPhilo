/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:32:11 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/18 20:49:18 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	routine(t_philo *philo)
{
	if ((*philo).id % 2 == 0)
		usleep(250);
	while (is_dead(philo) == 0 && is_over(philo) == 0)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
}

void	eating(t_philo *philo)
{
	sem_wait(*(*philo).s_forks);
	print_log(philo, FORKING);
	sem_wait(*(*philo).s_forks);
	print_log(philo, FORKING);
	print_log(philo, EATING);
	sem_wait(*(*philo).s_meal);
	(*philo).nb_meal++;
	(*philo).last_meal = gettime_ms();
	sem_post(*(*philo).s_meal);
	dead_msleep((*philo).time_to_eat, philo);
	sem_post(*(*philo).s_forks);
	sem_post(*(*philo).s_forks);
}

void	sleeping(t_philo *philo)
{
	if (is_dead(philo) == 0 && is_over(philo) == 0)
	{
		print_log(philo, SLEEPING);
		dead_msleep((*philo).time_to_sleep, philo);
	}
}

void	thinking(t_philo *philo)
{
	if (is_dead(philo) == 0 && is_over(philo) == 0)
	{
		print_log(philo, THINKING);
		if ((*philo).nb_philo % 2 == 1 && (*philo).id == (*philo).nb_philo)
			dead_msleep((*philo).time_to_eat, philo);
		else if ((*philo).nb_philo % 2 == 1)
			dead_msleep((*philo).time_to_eat - (*philo).time_to_sleep + 1,
				philo);
	}
}
