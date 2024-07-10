/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:58:18 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/10 03:45:40 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_phi	phi;
	t_philo	*philo;

	if (check_args(argc, argv) == KO)
		return (KO);
	// printf("sizeof(t_philo) = %ld\n", sizeof(t_philo));
	// pid = ft_calloc(ft_atoll(argv[1]), sizeof(pid_t));
	philo = ft_calloc(ft_atoll(argv[1]), sizeof(t_philo));
	if (!philo)
		return (KO);
	// phi = (t_phi){0};
	if (init_phi(&phi, philo, argv) == OK)
	{
		create_philos(&phi);
		if (wait_dead(phi) == OK)
		{
			sem_close(phi.s_forks);
			sem_close(phi.s_print);
			sem_close(phi.s_meal);
			sem_close(phi.s_dead);
			sem_unlink(S_FORKS);
			sem_unlink(S_PRINT);
			sem_unlink(S_DEAD);
			sem_unlink(S_MEAL);
			return (free(philo), OK);
		}
	}
	else
		return (free(philo), KO);
}

//
int	wait_dead(t_phi phi)
{
	int	status;
	int	i;

	while (1)
	{
		if (waitpid(-1, &status, 0) != -1)
		{
			i = 0;
			while (i < phi.nb_philo)
			{
				printf("pid %d = %d\n", i, phi.philos[i].pid);
				printf("kill %d = %d\n", i, kill(phi.philos[i].pid, SIGKILL));
				i++;
			}
		}
		return (OK);
	}
	// if (WIFEXITED(status))
	// {
	// 	if (WEXITSTATUS(status) == OK)
	// 	{
	// 		return (OK);
	// 	}
	// }
	return (KO);
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

// void	free_phi(t_philo *philos, pthread_mutex_t *forks)
// {
// 	free(philos);
// 	free(forks);
// }

// // if (nb_philo == 1)
// // 		alone(&phi);
// void	alone(t_phi *phi)
// {
// 	print_log(&((*phi).philos[0]), FORKING);
// 	ft_msleep((*phi).philos[0].time_to_die);
// 	print_log(&((*phi).philos[0]), DIED);
// }
