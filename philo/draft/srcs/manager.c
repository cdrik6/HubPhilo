/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 22:59:31 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/25 19:47:06 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

int	is_a_dead(t_phi *phi)
{
	int	i;

	// int dead;
	i = 1;
	while (i <= (*phi).nb_philo)
	{
		if (is_to_die(&((*phi).philo[i])) == 1)
		{
			print_log(&((*phi).philo[i]), DIED);
			pthread_mutex_lock(&((*phi).philo[i].m_is_dead));
			*((*phi).philo[i].is_dead) = 1;
			pthread_mutex_unlock(&((*phi).philo[i].m_is_dead));
			// //
			// i = 0;
			// while (i <= (*phi).nb_philo)
			// {
			// 	printf("%d is dead = %d\n", (*phi).philo[i].id,
			// 		*((*phi).philo[i].is_dead));
			// 	i++;
			// }
			// //
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_all_over(t_phi *phi)
{
	int	i;
	int	nb_meal;

	if ((*phi).must_eat == -1)
		return (0);
	i = 1;
	while (i <= (*phi).nb_philo)
	{
		pthread_mutex_lock(&((*phi).philo[i].m_meal));
		nb_meal = (*phi).philo[i].nb_meal;
		pthread_mutex_unlock(&((*phi).philo[i].m_meal));
		if (nb_meal < (*phi).must_eat)
			return (0);
		i++;
	}
	i = 1;
	while (i <= (*phi).nb_philo)
	{
		pthread_mutex_lock(&((*phi).philo[i].m_is_over));
		(*phi).philo[i].is_over = 1;
		pthread_mutex_unlock(&((*phi).philo[i].m_is_over));
		i++;
	}
	return (1);
}

void	*manager(void *data)
{
	t_phi	*phi;
	int		ready;

	phi = (t_phi *)data;
	ready = 0;
	if ((*phi).nb_philo == 1)
	{
		alone(phi);
		return (data);
	}
	while (ready != (*phi).nb_philo + 1)
	{
		usleep(100);
		pthread_mutex_lock(&((*phi).philo[0].mutex));
		ready = (*phi).ready;
		pthread_mutex_unlock(&((*phi).philo[0].mutex));
		// printf("%d\n", ready);
	}
	printf("%d\n", ready);
	while (is_a_dead(phi) == 0 && is_all_over(phi) == 0)
	{
		// if (is_a_dead(phi) != 0 || is_all_over(phi) != 0)
		// 	break ;
		// printf("ici\n");
		// usleep(100);
		allocate_forks(phi);
		// ft_msleep((*phi).philo[0].time_to_eat);
	}
	return (data);
}

void	alone(t_phi *phi)
{
	print_log(&((*phi).philo[1]), FORKING);
	ft_msleep((*phi).philo[1].time_to_die);
	print_log(&((*phi).philo[1]), DIED);
	pthread_mutex_lock(&((*phi).philo[1].m_is_dead));
	*((*phi).philo[1].is_dead) = 1;
	pthread_mutex_unlock(&((*phi).philo[1].m_is_dead));
}

/*
int	one_eating(t_phi *phi)
{
	int	i;

	i = 1;
	while (i <= (*phi).nb_philo)
	{
		pthread_mutex_lock(&((*phi).philo[0].mutex));
		if (is_to_die(&((*phi).philo[i])) == 1)
		{
			pthread_mutex_lock(&((*phi).philo[i].m_is_dead));
			*((*phi).philo[i].is_eating) = 1;
			pthread_mutex_unlock(&((*phi).philo[i].m_is_dead));
			// //
			// i = 0;
			// while (i <= (*phi).nb_philo)
			// {
			// 	printf("%d is dead = %d\n", (*phi).philo[i].id,
			// 		*((*phi).philo[i].is_dead));
			// 	i++;
			// }
			// //
			return (1);
		}
		i++;
	}
	return (0);
}
*/