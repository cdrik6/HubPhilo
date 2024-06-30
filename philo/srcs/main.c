/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:58:18 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/30 04:32:55 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

// phi = (t_phi){0};
int	main(int argc, char **argv)
{
	t_phi			phi;
	t_philo			philos[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];
	int				nb_philo;

	//printf("%lld", ft_atoll(argv[2]));
	if (check_args(argc, argv) == KO)
		return (KO);
	nb_philo = ft_atoll(argv[1]);
	
	if (init_phi(&phi, philos, argv) == OK && init_forks(forks, nb_philo) == OK)
	{
		init_philos(&phi, philos, forks, argv);
		if (nb_philo == 1)
			alone(&phi);
		else if (create_thread(&phi) == OK)
		{
			monitor(&phi);
			join_thread(&phi);
		}
	}
	destroy_mutex(&phi, forks);
	return (OK);
}

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (putstr_fd(ERR_ARG, 2), putstr_fd(USAGE, 2), KO);
	if (ft_atoll(argv[1]) <= 0)
		return (putstr_fd(MIN_NBP, 2), KO);
	if (ft_atoll(argv[1]) > MAX_PHILO)
		return (putstr_fd(MAX_NBP, 2), KO);
	if (ft_atoll(argv[2]) < 0)
		return (putstr_fd(ERR_TTD, 2), KO);
	if (ft_atoll(argv[3]) < 0)
		return (putstr_fd(ERR_TTE, 2), KO);
	if (ft_atoll(argv[4]) < 0)
		return (putstr_fd(ERR_TTS, 2), KO);
	if (argv[5] && ft_atoll(argv[5]) < 0)
		return (putstr_fd(ERR_TME, 2), KO);
	return (OK);
}

void	alone(t_phi *phi)
{
	print_log(&((*phi).philos[0]), FORKING);
	ft_msleep((*phi).philos[0].time_to_die);
	print_log(&((*phi).philos[0]), DIED);
}
