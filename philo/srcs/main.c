/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:58:18 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/26 00:15:48 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

int	main(int argc, char **argv)
{
	t_phi	phi;

	if (check_args(argc, argv) == FAILURE)
		return (FAILURE);
	phi = (t_phi){0};
	init_phi(&phi, argv);
	
	if (init_mutex(&phi) == FAILURE)
		return (destroy_mutex, FAILURE);
		
	create_thread_manager(&phi);
	create_thread(&phi);
	join_thread(&phi);
	if (phi.nb_philo == 1)
		alone;
	else 
		manager(phi);	
	
	
	destroy_mutex(&phi);
	return (SUCCESS);
}

void	init_phi(t_phi *phi, char **argv)
{
	(*phi).nb_philo = ft_atoll(argv[1]);
	if (argv[5])
		(*phi).must_eat = ft_atoll(argv[5]);
	else
		(*phi).must_eat = -1;
	(*phi).time_to_die = ft_atoll(argv[2]);
	(*phi).time_to_eat = ft_atoll(argv[3]);
	(*phi).time_to_sleep = ft_atoll(argv[4]);
}

// void	init_phi(t_phi *phi, char **argv)
// {
// 	int	i;

// 	(*phi).nb_philo = ft_atoll(argv[1]);
// 	if (argv[5])
// 		(*phi).must_eat = ft_atoll(argv[5]);
// 	else
// 		(*phi).must_eat = -1;
// 	i = 0;
// 	while (i <= (*phi).nb_philo)
// 	{

// 		(*phi).time_to_die = ft_atoll(argv[2]);
// 		(*phi).time_to_eat = ft_atoll(argv[3]);
// 		(*phi).time_to_sleep = ft_atoll(argv[4]);
// 		(*phi).philo[i].is_dead = &((*phi).all_dead);

// 		// (*phi).philo[i].start = gettime_ms();
// 		// (*phi).philo[i].last_meal = gettime_ms();
// 		// (*phi).philo[i].id = i;
// 		i++;
// 	}
// }
