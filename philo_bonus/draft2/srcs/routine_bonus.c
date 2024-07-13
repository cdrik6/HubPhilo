/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:32:11 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/12 05:23:27 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if ((*philo).id % 2 == 0)
		ft_msleep(1);
	// while (1)
	while (is_dead(philo) == 0)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	// }
	// printf("sizeof(t_philo) = %ld\n", sizeof(t_philo));
	// sem_wait((*phi).s_print);
	// printf("id = %d\n", (*philo).id);
	// sem_post((*phi).s_print);
	// print_log(phi, philo, DIED);
	// sem_close(*((*philo).s_forks));
	// sem_close(*((*philo).s_print));
	// sem_close(*((*philo).s_meal));
	// sem_close(*((*philo).s_dead));
	// sem_unlink(S_FORKS);
	// sem_unlink(S_PRINT);
	// sem_unlink(S_DEAD);
	// sem_unlink(S_MEAL);
	// free((*phi).philos);
	// exit((*philo).pid);
	// exit(OK);
	// pthread_join((*philo).thread, NULL);
	// pthread_detach((*philo).thread);
	return (data);
	// return(NULL);
}

void	eating(t_philo *philo)
{
	sem_wait(*(*philo).s_forks);
	if (is_dead(philo) == 1)
		return;
	print_log(philo, FORKING);
	//	
	sem_wait(*(*philo).s_forks);
	if (is_dead(philo) == 1)
		return;
	print_log(philo, FORKING);
	//
	print_log(philo, EATING);
	//
	sem_wait(*(*philo).s_meal);
	(*philo).nb_meal++;
	(*philo).last_meal = gettime_ms();
	sem_post(*(*philo).s_meal);
	//
	ft_msleep((*philo).time_to_eat);
	sem_post(*(*philo).s_forks);
	sem_post(*(*philo).s_forks);
}

void	sleeping(t_philo *philo)
{
	if (is_dead(philo) == 0)
	{
		print_log(philo, SLEEPING);
		ft_msleep((*philo).time_to_sleep);
	}	
}

void	thinking(t_philo *philo)
{
	if (is_dead(philo) == 0)
	{
		print_log(philo, THINKING);
		ft_msleep((*philo).time_to_eat - (*philo).time_to_sleep + 1);
	}
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
