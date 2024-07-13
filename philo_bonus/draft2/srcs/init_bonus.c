/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:13:26 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/12 04:36:33 by caguillo         ###   ########.fr       */
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
	// (*phi).start = gettime_ms();
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
// le parent recoit le pid de l'enfant
int	create_philos(t_phi *phi)
{
	int		i;
	pid_t	pid;

	// pthread_t *threads;
	// threads = ft_calloc((*phi).nb_philo, sizeof(pthread_t));
	// if (!threads)
	// 	return (KO);
	i = 0;
	while (i < (*phi).nb_philo)
	{
		pid = fork();
		init_philo(phi, pid, i);
		if (pid == -1)
			return (perror("philo: fork"), KO);
		if (pid == 0)
		{
			create_thread(&(*phi).philos[i]);			
			monitor(&(*phi).philos[i]);
			printf("id = %d\n", i+1);
			pthread_join((*phi).philos[i].thread, NULL);
			//printf("join id = %d\n", i+1);
			// pthread_detach((*phi).philos[i].thread);
			// if (is_to_die(phi, &(*phi).philos[i]) == 1)
			// {
			// 	print_log(phi, &((*phi).philos[i]), DIED);
			// }
			// free((*phi).philos);
			sem_close((*phi).s_forks);
			sem_close((*phi).s_print);
			sem_close((*phi).s_meal);
			sem_close((*phi).s_dead);
			free((*phi).philos);// exit((*phi).philos[i].pid);
			exit(0);
			
		}
		i++;
	}
	// free(threads);
	return (OK);
}

void	init_philo(t_phi *phi, pid_t pid, int i)
{
	(*phi).philos[i].pid = pid;
	(*phi).philos[i].id = i + 1;
	(*phi).philos[i].start = gettime_ms();
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
	(*phi).philos[i].dead = 0;
	// (*phi).philos[i].dead = &(*phi).is_dead;
}
