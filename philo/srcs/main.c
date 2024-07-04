/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:58:18 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/04 23:56:53 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

// phi = (t_phi){0};
// printf("%lld", ft_atoll(argv[2]));
// if (create_thread(&phi) == OK)
// int				nb_philo;
// nb_philo = ft_atoll(argv[1]);
// if (init_phi(&phi, philos, argv) == OK && init_forks(forks, nb_philo) == OK)
// issue_id = 1;
// t_philo			philos[MAX_PHILO];
// pthread_mutex_t	forks[MAX_PHILO];
int	main(int argc, char **argv)
{
	t_phi			phi;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				mut_id;

	if (check_args(argc, argv) == KO)
		return (KO);
	philos = ft_calloc(ft_atoll(argv[1]), sizeof(t_philo));
	if (!philos)
		return (KO);
	forks = ft_calloc(ft_atoll(argv[1]), sizeof(pthread_mutex_t));
	if (!forks)
		return (free(philos), KO);
	mut_id = init_phi(&phi, philos, forks, argv);
	if (mut_id == 0)
		return(philosopher(&phi, philos, forks, argv));
	else
	{
		destroy_mutex_id(&phi, forks, mut_id);
		return (free_phi(philos, forks), KO);
	}
	return (OK);
}

int	philosopher(t_phi *phi, t_philo *philos, pthread_mutex_t *forks,
		char **argv)
{
	int	issue_id;

	init_philos(phi, philos, forks, argv);
	issue_id = create_thread(phi);
	if (issue_id == 0)
		monitor(phi);
	join_thread(phi, issue_id);
	if (destroy_mutex(phi, forks) == KO)
		return (free_phi(philos, forks), KO);
	return (free_phi(philos, forks), OK);
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
	if (ft_atoll(argv[2]) > INT_MAX)
		return (putstr_fd(ERR_TTD, 2), KO);
	if (ft_atoll(argv[3]) < 0)
		return (putstr_fd(ERR_TTE, 2), KO);
	if (ft_atoll(argv[3]) > INT_MAX)
		return (putstr_fd(ERR_TTE, 2), KO);
	if (ft_atoll(argv[4]) < 0)
		return (putstr_fd(ERR_TTS, 2), KO);
	if (ft_atoll(argv[4]) > INT_MAX)
		return (putstr_fd(ERR_TTS, 2), KO);
	if (argv[5] && ft_atoll(argv[5]) < 0)
		return (putstr_fd(ERR_TME, 2), KO);
	if (argv[5] && ft_atoll(argv[5]) > INT_MAX)
		return (putstr_fd(ERR_TME, 2), KO);
	return (OK);
}

void	free_phi(t_philo *philos, pthread_mutex_t *forks)
{
	free(philos);
	free(forks);
}

// // if (nb_philo == 1)
// // 		alone(&phi);
// void	alone(t_phi *phi)
// {
// 	print_log(&((*phi).philos[0]), FORKING);
// 	ft_msleep((*phi).philos[0].time_to_die);
// 	print_log(&((*phi).philos[0]), DIED);
// }
