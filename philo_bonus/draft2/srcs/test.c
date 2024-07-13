/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 01:28:22 by caguillo          #+#    #+#             */
/*   Updated: 2024/07/13 01:33:08 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h> // For O_* constants
#include <semaphore.h>
#include <stdio.h>

int	main(void)
{
	sem_t *sema;

	sem_unlink("/sema");
	sema = sem_open("/sema", O_CREAT | O_EXCL, 0600, 0);
	if (sema == SEM_FAILED)
		return (perror("sem_open sema"), 1);
	int i = 0;
	while (sem_wait(sema) == 1)
	{
		printf("%d\n", i);
		if (i >= 1000)
			sem_post(sema);
		i++;
	}
	return (0);
}