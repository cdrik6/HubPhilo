/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 00:29:37 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/13 05:30:15 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
		perror("philo: gettimeofday");
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	ft_msleep(long ms)
{
	long	start;

	start = gettime_ms();
	while ((gettime_ms() - start) < ms)
		usleep(500);
}

void	print_log(t_philo *philo, char *str)
{
	
	if (is_dead(philo) == 0)
	{
		sem_wait(*(*philo).s_stop);
		sem_wait(*((*philo).s_print));
		printf("%ld %d %s\n", gettime_ms() - (*philo).start, (*philo).id, str);
		sem_post(*((*philo).s_print));
		sem_post(*(*philo).s_stop);
	}
	
}

// void	eating_alone(t_philo *philo)
// {
// 	pthread_mutex_lock((*philo).right_fork);
// 	print_log(philo, FORKING);
// 	pthread_mutex_unlock((*philo).right_fork);
// }
// // ft_msleep((*philo).time_to_die);
// // print_log(philo, DIED);
