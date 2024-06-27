/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 00:29:37 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/28 01:12:09 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

void	putstr_fd(char *str, int fd)
{
	int	i;

	if (!str || fd < 0)
		return ;
	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	is_space(char c)
{
	if (9 <= c && c <= 13)
		return (1);
	if (c == 32)
		return (1);
	return (0);
}

long long	ft_atoll(char *str)
{
	int			i;
	int			sign;
	long long	nbr;

	if (!str)
		return (0);
	i = 0;
	sign = 1;
	nbr = 0;
	while (str[i] && is_space(str[i]) == 1)
		i++;
	while (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] && 48 <= str[i] && str[i] <= 57)
	{
		nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	return (sign * nbr);
}

void	print_log(t_philo *philo, char *str)
{
	pthread_mutex_lock((*philo).m_print);
	if (is_dead(philo) == 0)
		printf("%ld %d %s\n", gettime_ms() - (*philo).start, (*philo).id, str);
	pthread_mutex_unlock((*philo).m_print);
}

// struct timeval {
//     time_t      tv_sec;  // seconds since the Epoch
//     suseconds_t tv_usec; // microseconds
// };
// int gettimeofday(struct timeval *tv, struct timezone *tz);
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
