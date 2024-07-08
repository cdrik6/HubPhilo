/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:13:26 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/08 04:00:46 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	init_phi(t_phi *phi, t_philo *philos, char **argv)
{
	(*phi).philos = philos;
	(*phi).nb_philo = ft_atoll(argv[1]);
	(*phi).time_to_die = ft_atoll(argv[2]);
	(*phi).time_to_eat = ft_atoll(argv[3]);
	(*phi).time_to_sleep = ft_atoll(argv[4]);
	if (argv[5])
		(*phi).must_eat = ft_atoll(argv[5]);
	else
		(*phi).must_eat = -1;
	(*phi).is_dead = 0;
	return (init_sem(phi));
}

// 0600 = R + W for USER (0666 for all)
int	init_sem(t_phi *phi)
{
	sem_unlink(S_FORKS);
	sem_unlink(S_PRINT);
	sem_unlink(S_DEAD);
	sem_unlink(S_MEAL);
	(*phi).s_forks = sem_open(S_FORKS, O_CREAT | O_EXCL, 0600, (*phi).nb_philo);
	if ((*phi).s_forks == SEM_FAILED)
		return (perror("sem_open forks"), KO);
	(*phi).s_print = sem_open(S_PRINT, O_CREAT | O_EXCL, 0600, 1);
	if ((*phi).s_print == SEM_FAILED)
		return (perror("sem_open print"), KO);
	(*phi).s_dead = sem_open(S_DEAD, O_CREAT | O_EXCL, 0600, 1);
	if ((*phi).s_dead == SEM_FAILED)
		return (perror("sem_open dead"), KO);
	(*phi).s_meal = sem_open(S_MEAL, O_CREAT | O_EXCL, 0600, 1);
	if ((*phi).s_meal == SEM_FAILED)
		return (perror("sem_open meal"), KO);
	return (OK);
}

// (*phi).philo[i] = (t_philo){0};
int	init_philos(t_phi *phi)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < (*phi).nb_philo)
	{
		pid = fork();
		(*phi).philos[i].id = i + 1;
		(*phi).philos[i].start = gettime_ms();
		(*phi).philos[i].last_meal = gettime_ms();
		(*phi).philos[i].nb_meal = 0;
		(*phi).philos[i].dead = &(*phi).is_dead;
		if (pid == -1)
			return (perror("fork"), KO);
		if (pid == 0)
		{
			routine(phi, &((*phi).philos[i]));
		}
		(*phi).philos[i].pid = pid;
		i++;
	}
}
