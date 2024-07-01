/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:58:18 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/01 06:14:03 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

// phi = (t_phi){0};
// printf("%lld", ft_atoll(argv[2]));
// if (create_thread(&phi) == OK)
int	main(int argc, char **argv)
{
	t_phi			phi;
	t_philo			philos[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];
	int				issue_id;
	// int				nb_philo;
	
	if (check_args(argc, argv) == KO)
		return (KO);
	issue_id = 1;
	// nb_philo = ft_atoll(argv[1]);
	// if (init_phi(&phi, philos, argv) == OK && init_forks(forks, nb_philo) == OK)
	if (init_phi(&phi, philos, forks, argv) == OK)
	{
		init_philos(&phi, philos, forks, argv);
		issue_id = create_thread(&phi);
		if (issue_id == 0)
			monitor(&phi);
	}
	join_thread(&phi, issue_id);
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

// if (nb_philo == 1)
// 		alone(&phi);
void	alone(t_phi *phi)
{
	print_log(&((*phi).philos[0]), FORKING);
	ft_msleep((*phi).philos[0].time_to_die);
	print_log(&((*phi).philos[0]), DIED);
}
