/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 23:32:31 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/25 00:47:27 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

// temp == 0 => noone eating
void	allocate_forks(t_phi *phi)
{
	int	i;
	int	eating;

	i = 1;
	eating = 0;
	while (i <= (*phi).nb_philo)
	{
		pthread_mutex_lock(&((*phi).philo[i].mutex));
		if ((*phi).philo[i].eating != 0)
		{
			pthread_mutex_unlock(&((*phi).philo[i].mutex));
			eating = 1;
			break ;
		}
		pthread_mutex_unlock(&((*phi).philo[i].mutex));
		i++;
	}
	if (eating == 0)
	{
		// printf("-------- allocate forks --------------\n");
		if ((*phi).nb_philo % 2 == 0)
			even_allocation(phi);
		else
			odd_allocation(phi);
		i = 1;
		while (i <= (*phi).nb_philo)
		{
			pthread_mutex_lock(&((*phi).philo[i].m_starting));
			//(*phi).philo[i].sleeping = 0;
			//(*phi).philo[i].thinking = 0;
			(*phi).philo[i].starting = 1;
			pthread_mutex_unlock(&((*phi).philo[i].m_starting));
			i++;
		}
	}
}

// pair
//(*phi).nb_philo - (*phi).nb_philo % 2 -->
//  pour gerer les cas impairs sans le dernier
void	even_allocation(t_phi *phi)
{
	int	i;

	i = 1;
	if ((*phi).philo[1].forks == 1)
	{
		while (i <= (*phi).nb_philo - (*phi).nb_philo % 2)
		{
			pthread_mutex_lock(&((*phi).philo[i].m_forks));
			(*phi).philo[i].forks = (i - 1) % 2;
			pthread_mutex_unlock(&((*phi).philo[i].m_forks));
			if ((i - 1) % 2 == 1)
			{
				// pthread_mutex_lock(&((*phi).philo[i].m_print));
				print_log(&((*phi).philo[i]), FORKING);
				print_log(&((*phi).philo[i]), FORKING);
				// pthread_mutex_unlock(&((*phi).philo[i].m_print));
			}
			pthread_mutex_lock(&((*phi).philo[i].mutex));
			(*phi).philo[i].eating = (i - 1) % 2;
			pthread_mutex_unlock(&((*phi).philo[i].mutex));
			i++;
		}
	}
	else
	{
		while (i <= (*phi).nb_philo - (*phi).nb_philo % 2)
		{
			pthread_mutex_lock(&((*phi).philo[i].m_forks));
			(*phi).philo[i].forks = i % 2;
			pthread_mutex_unlock(&((*phi).philo[i].m_forks));
			if (i % 2 == 1)
			{
				// pthread_mutex_lock(&((*phi).philo[i].m_print));
				print_log(&((*phi).philo[i]), FORKING);
				print_log(&((*phi).philo[i]), FORKING);
				// pthread_mutex_unlock(&((*phi).philo[i].m_print));
			}
			pthread_mutex_lock(&((*phi).philo[i].mutex));
			(*phi).philo[i].eating = i % 2;
			pthread_mutex_unlock(&((*phi).philo[i].mutex));
			i++;
		}
	}
}

int	is_last(t_phi *phi)
{
	int	last;
	int	i;
	int	n;

	n = (*phi).nb_philo;
	last = 1;
	i = 1;
	while (i <= (*phi).nb_philo - 1)
	{
		pthread_mutex_lock(&((*phi).philo[i].m_meal));
		// printf("n meal %d\n", (*phi).philo[n].nb_meal);
		// printf("%d meal %d\n", i, (*phi).philo[i].nb_meal);
		if ((*phi).philo[n].nb_meal >= (*phi).philo[i].nb_meal)
		{
			last = 0;
			pthread_mutex_unlock(&((*phi).philo[i].m_meal));
			break ;
		}
		pthread_mutex_unlock(&((*phi).philo[i].m_meal));
		i++;
	}
	return (last);
}

void	odd_allocation(t_phi *phi)
{
	int	i;
	int	n;

	n = (*phi).nb_philo;
	if (is_last(phi) == 1)
	{
		// printf("ici\n");
		pthread_mutex_lock(&((*phi).philo[n].m_forks));
		(*phi).philo[n].forks = 1;
		pthread_mutex_unlock(&((*phi).philo[n].m_forks));
		// pthread_mutex_lock(&((*phi).philo[n].m_print));
		print_log(&((*phi).philo[n]), FORKING);
		print_log(&((*phi).philo[n]), FORKING);
		// pthread_mutex_unlock(&((*phi).philo[n].m_print));
		i = 1;
		while (i < (*phi).nb_philo)
		{
			pthread_mutex_lock(&((*phi).philo[i].m_forks));
			(*phi).philo[i].forks = 0;
			pthread_mutex_unlock(&((*phi).philo[i].m_forks));
			i++;
		}
	}
	else
	{
		// printf("la\n");
		pthread_mutex_lock(&((*phi).philo[n].m_forks));
		(*phi).philo[n].forks = 0;
		pthread_mutex_unlock(&((*phi).philo[n].m_forks));
		even_allocation(phi);
	}
}

// if (temp == 0)
// {
// 	i = 1;
// 	if ((*phi).philo[1].forks == 0)
// 	{
// 		if ((*phi).philo[n].forks == 0)
// 		{
// 			if ((*phi).philo[n].nb_meal < (*phi).philo[1].nb_meal)
// 				(*phi).philo[n].forks = 1;
// 			else
// 				(*phi).philo[1].forks = 1;
// 		}
// 		else if ((*phi).philo[2].forks == 0)
// 		{
// 			if ((*phi).philo[1].nb_meal < (*phi).philo[2].nb_meal)
// 				(*phi).philo[1].forks = 1;
// 			else
// 				(*phi).philo[2].forks = 1;
// 		}
// 		else
// 			(*phi).philo[1].forks = 1;
// 	}
// 	//
// 	i = 1;
// 	while (i <= (*phi).nb_philo)
// 	{
// 		if ((*phi).philo[i].forks == 0)
// 		{
// 			if (i == 1)
// 				j = (*phi).nb_philo;
// 			else
// 				j = i - 1;
// 			if ((*phi).philo[j].forks == 0)
// 			{
// 				if ((*phi).philo[j].nb_meal < (*phi).philo[i].nb_meal)
// 					(*phi).philo[j].forks = 1;
// 				else
// 					(*phi).philo[i].forks = 1;
// 			}
// 			else if ((*phi).philo[i + 1].forks == 0)
// 			{
// 				if ((*phi).philo[i].nb_meal < (*phi).philo[i + 1].nb_meal)
// 					(*phi).philo[i].forks = 1;
// 				else
// 					(*phi).philo[i + 1].forks = 1;
// 			}
// 			else
// 				(*phi).philo[i].forks = 1;
// 		}
// 		i++;
// 	}
// }

// while (i <= (*phi).nb_philo)
// 	{
// 		pthread_mutex_lock(&((*phi).philo[i].mutex));
// 		eating = eating + (*phi).philo[i].eating;
// 		pthread_mutex_unlock(&((*phi).philo[i].mutex));
// 		i++;
// }
