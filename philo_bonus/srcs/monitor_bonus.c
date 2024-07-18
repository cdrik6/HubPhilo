/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 22:59:31 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/18 02:45:39 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*monitor(void *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)data;
	while (1)
	{
		usleep(100);
		if (is_to_die(philo) == 1)
		{
			sem_wait(*(*philo).s_dead);
			(*philo).dead = 1;
			sem_post(*(*philo).s_dead);
			i = -1;
			while (i++ < 2 * (*philo).nb_philo)
				sem_post(*(*philo).s_forks);
			break ;
		}
		if (is_over(philo) == 1)
		{
			dead_msleep((*philo).time_to_eat, philo);
			break ;
		}		
	}
	return (NULL);
}

int	is_to_die(t_philo *philo)
{
	sem_wait(*((*philo).s_meal));
	if ((gettime_ms() - (*philo).last_meal) > (*philo).time_to_die)
	{
		sem_post(*((*philo).s_meal));
		return (1);
	}
	sem_post(*((*philo).s_meal));
	return (0);
}

int	is_dead(t_philo *philo)
{
	sem_wait(*(*philo).s_dead);
	if ((*philo).dead == 1)
	{
		sem_post(*(*philo).s_dead);
		return (1);
	}
	sem_post(*(*philo).s_dead);
	return (0);
}

int	is_over(t_philo *philo)
{
	if ((*philo).must_eat == -1)
		return (0);
	sem_wait(*(*philo).s_meal);
	if ((*philo).nb_meal >= (*philo).must_eat)
	{
		sem_post(*(*philo).s_meal);
		return (1);
	}
	sem_post(*(*philo).s_meal);
	return (0);
}
