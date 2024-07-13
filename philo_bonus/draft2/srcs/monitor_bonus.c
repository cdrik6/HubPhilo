/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 22:59:31 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/12 05:21:21 by caguillo         ###   ########.fr       */
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

// void	monitor(t_phi *phi, t_philo *philo, pthread_t *threads)
// void	monitor(t_phi *phi, t_philo *philo)
void	monitor(t_philo *philo)
{
	// t_philo *philo;

	// philo = (t_philo *)data;
	while (1)
	{
		// if (is_a_dead(phi) == 1 || is_all_over(phi) == 1)
		if (is_to_die(philo) == 1)
		{
			// // printf("dead: id = %d\n", (*philo).id);
			// sem_wait(*((*philo).s_dead));
			// (*philo).dead = 1;
			// sem_post(*((*philo).s_dead));
			break ;
		}
		//usleep(10);
	}	
	// // // 
	// // // pthread_join((*philo).thread, NULL);
	// sem_close(*((*philo).s_forks));
	// sem_close(*((*philo).s_print));
	// sem_close(*((*philo).s_meal));
	// sem_close(*((*philo).s_dead));
	// // sem_unlink(S_FORKS);
	// // sem_unlink(S_PRINT);
	// // sem_unlink(S_DEAD);
	// // sem_unlink(S_MEAL);
	// // // pthread_detach((*philo).thread);	
	// // free((*phi).philos);
	// // pthread_detach(threads[(*philo).id - 1]);
	// // free(threads);
	// exit((*philo).pid);
	// // // kill((*philo).pid, SIGKILL);	
	// exit(0);
	// pthread_join((*philo).thread, NULL);
	// return(data);
}

// printf("%d", (gettime_ms() - (*philo).last_meal) > (*philo).time_to_die);
int	is_to_die(t_philo *philo)
{
	sem_wait(*((*philo).s_meal));
	if ((gettime_ms() - (*philo).last_meal) > (*philo).time_to_die)
	{
		sem_post(*((*philo).s_meal));
		print_log(philo, DIED);
		//sem_wait(*((*philo).s_print));
		sem_wait(*((*philo).s_dead));
		(*philo).dead = 1;
		sem_post(*((*philo).s_dead));
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
