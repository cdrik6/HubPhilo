/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:13:26 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/17 01:08:47 by caguillo         ###   ########.fr       */
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
	// (*phi).is_dead = 0;
	(*phi).start = gettime_ms();
	return (init_sem(phi));
}

// 0600 = R + W for USER (0666 for all)
int	init_sem(t_phi *phi)
{
	sem_unlink(S_FORKS);
	sem_unlink(S_PRINT);
	sem_unlink(S_DEAD);
	sem_unlink(S_MEAL);
	sem_unlink(S_STOP);
	(*phi).s_forks = sem_open(S_FORKS, O_CREAT | O_EXCL, 0666, (*phi).nb_philo);
	if ((*phi).s_forks == SEM_FAILED)
		return (perror("sem_open forks"), KO);
	(*phi).s_print = sem_open(S_PRINT, O_CREAT | O_EXCL, 0666, 1);
	if ((*phi).s_print == SEM_FAILED)
		return (perror("sem_open print"), KO);
	(*phi).s_dead = sem_open(S_DEAD, O_CREAT | O_EXCL, 0666, 1);
	if ((*phi).s_dead == SEM_FAILED)
		return (perror("sem_open dead"), KO);
	(*phi).s_meal = sem_open(S_MEAL, O_CREAT | O_EXCL, 0666, 1);
	if ((*phi).s_meal == SEM_FAILED)
		return (perror("sem_open meal"), KO);
	//
	(*phi).s_stop = sem_open(S_STOP, O_CREAT | O_EXCL, 0666, 1);
	if ((*phi).s_stop == SEM_FAILED)
		return (perror("sem_open stop"), KO);
	//
	return (OK);
}

//*************** on perror pour i,  free des children avant i   *******/
// le parent recoit le pid de l'enfant
int	create_philos(t_phi *phi)
{
	int		i;
	pid_t	pid;
	int		code;

	i = 0;
	while (i < (*phi).nb_philo)
	{
		pid = fork();
		// printf("pid = %d\n", pid);
		init_philo(phi, pid, i);
		if (pid == -1)
			return (perror("philo: fork"), KO);
		if (pid == 0)
		{
			create_thread(&(*phi).philos[i]);
			routine(phi, &(*phi).philos[i]);
			pthread_join((*phi).philos[i].thread, NULL);
			//
			if (is_dead(&(*phi).philos[i]) == 1)
				code = 1;
			else
				code = 0;	
			sem_close((*phi).s_forks);
			sem_close((*phi).s_print);
			sem_close((*phi).s_meal);
			sem_close((*phi).s_dead);
			sem_close((*phi).s_stop);
			// sem_unlink(S_FORKS);
			// sem_unlink(S_PRINT);
			// sem_unlink(S_DEAD);
			// sem_unlink(S_MEAL);
			free((*phi).philos);
			// //exit((*phi).philos[i].pid);
			exit(code);
		}
		i++;
	}
	// is_a_dead(phi);
	return (OK);
}

void	init_philo(t_phi *phi, pid_t pid, int i)
{
	(*phi).philos[i].pid = pid;
	(*phi).philos[i].id = i + 1;
	//(*phi).philos[i].start = gettime_ms();
	(*phi).philos[i].start = (*phi).start;
	(*phi).philos[i].last_meal = gettime_ms();
	(*phi).philos[i].nb_meal = 0;
	(*phi).philos[i].nb_philo = (*phi).nb_philo;
	(*phi).philos[i].time_to_die = (*phi).time_to_die;
	(*phi).philos[i].time_to_eat = (*phi).time_to_eat;
	(*phi).philos[i].time_to_sleep = (*phi).time_to_sleep;
	(*phi).philos[i].must_eat = (*phi).must_eat;
	(*phi).philos[i].s_forks = &(*phi).s_forks;
	(*phi).philos[i].s_print = &(*phi).s_print;
	(*phi).philos[i].s_dead = &(*phi).s_dead;
	(*phi).philos[i].s_meal = &(*phi).s_meal;
	(*phi).philos[i].s_stop = &(*phi).s_stop;
	(*phi).philos[i].dead = 0;
	// (*phi).philos[i].dead = &(*phi).is_dead;
	// printf("la\n");
}

void	is_a_dead(t_phi *phi)
{
	int	i;

	sem_wait((*phi).s_stop);
	i = 0;
	while (i < (*phi).nb_philo)
	{
		kill((*phi).philos[i].pid, SIGKILL);
		i++;
	}
	sem_post((*phi).s_stop);
	// return (OK);
}
