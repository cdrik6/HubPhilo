/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 22:59:31 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/11 23:58:04 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// int	is_a_dead(t_phi *phi)
// {
// 	int	i;

// 	i = 0;
// 	while (i < (*phi).nb_philo)
// 	{
// 		if (is_to_die(phi, &((*phi).philos[i])) == 1)
// 		{
// 			print_log(phi, &((*phi).philos[i]), DIED);
// 			sem_wait((*phi).s_dead);
// 			*((*phi).philos[i].dead) = 1;
// 			sem_post((*phi).s_dead);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	is_all_over(t_phi *phi)
// {
// 	int	i;

// 	if ((*phi).must_eat == -1)
// 		return (0);
// 	i = 0;
// 	while (i < (*phi).nb_philo)
// 	{
// 		pthread_mutex_lock(&((*phi).m_meal));
// 		if ((*phi).philos[i].nb_meal < (*phi).must_eat)
// 			return (pthread_mutex_unlock(&((*phi).m_meal)), 0);
// 		pthread_mutex_unlock(&((*phi).m_meal));
// 		i++;
// 	}
// 	pthread_mutex_lock(&((*phi).m_dead));
// 	(*phi).is_dead = 1;
// 	pthread_mutex_unlock(&((*phi).m_dead));
// 	return (1);
// }

void	*monitor(void *data)
{
	t_phi	*phi;
	int		i;
	int		stop;

	phi = (t_phi *)data;
	
	stop = 0;
	while (1)
	{
		i = 0;
		
		while (i < (*phi).nb_philo)
		{
			// if (is_a_dead(phi) == 1 || is_all_over(phi) == 1)
			if (is_to_die(&(*phi).philos[i]) == 1)
			{
				// printf("dead: id = %d\n", (*philo).id);
				sem_wait((*phi).s_dead);
				*(*phi).philos[i].dead = 1;
				sem_post((*phi).s_dead);				
				stop = 1;
				break ;
			}
			i++;
		}
		if (stop == 1)
		{
			// sem_wait((*phi).s_dead);
			// printf("%d\n", *(*phi).philos[i].dead);
			// sem_post((*phi).s_dead);
			
			break ;
		}
			
		usleep(100);
	}
	// // free((*phi).philos);
	// sem_close(*((*philo).s_forks));
	// sem_close(*((*philo).s_print));
	// sem_close(*((*philo).s_meal));
	// sem_close(*((*philo).s_dead));
	// // sem_unlink(S_FORKS);
	// // sem_unlink(S_PRINT);
	// // sem_unlink(S_DEAD);
	// // sem_unlink(S_MEAL);
	// exit((*philo).pid);
	// // kill((*philo).pid, SIGKILL);	
	return (data);
	// return (NULL);
}

// printf("%d", (gettime_ms() - (*philo).last_meal) > (*philo).time_to_die);
int	is_to_die(t_philo *philo)
{
	sem_wait(*((*philo).s_meal));
	if ((gettime_ms() - (*philo).last_meal) > (*philo).time_to_die)
	{
		sem_post(*((*philo).s_meal));
		print_log(philo, DIED);
		return (1);
	}
	sem_post(*((*philo).s_meal));
	return (0);
}

int	is_dead(t_philo *philo)
{
	sem_wait(*(*philo).s_dead);
	if (*(*philo).dead == 1)
	{
		sem_post(*(*philo).s_dead);
		return (1);
	}
	sem_post(*(*philo).s_dead);
	return (0);
}
