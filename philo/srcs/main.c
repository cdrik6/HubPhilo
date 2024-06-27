/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:58:18 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/28 01:05:42 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

// phi = (t_phi){0};
int	main(int argc, char **argv)
{
	t_phi			phi;
	t_philo			philo[MAX_PHILO];
	pthread_mutex_t	fork[MAX_PHILO];
	int				nb_philo;

	if (check_args(argc, argv) == FAILURE)
		return (FAILURE);
	nb_philo = ft_atoll(argv[1]);
	if (init_phi(&phi, philo, argv) == SUCCESS && init_forks(fork,
			nb_philo) == SUCCESS)
	{
		init_philo(&phi, philo, fork, argv);
		if (nb_philo == 1)
			alone(&phi);
		else if (create_thread(&phi) == SUCCESS && join_thread(&phi) == SUCCESS)
			monitor(&phi);
	}
	return (destroy_mutex(&phi, fork));
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
	if (ft_atoll(argv[1]) > MAX_PHILO)
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
