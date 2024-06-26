/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:58:18 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/26 03:54:40 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

int	main(int argc, char **argv)
{
	t_phi	phi;

	if (check_args(argc, argv) == FAILURE)
		return (FAILURE);
	// phi = (t_phi){0};
	init_phi(&phi, argv);	
	if (init_mutex(&phi) == FAILURE)
		return (destroy_mutex, FAILURE);
		
	create_thread_manager(&phi);
	create_thread(&phi);
	join_thread(&phi);
	if (phi.nb_philo == 1)
		alone;
	else 
		manager(&phi);	
	
	
	destroy_mutex(&phi);
	return (SUCCESS);
}

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (putstr_fd(ERR_ARG, 2), putstr_fd(USAGE, 2), FAILURE);
	return (check_argv(argv));
}

int	check_argv(char **argv)
{
	if (ft_atoll(argv[1]) <= 0)
		return (putstr_fd(MIN_NBP, 2), FAILURE);
	if (ft_atoll(argv[1]) > MAX)
		return (putstr_fd(MAX_NBP, 2), FAILURE);
	if (ft_atoll(argv[2]) < 0)
		return (putstr_fd(ERR_TTD, 2), FAILURE);
	if (ft_atoll(argv[3]) < 0)
		return (putstr_fd(ERR_TTE, 2), FAILURE);
	if (ft_atoll(argv[4]) < 0)
		return (putstr_fd(ERR_TTS, 2), FAILURE);
	if (argv[5] && ft_atoll(argv[5]) < 0)
		return (putstr_fd(ERR_TME, 2), FAILURE);
	return (SUCCESS);
}



