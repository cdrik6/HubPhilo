/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 00:29:37 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/19 19:27:32 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// struct timeval {
//     time_t      tv_sec;  // seconds since the Epoch
//     suseconds_t tv_usec; // microseconds
// };
// int gettimeofday(struct timeval *tv, struct timezone *tz);
// printf("%ld\n", t.tv_sec * 1000 + t.tv_usec / 1000);
long	gettime_ms(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		printf("philo: gettimeofday error");
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	ft_msleep(long ms)
{
	long	start;

	start = gettime_ms();
	while ((gettime_ms() - start) < ms)
		usleep(500);
}

void	dead_msleep(long ms, t_philo *philo)
{
	long	start;

	start = gettime_ms();
	while ((gettime_ms() - start) < ms && is_dead(philo) == 0)
		usleep(500);
}

void	print_log(t_philo *philo, char *str)
{
	if (is_dead(philo) == 0)
	{
		pthread_mutex_lock((*philo).m_print);
		printf("%ld %d %s\n", gettime_ms() - (*philo).start, (*philo).id, str);
		pthread_mutex_unlock((*philo).m_print);
	}
}

void	eating_alone(t_philo *philo)
{
	pthread_mutex_lock((*philo).right_fork);
	print_log(philo, FORKING);
	pthread_mutex_unlock((*philo).right_fork);
}
