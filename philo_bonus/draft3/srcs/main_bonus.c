/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:58:18 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/17 20:56:32 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_phi	phi;
	t_philo	*philos;

	if (check_args(argc, argv) == KO)
		return (KO);
	philos = ft_calloc(ft_atoll(argv[1]), sizeof(t_philo));
	if (!philos)
		return (KO);
	if (init_phi(&phi, philos, argv) == OK)
	{
		create_philos(&phi);
		if (wait_dead(phi) == OK)
		{
			// sem_post(phi.s_stop);
			sem_close(phi.s_forks);
			sem_close(phi.s_print);
			sem_close(phi.s_meal);
			sem_close(phi.s_dead);
			sem_close(phi.s_stop);
			sem_unlink(S_FORKS);
			sem_unlink(S_PRINT);
			sem_unlink(S_DEAD);
			sem_unlink(S_MEAL);
			sem_unlink(S_STOP);
			free(philos);
		}
		return (OK);
	}
	else
		return (free(philos), KO);
}

// printf("pid %d = %d\n", i + 1, phi.philos[i].pid);
// printf("kill %d = %d\n", i+ 1,kill(phi.philos[i].pid, SIGKILL));
// printf("status =%d\n", WEXITSTATUS(status));
int	wait_dead(t_phi phi)
{
	int	status;
	int	i;
	int	k;

	while (1)
	{
		if (waitpid(-1, &status, 0) != -1)
		{
			if (WEXITSTATUS(status) == 1)
			{
				i = 0;
				while (i < phi.nb_philo)
				{
					if (kill(phi.philos[i].pid, SIGKILL) == -1)
						k = i;
					i++;
				}
				printf("%ld %d %s\n", gettime_ms() - (phi).start,
					phi.philos[k].id, DIED);
			}
			return (OK);
		}
	}
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
