/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:58:12 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/19 19:31:08 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	create_thread(t_philo *philo)
{
	if (pthread_create(&(*philo).thread, NULL, &monitor, philo) != 0)
	{
		printf("philo: pthread_create error");
		return (KO);
	}
	return (OK);
}
