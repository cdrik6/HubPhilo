/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:32:11 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/25 00:37:23 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

// philo = phi.philo[i]
void	*routine(void *data)
{
	t_philo	*philo;
	int		starting;

	philo = (t_philo *)data;
	while (is_dead(philo) == 0)
	{
		pthread_mutex_lock(&((*philo).m_starting));
		starting = (*philo).starting;
		pthread_mutex_unlock(&((*philo).m_starting));
		if (starting == 1)
		{
			pthread_mutex_lock(&((*philo).m_starting));
			(*philo).starting = 0;
			pthread_mutex_unlock(&((*philo).m_starting));
			eating(philo);
			sleeping(philo);
			thinking(philo);
		}
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
	int	forks;

	pthread_mutex_lock(&((*philo).m_forks));
	forks = (*philo).forks;
	pthread_mutex_unlock(&((*philo).m_forks));
	if (forks == 1 && is_dead(philo) == 0)
	// if (is_dead(philo) == 0)
	{
		pthread_mutex_lock(&((*philo).mutex));
		(*philo).eating = 1;
		pthread_mutex_unlock(&((*philo).mutex));
		//
		pthread_mutex_lock(&((*philo).m_meal));
		(*philo).nb_meal++;
		(*philo).last_meal = gettime_ms();
		pthread_mutex_unlock(&((*philo).m_meal));
		//
		print_log(philo, EATING);
		//
		ft_msleep((*philo).time_to_eat);
		//
		pthread_mutex_lock(&((*philo).mutex));
		(*philo).eating = 0;
		(*philo).sleeping = 0;
		pthread_mutex_unlock(&((*philo).mutex));
	}
}

void	sleeping(t_philo *philo)
{
	// is_dead(philo);
	// if ((*philo).sleeping == 0 && (*philo).is_dead == 0
	//	&& is_over(philo) == 0)
	// if ((*philo).sleeping == 0 && is_dead(philo) == 0 && is_over(philo) == 0)
	if ((*philo).sleeping == 0 && is_over(philo) == 0)
	{
		pthread_mutex_lock(&((*philo).mutex));
		(*philo).sleeping = 1;
		(*philo).thinking = 0;
		pthread_mutex_unlock(&((*philo).mutex));
		// pthread_mutex_lock(&((*philo).m_print));
		print_log(philo, SLEEPING);
		// pthread_mutex_unlock(&((*philo).m_print));
		//
		ft_msleep((*philo).time_to_sleep);
		//
		// pthread_mutex_lock(&((*philo).mutex));
		// (*philo).thinking = 0;
		// pthread_mutex_unlock(&((*philo).mutex));
	}
}

void	thinking(t_philo *philo)
{
	// is_dead(philo);
	// if ((*philo).thinking == 0 && (*philo).is_dead == 0
	//	&& is_over(philo) == 0)
	// if ((*philo).thinking == 0 && is_dead(philo) == 0 && is_over(philo) == 0)
	if ((*philo).thinking == 0 && is_over(philo) == 0)
	{
		pthread_mutex_lock(&((*philo).mutex));
		(*philo).thinking = 1;
		pthread_mutex_unlock(&((*philo).mutex));
		// pthread_mutex_lock(&((*philo).m_print));
		print_log(philo, THINKING);
		// pthread_mutex_unlock(&((*philo).m_print));
		// ft_msleep(1);
	}
}

int	is_to_die(t_philo *philo)
{
	pthread_mutex_lock(&((*philo).m_meal));
	if ((gettime_ms() - (*philo).last_meal) > (*philo).time_to_die)
	{
		pthread_mutex_unlock(&((*philo).m_meal));
		return (1);
	}
	pthread_mutex_unlock(&((*philo).m_meal));
	return (0);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&((*philo).m_is_dead));
	if (*((*philo).is_dead) == 1)
	{
		pthread_mutex_unlock(&((*philo).m_is_dead));
		return (1);
	}
	pthread_mutex_unlock(&((*philo).m_is_dead));
	return (0);
}

int	is_over(t_philo *philo)
{
	pthread_mutex_lock(&((*philo).m_is_over));
	if ((*philo).is_over == 1)
	{
		pthread_mutex_unlock(&((*philo).m_is_over));
		return (1);
	}
	pthread_mutex_unlock(&((*philo).m_is_over));
	return (0);
}

// int	is_over(t_philo *philo)
// {
// 	if ((*philo).must_eat == -1)
// 		return (0);
// 	if ((*philo).nb_meal >= (*philo).must_eat)
// 	{
// 		pthread_mutex_lock(&((*philo).mutex));
// 		(*philo).is_over = 1;
// 		pthread_mutex_unlock(&((*philo).mutex));
// 		return (1);
// 	}
// 	return (0);
// }
