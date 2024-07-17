/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:32:11 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/17 21:12:23 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	routine(t_phi *phi, t_philo *philo)
{
	if ((*philo).id % 2 == 0)
		ft_msleep(1);
	// dead_msleep((*phi).time_to_eat + 1, philo);
	// ft_msleep(10);
	// if ((*philo).nb_philo % 2 == 1 && (*philo).id == (*philo).nb_philo)
	// 	dead_msleep((*phi).time_to_eat + 1, philo);
	while (is_dead(philo) == 0 && is_over(philo) == 0)	
	{
		eating(phi, philo);
		sleeping(phi, philo);
		thinking(philo);
	}
}

void	eating(t_phi *phi, t_philo *philo)
{
	sem_wait((*phi).s_forks);
	print_log(philo, FORKING);
	sem_wait((*phi).s_forks);
	print_log(philo, FORKING);
	print_log(philo, EATING);
	sem_wait((*phi).s_meal);
	//(*philo).nb_meal++;
	(*philo).last_meal = gettime_ms();
	sem_post((*phi).s_meal);
	dead_msleep((*phi).time_to_eat, philo);
	// ft_msleep((*phi).time_to_eat);
	sem_post((*phi).s_forks);
	sem_post((*phi).s_forks);
	sem_wait((*phi).s_meal);
	(*philo).nb_meal++;
	sem_post((*phi).s_meal);
}

// void	eating(t_phi *phi, t_philo *philo)
// {
// 	// printf("%d ici 1\n", (*philo).id);
// 	sem_wait((*phi).s_forks);
// 	// usleep(500);
// 	if (is_dead(philo) == 0)
// 	{
// 		// printf("%d ici 2\n", (*philo).id);
// 		/*****bloque ici**** */
// 		print_log(philo, FORKING);
// 		// printf("%d ici 3\n", (*philo).id);
// 		if (is_dead(philo) == 0)
// 			sem_wait((*phi).s_forks);
// 		// printf("%d ici 4\n", (*philo).id);
// 		if (is_dead(philo) == 0)
// 			print_log(philo, FORKING);
// 		// printf("%d ici 5\n", (*philo).id);
// 		if (is_dead(philo) == 0)
// 		{
// 			print_log(philo, EATING);
// 			// printf("%d ici 6\n", (*philo).id);
// 			sem_wait((*phi).s_meal);
// 			(*philo).nb_meal++;
// 			(*philo).last_meal = gettime_ms();
// 			sem_post((*phi).s_meal);
// 			// printf("%d ici 7\n", (*philo).id);
// 			dead_msleep((*phi).time_to_eat, philo);
// 			// printf("%d ici 8\n", (*philo).id);
// 			sem_post((*phi).s_forks);
// 		}
// 	}
// 	sem_post((*phi).s_forks);
// }

void	sleeping(t_phi *phi, t_philo *philo)
{
	if (is_dead(philo) == 0 && is_over(philo) == 0)
	{
		// if (is_over(philo) == 1)
		// 	return ;
		print_log(philo, SLEEPING);
		dead_msleep((*phi).time_to_sleep, philo);
		// ft_msleep((*phi).time_to_sleep);
	}
}

void	thinking(t_philo *philo)
{
	if (is_dead(philo) == 0 && is_over(philo) == 0)
	{
		print_log(philo, THINKING);
		// if ((*philo).nb_philo % 2 == 1 )
		//  	//ft_msleep((*philo).time_to_eat);
		//     dead_msleep((*philo).time_to_eat, philo);
		// else
		// 	ft_msleep(1);
		// dead_msleep((*philo).time_to_eat - (*philo).time_to_sleep+ 1,philo);
		// // ft_msleep(10);
		// //
		/*if ((*philo).time_to_eat - (*philo).time_to_sleep > 0)
		{
			dead_msleep((*philo).time_to_eat - (*philo).time_to_sleep + 1,
				philo);
		}
		else
		{
			//if ((*philo).id % 2 == 1)
				dead_msleep(1, philo);
			// ft_msleep(1);
		}*/
		
		if ((*philo).nb_philo % 2 == 1 && (*philo).id == (*philo).nb_philo)
			dead_msleep((*philo).time_to_eat, philo);
		else if ((*philo).nb_philo % 2 == 1	)
			dead_msleep((*philo).time_to_eat - (*philo).time_to_sleep + 1, philo);	
		else			
			usleep(500);
		
		// if ((*philo).nb_philo % 2 == 1 && (*philo).id == (*philo).nb_philo)
		// 	dead_msleep(10, philo);
		// 	//dead_msleep((*philo).time_to_eat, philo);
		// else
		// 	dead_msleep((*philo).time_to_eat - (*philo).time_to_sleep + 1, philo);
		
	}
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
