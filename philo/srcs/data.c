/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguillo <caguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:58:12 by caguillo          #+#    #+#             */
/*   Updated: 2024/06/12 00:12:39 by caguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/phi.h"

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
	if (ft_atoll(argv[1]) > MAX)
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
