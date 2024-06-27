/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:32:11 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/27 04:37:26 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

// philo = phi.philo[i]
void	*routine(void *data)
{
	t_philo	*philo;

	// int		starting;
	philo = (t_philo *)data;
	while (is_dead(philo) == 0)
	{
		// pthread_mutex_lock(&((*philo).m_starting));
		// starting = (*philo).starting;
		// pthread_mutex_unlock(&((*philo).m_starting));
		// if (starting == 1)
		// {
		// pthread_mutex_lock(&((*philo).m_starting));
		// (*philo).starting = 0;
		// pthread_mutex_unlock(&((*philo).m_starting));
		eating(philo);
		sleeping(philo);
		thinking(philo);
		// }
	}
	return (data);
}

// && got_forks(philo) == 1
// void	update_eat_count(t_phi *phi)
// {
// 	int	i;

// 	// count % 2 == (*philo).id % 2
// 	i = 1;
// 	while (i <= (*phi).nb_philo)
// 	{
// 		pthread_mutex_lock(&((*phi).philo[i].m_meal));
// 		if ((*phi).eat_count < (*phi).philo[i].nb_meal + 1)
// 		{
// 			(*phi).eat_count = (*phi).philo[i].nb_meal + 1;
// 			pthread_mutex_unlock(&((*phi).philo[i].m_meal));
// 			break ;
// 		}
// 		pthread_mutex_unlock(&((*phi).philo[i].m_meal));
// 		i++;
// 	}
// }

void	eating(t_philo *philo)
{
	// int	forks;
	// pthread_mutex_lock(&((*philo).m_forks));
	// forks = (*philo).forks;
	// pthread_mutex_unlock(&((*philo).m_forks));
	// if (forks == 1 && is_dead(philo) == 0)
	if (is_dead(philo) == 0)
	{
		//
		pthread_mutex_lock((*philo).right_fork);
		print_log(philo, FORKING);
		pthread_mutex_lock((*philo).left_fork);
		print_log(philo, FORKING);
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
	}
}

void	sleeping(t_philo *philo)
{
	// is_dead(philo);
	// if ((*philo).sleeping == 0 && (*philo).is_dead == 0
	//	&& is_over(philo) == 0)
	// if ((*philo).sleeping == 0 && is_dead(philo) == 0 && is_over(philo) == 0)
	// if ((*philo).sleeping == 0 && is_over(philo) == 0)
	// {
	// 	pthread_mutex_lock(&((*philo).mutex));
	// 	(*philo).sleeping = 1;
	// 	(*philo).thinking = 0;
	// 	pthread_mutex_unlock(&((*philo).mutex));
	// pthread_mutex_lock(&((*philo).m_print));
	print_log(philo, SLEEPING);
	// pthread_mutex_unlock(&((*philo).m_print));
	//
	ft_msleep((*philo).time_to_sleep);
	//
	// pthread_mutex_lock(&((*philo).mutex));
	// (*philo).thinking = 0;
	// pthread_mutex_unlock(&((*philo).mutex));
	// }
}

void	thinking(t_philo *philo)
{
	// is_dead(philo);
	// if ((*philo).thinking == 0 && (*philo).is_dead == 0
	//	&& is_over(philo) == 0)
	// if ((*philo).thinking == 0 && is_dead(philo) == 0 && is_over(philo) == 0)
	// if ((*philo).thinking == 0 && is_over(philo) == 0)
	// {
	// 	pthread_mutex_lock(&((*philo).mutex));
	// 	(*philo).thinking = 1;
	// 	pthread_mutex_unlock(&((*philo).mutex));
	// pthread_mutex_lock(&((*philo).m_print));
	print_log(philo, THINKING);
	// pthread_mutex_unlock(&((*philo).m_print));
	// ft_msleep(1);
	// }
}

void	alone(t_phi *phi)
{
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
